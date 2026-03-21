import os
import shutil
import typing
import glob
import time
import re
from jinja2 import Environment, FileSystemLoader
from typedecorator import params, returns

from ElunaDoc.parser import ClassParser


@returns([(str, typing.IO)])
@params(search_path=str)
def find_class_files(search_path):
    """Find and open all files containing Eluna class methods in `search_path`."""
    old_dir = os.getcwd()
    os.chdir(search_path)
    method_file_names = [file_name for file_name in glob.glob("*Methods.h") if file_name != "BigIntMethods.h"]
    method_files = [open(file_name, "r", encoding="utf-8") for file_name in method_file_names]
    os.chdir(old_dir)
    return method_files


def make_renderer(template_path, link_parser_factory):
    """Return a function that can be used to render Jinja2 templates from the `template_path` directory."""
    env = Environment(loader=FileSystemLoader(template_path))

    def inner(template_name, output_path, level, **kwargs):
        env.filters["parse_links"], env.filters["parse_data_type"] = link_parser_factory(level)
        template = env.get_template(template_name)
        static = make_static(level)
        root = make_root(level)

        with open("build/" + output_path, "w", encoding="utf-8") as out:
            out.write(template.render(level=level, static=static, root=root, **kwargs))

    return inner


def make_static(level):
    return lambda file_name: ("../" * level) + "static/" + file_name


def make_root(level):
    return lambda file_name: ("../" * level) + file_name


# ---------------- Hooks.h parsing (events.<category>.<name>) ----------------

_macro_start = re.compile(r"^\s*#define\s+([A-Z0-9_]+)_EVENTS_LIST\(X\)\s*\\\s*$")
_macro_item = re.compile(r'^\s*X\(\s*([A-Z0-9_]+)\s*,\s*([0-9]+)\s*,\s*"([^"]+)"\s*\)\s*\\?\s*$')

# Capture: { "category", SomeEventsTable, CountOf(SomeEventsTable) },
_hook_table_entry = re.compile(
    r'^\s*\{\s*"([^"]+)"\s*,\s*([A-Za-z0-9_]+)\s*,\s*CountOf\(\2\)\s*\}\s*,?\s*$'
)


def _table_name_to_macro_key(events_table_name: str) -> str:
    """
    Converts 'InstanceEventsTable' -> 'instance'
             'GameObjectEventsTable' -> 'gameobject'
             'PacketEventsTable' -> 'packet'
    """
    suffix = "EventsTable"
    if events_table_name.endswith(suffix):
        return events_table_name[: -len(suffix)].lower()
    return events_table_name.lower()


def parse_macro_lists(hooks_h_path: str) -> dict[str, dict[str, dict]]:
    """
    Return mapping per macro_category (derived from *_EVENTS_LIST macro name):
      {
        "spell": {
          "by_id":   { 1: "on_cast", ... },
          "by_enum": { "SPELL_EVENT_ON_CAST": (1, "on_cast"), ... }
        },
        ...
      }
    """
    hooks: dict[str, dict[str, dict]] = {}
    current: str | None = None

    with open(hooks_h_path, "r", encoding="utf-8") as f:
        for line in f:
            m = _macro_start.match(line)
            if m:
                current = m.group(1).lower()  # e.g. SPELL -> "spell", INSTANCE -> "instance"
                hooks.setdefault(current, {"by_id": {}, "by_enum": {}})
                continue

            if current:
                mi = _macro_item.match(line)
                if mi:
                    enum_name = mi.group(1)
                    id_value = int(mi.group(2))
                    lua_name = mi.group(3)
                    hooks[current]["by_id"][id_value] = lua_name
                    hooks[current]["by_enum"][enum_name] = (id_value, lua_name)
                    continue

                # End macro block when we hit a line not continuing with '\'
                if not line.rstrip().endswith("\\"):
                    current = None

    return hooks


def build_exported_hook_map(hooks_h_path: str) -> dict[str, dict]:
    """
    Builds a map keyed by exported Lua category from HookTypeTable.

    IMPORTANT: the macro key is derived from the backing EventsTable name, not the exported category.
    Example:
      { "map", InstanceEventsTable, CountOf(InstanceEventsTable) }
      -> macro key = "instance" -> INSTANCE_EVENTS_LIST
    """
    macro_lists = parse_macro_lists(hooks_h_path)

    exported: dict[str, dict] = {}
    in_hook_table = False

    with open(hooks_h_path, "r", encoding="utf-8") as f:
        for line in f:
            if "static constexpr HookStorage HookTypeTable" in line:
                in_hook_table = True
                continue
            if in_hook_table and "};" in line:
                in_hook_table = False
                continue
            if not in_hook_table:
                continue

            m = _hook_table_entry.match(line)
            if not m:
                continue

            exported_category = m.group(1)   # e.g. "map"
            events_table_name = m.group(2)   # e.g. "InstanceEventsTable"

            macro_key = _table_name_to_macro_key(events_table_name)  # e.g. "instance"
            table_map = macro_lists.get(macro_key)

            if not table_map:
                exported[exported_category] = {"by_id": {}, "by_enum": {}}
                print(
                    f"[docs] Warning: HookTypeTable exports '{exported_category}' ({events_table_name}) "
                    f"but no matching *_EVENTS_LIST was found for key '{macro_key}'"
                )
                continue

            exported[exported_category] = table_map

    return exported


