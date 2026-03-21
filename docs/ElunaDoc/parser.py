import re
import typing
import markdown
from typedecorator import params, returns, Nullable
from typing import Any, Dict, List, Optional, Tuple, TypedDict


class TableDict(TypedDict):
    columns: List[str]
    values: List[List[Any]]


class ParameterDoc(object):
    """The documentation data of a parameter or return value for an Eluna method."""

    # The integer ranges that each C++ type is valid for. None means valid for all numbers.
    valid_ranges = {
        "float": None,
        "double": None,
        "int": ("-2,147,483,647", "2,147,483,647"),  # safe assumption 32-bit
        "int8": ("-127", "127"),
        "uint8": ("0", "255"),
        "int16": ("-32,767", "32,767"),
        "uint16": ("0", "65,535"),
        "int32": ("-2,147,483,647", "2,147,483,647"),
        "uint32": ("0", "4,294,967,295"),
        "int64": ("-9,223,372,036,854,775,808", "9,223,372,036,854,775,807"),
        "uint64": ("0", "18,446,744,073,709,551,615"),
        "ObjectGuid": ("0", "18,446,744,073,709,551,615"),
    }

    @params(self=object, name=Nullable(str), data_type=str, description=str, default_value=Nullable(str))
    def __init__(self, name, data_type, description, default_value=None):
        """If `name` is not provided, the Parameter is a returned value instead of a parameter."""
        self.name = name
        self.data_type = data_type
        self.default_value = default_value

        if self.data_type == "...":
            self.name = "..."
        else:
            assert self.name is not None

        if description:
            # Capitalize the first letter, add a period, and parse as Markdown.
            self.description = "{}{}. ".format(description[0].capitalize(), description[1:])
            self.description = markdown.markdown(self.description)
        else:
            self.description = ""

        # If the data type is a C++ number, convert to Lua number and add range info to description.
        if self.data_type in self.valid_ranges.keys():
            range_ = ParameterDoc.valid_ranges[self.data_type]
            if range_:
                self.description += '<p><em>Valid numbers</em>: integers from {0} to {1}.</p>'.format(
                    range_[0], range_[1]
                )
            else:
                self.description += "<p><em>Valid numbers</em>: all decimal numbers.</p>"

            self.data_type = "number"

        elif self.data_type == "bool":
            self.data_type = "boolean"

        elif self.data_type == "int64" or self.data_type == "uint64":
            self.data_type = "[" + self.data_type + "]"

        elif (
            self.data_type not in ["nil", "boolean", "number", "string", "table", "function", "..."]
            and self.data_type[:1] != "["
        ):
            print(f"Missing angle brackets [] around the data type name: `{self.data_type}`")


def _apply_hook_lua_names_to_tables(
    tables: List[TableDict],
    hook_category: Optional[str],
    exported_hooks: Optional[Dict[str, Dict[str, Dict]]],
) -> List[TableDict]:
    """
    Rewrites the first value in each @values row to the Lua global:
      events.<category>.<lua_name>
    and keeps the numeric id as a tooltip by using dict format:
      { "events.category.name": "123" }

    This function ONLY runs when hook_category is provided via @hook.

    It supports row[0] being either:
      - a numeric id (e.g. "1")
      - an enum token (e.g. "SPELL_EVENT_ON_CAST")
    """
    if not tables or not hook_category or not exported_hooks:
        return tables

    cat = exported_hooks.get(hook_category)
    if not cat:
        return tables

    by_id = cat.get("by_id", {})
    by_enum = cat.get("by_enum", {})

    for t in tables:
        for row in t.get("values", []):
            if not row:
                continue

            key = row[0]

            # 1) Numeric ID style
            id_int: Optional[int] = None
            lua_name: Optional[str] = None
            try:
                id_int = int(key)
                lua_name = by_id.get(id_int)
            except (TypeError, ValueError):
                pass

            # 2) Enum token style
            if lua_name is None and isinstance(key, str):
                enum_info = by_enum.get(key)
                if enum_info:
                    id_int, lua_name = enum_info  # (int, str)

            if lua_name is None or id_int is None:
                continue

            lua_global = f"events.{hook_category}.{lua_name}"
            row[0] = {lua_global: str(id_int)}

    return tables


class MethodDoc(object):
    """The documentation data of an Eluna method."""

    @params(
        self=object,
        name=str,
        description=str,
        tables=[TableDict],
        prototypes=[str],
        warning=[str],
        parameters=[ParameterDoc],
        returned=[ParameterDoc],
        hook_category=Nullable(str),
        exported_hooks=Nullable(object),
    )
    def __init__(
        self,
        name: str,
        description: str,
        tables: List[TableDict],
        prototypes: List[str],
        warning: str,
        parameters: List[ParameterDoc],
        returned: List[ParameterDoc],
        hook_category: Optional[str] = None,
        exported_hooks: Optional[Dict[str, Dict[str, Dict]]] = None,
    ):
        self.name = name
        self.prototypes = prototypes
        self.parameters = parameters
        self.returned = returned
        self.hook_category = hook_category

        # If this method has @hook, rewrite its table Event column to events.<category>.<name>
        if tables and hook_category:
            tables = _apply_hook_lua_names_to_tables(tables, hook_category, exported_hooks)

        # Convert any parsed tables into HTML (Markdown tables → HTML)
        if tables:
            html_tables = []
            for table in tables:
                md_table = "| " + " | ".join(table["columns"]) + " |\n"
                md_table += "| " + " | ".join(["---"] * len(table["columns"])) + " |\n"

                for row in table["values"]:
                    md_row = "| "
                    for value in row:
                        if isinstance(value, dict):
                            md_row += self._format_dict_values(value)
                        else:
                            md_row += str(value)
                        md_row += " | "
                    md_table += md_row + "\n"

                html_table = markdown.markdown(md_table, extensions=["tables"])
                html_tables.append(html_table)

            self.tables = "".join(html_tables)
        else:
            self.tables = ""

        # Parse the description as Markdown.
        self.description = markdown.markdown(description)
        # Pull the first paragraph out of the description as the short description.
        self.short_description = self.description.split("</p>")[0][3:]
        # If it has a description, it is "documented".
        self.documented = self.description != ""
        # Parse the warning as Markdown, but remove <p> tags
        self.warning = markdown.markdown(warning)
        self.warning = re.sub(r"^<p>(.*?)</p>$", r"\1", self.warning, flags=re.DOTALL)

    """Helper function to parse table dictionaries. Only used in Register methods for now."""

    def _format_dict_values(self, d: Dict[str, str]) -> str:
        html_parts = []
        for key, value in d.items():
            html_parts.append(f'<span title="{value}">{key}</span>')
        return ", ".join(html_parts)


class MangosClassDoc(object):
    """The documentation of a MaNGOS class that has Lua methods."""

    @params(self=object, name=str, description=str, methods=[MethodDoc])
    def __init__(self, name, description, methods):
        self.name = name
        # Parse the description as Markdown.
        self.description = markdown.markdown(description)
        # Pull the first paragraph out of the description as the short description.
        self.short_description = self.description.split("</p>")[0][3:]
        # Sort the methods by their names.
        self.methods = sorted(methods, key=lambda m: m.name)

        # If any of our methods are not documented, we aren't fully documented.
        for method in methods:
            if not method.documented:
                self.fully_documented = False
                break
        else:
            self.fully_documented = True

        # If any of our methods are documented, we aren't fully undocumented.
        for method in methods:
            if method.documented:
                self.fully_undocumented = False
                break
        else:
            self.fully_undocumented = True