# ---------------- Main ----------------

if __name__ == "__main__":
    # Recreate the build folder and copy static files over.
    if os.path.exists("build"):
        shutil.rmtree("build")
    os.mkdir("build")
    shutil.copytree("ElunaDoc/static", "build/static")

    # Load hook globals (events.<category>.<name>) from Hooks.h
    hooks_path = os.path.normpath(os.path.join(os.path.dirname(__file__), "..", "..", "hooks", "Hooks.h"))
    print(f"Loading hook globals from: {hooks_path}")
    exported_hooks = build_exported_hook_map(hooks_path)

    # Load up all files with methods we need to parse.
    print("Finding Eluna method files...")
    class_files = find_class_files("../methods/TrinityCore/")

    # Parse all the method files.
    classes = []
    for f in class_files:
        print(f"Parsing file {f.name}...")
        classes.append(ClassParser.parse_file(f, exported_hooks=exported_hooks))
        f.close()

    # Sort the classes so they are in the correct order in lists.
    classes.sort(key=lambda c: c.name)

    def make_parsers(level):
        """Returns filters that parse refs to other classes/methods/enums and insert links."""
        class_names = []
        method_names = []

        for class_ in classes:
            class_names.append("[" + class_.name + "]")
            for method in class_.methods:
                method_names.append("[" + class_.name + ":" + method.name + "]")

        def link_parser(content):
            # Replace [Class:Method] and [Class] with links
            for name in method_names:
                full_name = name[1:-1]
                class_name, method_name = full_name.split(":")
                url = "{}{}/{}.html".format(("../" * level), class_name, method_name)
                content = content.replace(name, '<a class="fn" href="{}">{}</a>'.format(url, full_name))

            for name in class_names:
                class_name = name[1:-1]
                url = "{}{}/index.html".format(("../" * level), class_name)
                content = content.replace(name, '<a class="mod" href="{}">{}</a>'.format(url, class_name))

            return content

        # Links to the "Programming in Lua" documentation for each Lua type.
        lua_type_documentation = {
            "nil": "http://www.lua.org/pil/2.1.html",
            "boolean": "http://www.lua.org/pil/2.2.html",
            "number": "http://www.lua.org/pil/2.3.html",
            "string": "http://www.lua.org/pil/2.4.html",
            "table": "http://www.lua.org/pil/2.5.html",
            "function": "http://www.lua.org/pil/2.6.html",
            "...": "http://www.lua.org/pil/5.2.html",
        }

        def data_type_parser(content):
            # If the type is a Lua type, return a link to Lua documentation.
            if content in lua_type_documentation:
                url = lua_type_documentation[content]
                return '<strong><a href="{}">{}</a></strong>'.format(url, content)

            # Otherwise try to build a link to the proper page.
            if content in class_names:
                class_name = content[1:-1]
                url = "{}{}/index.html".format(("../" * level), class_name)
                return '<strong><a class="mod" href="{}">{}</a></strong>'.format(url, class_name)

            # Case for enums to direct to a search on github
            enum_name = content[1:-1]
            url = (
                'https://github.com/ElunaLuaEngine/ElunaTrinityWotlk/search?l=cpp&q=%22enum+{}%22'
                "&type=Code&utf8=%E2%9C%93"
            ).format(enum_name)
            return '<strong><a href="{}">{}</a></strong>'.format(url, enum_name)

        return link_parser, data_type_parser

    # Create the render function with the template path and parser maker.
    render = make_renderer("ElunaDoc/templates", make_parsers)

    # Render the index.
    render("index.html", "index.html", level=0, classes=classes)
    # Render the search index.
    render("search-index.js", "search-index.js", level=0, classes=classes)
    # Render the date.
    render("date.js", "date.js", level=0, currdate=time.strftime("%d/%m/%Y"))

    for class_ in classes:
        print(f"Rendering pages for class {class_.name}...")

        # Make a folder for the class.
        os.mkdir("build/" + class_.name)
        index_path = "{}/index.html".format(class_.name)
        sidebar_path = "{}/sidebar.js".format(class_.name)

        # Render the class's index page.
        render("class.html", index_path, level=1, classes=classes, current_class=class_)

        # Render the class's sidebar script.
        render("sidebar.js", sidebar_path, level=1, classes=classes, current_class=class_)

        # Render each method's page.
        for method in class_.methods:
            method_path = "{}/{}.html".format(class_.name, method.name)
            render("method.html", method_path, level=1, current_class=class_, current_method=method)