class ClassParser(object):
    """Parses a file line-by-line and returns methods when enough information is received to build them."""

    # Class documentation
    class_start_regex = re.compile(r"\s*/\*\*\*")
    class_body_regex = re.compile(r"\s*\*\s*(.*)")
    class_end_regex = re.compile(r"\s*\*/")

    # Method documentation
    start_regex = re.compile(r"\s*/\*\*")
    body_regex = re.compile(r"\s*\s?\*\s?(.*)")

    # Hook tag (explicit only)
    hook_regex = re.compile(r"\s*\*\s@hook\s+(\w+)")

    # Table parsing
    table_regex = re.compile(r"\s*\*\s@table")
    table_columns_regex = re.compile(r"\s*\*\s@columns\s*\[(.+)\]")
    table_values_regex = re.compile(r"\s*\*\s@values\s*\[(.+?)\]")

    # Warnings
    warning_regex = re.compile(r"""\s*\*\s*@warning\s+(.+)""", re.X)

    param_regex = re.compile(
        r"""\s*\*\s@param\s
        ([^\s]+)\s(\w+)?       # type + name
        (?:\s=\s([^\s:]+))?    # default
        (?:\s:\s(.+))?         # description
        """,
        re.X,
    )

    return_regex = re.compile(
        r"""\s*\*\s@return\s
        ([\[\]\w]+)\s(\w+)
        (?:\s:\s(.+))?
        """,
        re.X,
    )

    proto_regex = re.compile(
        r"""\s*\*\s@proto\s
        ([\w\s,]+)?            # args
        (?:=\s)?               # equals separator
        (?:\(([\w\s,]+)\))?    # returns
        """,
        re.X,
    )

    comment_end_regex = re.compile(r"\s*\*/")
    end_regex = re.compile(r"\s*int\s(\w+)\s*\(")

    @params(self=object, class_name=str, exported_hooks=Nullable(object))
    def __init__(self, class_name: str, exported_hooks: Optional[Dict[str, Dict[str, Dict]]] = None):
        assert ClassParser.class_body_regex is not ClassParser.body_regex
        self.methods: List[MethodDoc] = []
        self.class_name = class_name
        self.class_description = ""
        self.exported_hooks = exported_hooks
        self.reset()

    def reset(self):
        self.last_regex = None

        self.description = ""
        self.warning = ""
        self.params: List[ParameterDoc] = []
        self.returned: List[ParameterDoc] = []
        self.method_name: Optional[str] = None
        self.prototypes: List[str] = []
        self.tables: List[TableDict] = []

        # Explicit only; NO inference.
        self.hook_category: Optional[str] = None

    def handle_class_body(self, match):
        self.class_description += match.group(1) + "\n"

    def handle_body(self, match):
        self.description += match.group(1) + "\n"

    def handle_hook(self, match):
        self.hook_category = match.group(1).lower()

    def handle_table(self, _match):
        self.tables.append({"columns": [], "values": []})

    def handle_table_columns(self, match):
        if self.tables:
            self.tables[-1]["columns"] = match.group(1).split(", ")

    def handle_table_values(self, match):
        if not self.tables:
            return

        # Split values while respecting quoted strings and <> blobs.
        values = re.findall(r'(?:[^,<>"]|"(?:\\.|[^"])*"|<[^>]*>)+', match.group(1))
        processed_values: List[Any] = []

        for value in values:
            stripped_value = value.strip(' "')

            # Parse the content inside < >
            if stripped_value.startswith("<") and stripped_value.endswith(">"):
                inner_content = stripped_value[1:-1]

                # Convert inner key-value pairs to a dict
                pair_regex = re.compile(r"(\w+):\s*([\w\s]+)")
                stripped_value = dict(pair_regex.findall(inner_content))

            processed_values.append(stripped_value)

        self.tables[-1]["values"].append(processed_values)

    def handle_warning(self, match):
        self.warning += match.group(1)

    def handle_param(self, match):
        data_type, name, default, description = match.group(1), match.group(2), match.group(3), match.group(4)
        self.params.append(ParameterDoc(name, data_type, description, default))

    def handle_return(self, match):
        data_type, name, description = match.group(1), match.group(2), match.group(3)
        self.returned.append(ParameterDoc(name, data_type, description))

    def handle_proto(self, match):
        return_values, parameters = match.group(1), match.group(2)
        parameters = " " + parameters + " " if parameters else ""
        return_values = return_values + "= " if return_values else ""

        if self.class_name == "Global":
            prototype = "{0}{{0}}({1})".format(return_values, parameters)
        else:
            prototype = "{0}{1}:{{0}}({2})".format(return_values, self.class_name, parameters)

        self.prototypes.append(prototype)

    def handle_end(self, match):
        self.method_name = match.group(1)

        def make_prototype(parameters: str) -> str:
            if parameters != "":
                parameters = " " + parameters + " "

            if self.class_name == "Global":
                if self.returned:
                    return_values = ", ".join([param.name for param in self.returned])
                    return "{0} = {1}({2})".format(return_values, self.method_name, parameters)
                return "{0}({1})".format(self.method_name, parameters)

            if self.returned:
                return_values = ", ".join([param.name for param in self.returned])
                return "{0} = {1}:{2}({3})".format(return_values, self.class_name, self.method_name, parameters)
            return "{0}:{1}({2})".format(self.class_name, self.method_name, parameters)

        if not self.prototypes:
            params_with_default = []
            last_non_default_i = 0
            simple_order = True

            for i, param in enumerate(self.params):
                if param.default_value:
                    params_with_default.append(param)
                else:
                    last_non_default_i = i
                    if params_with_default:
                        simple_order = False

            if not params_with_default or not simple_order:
                parameters = ", ".join([param.name for param in self.params])
                self.prototypes.append(make_prototype(parameters))
            else:
                for i in range(last_non_default_i, len(self.params)):
                    parameters = ", ".join([param.name for param in self.params[: i + 1]])
                    self.prototypes.append(make_prototype(parameters))
        else:
            self.prototypes = [proto.format(self.method_name) for proto in self.prototypes]

        self.methods.append(
            MethodDoc(
                self.method_name,
                self.description,
                self.tables,
                self.prototypes,
                self.warning,
                self.params,
                self.returned,
                hook_category=self.hook_category,
                exported_hooks=self.exported_hooks,
            )
        )

    regex_handlers = {
        class_start_regex: None,
        class_body_regex: handle_class_body,
        class_end_regex: None,
        start_regex: None,
        body_regex: handle_body,
        hook_regex: handle_hook,
        table_regex: handle_table,
        table_columns_regex: handle_table_columns,
        table_values_regex: handle_table_values,
        warning_regex: handle_warning,
        param_regex: handle_param,
        return_regex: handle_return,
        proto_regex: handle_proto,
        comment_end_regex: None,
        end_regex: handle_end,
    }

    next_regexes = {
        None: [class_start_regex, start_regex, end_regex],
        class_start_regex: [class_end_regex, class_body_regex],
        class_body_regex: [class_end_regex, class_body_regex],
        class_end_regex: [],
        start_regex: [hook_regex, table_regex, warning_regex, param_regex, return_regex, proto_regex, comment_end_regex, body_regex],
        body_regex: [hook_regex, table_regex, warning_regex, param_regex, return_regex, proto_regex, comment_end_regex, body_regex],
        proto_regex: [hook_regex, table_regex, warning_regex, param_regex, return_regex, proto_regex, comment_end_regex, body_regex],
        table_regex: [hook_regex, table_regex, table_columns_regex, warning_regex, param_regex, return_regex, comment_end_regex, body_regex],
        table_columns_regex: [hook_regex, table_values_regex, warning_regex, param_regex, return_regex, comment_end_regex, body_regex],
        table_values_regex: [hook_regex, table_values_regex, table_regex, warning_regex, param_regex, return_regex, comment_end_regex, body_regex],
        warning_regex: [hook_regex, table_values_regex, table_regex, warning_regex, param_regex, return_regex, comment_end_regex, body_regex],
        param_regex: [hook_regex, table_regex, warning_regex, param_regex, return_regex, comment_end_regex, body_regex],
        return_regex: [hook_regex, return_regex, comment_end_regex],
        comment_end_regex: [end_regex],
        end_regex: [],
        hook_regex: [hook_regex, table_regex, warning_regex, param_regex, return_regex, proto_regex, comment_end_regex, body_regex],
    }

    @returns(Nullable(MethodDoc))
    @params(self=object, line=str)
    def next_line(self, line):
        valid_regexes = self.next_regexes[self.last_regex]

        for regex in valid_regexes:
            match = regex.match(line)
            if match:
                handler = self.regex_handlers[regex]
                if handler:
                    handler(self, match)
                self.last_regex = regex
                break
        else:
            self.reset()

    @returns(MangosClassDoc)
    def to_class_doc(self):
        return MangosClassDoc(self.class_name, self.class_description, self.methods)

    @staticmethod
    @returns(MangosClassDoc)
    @params(file=object, exported_hooks=Nullable(object))
    def parse_file(file, exported_hooks=None):
        """Parse the file `file` into a documented class."""
        class_name = file.name[:-len("Methods.h")]
        parser = ClassParser(class_name, exported_hooks=exported_hooks)

        line = file.readline()
        while line:
            parser.next_line(line)
            line = file.readline()

        return parser.to_class_doc()