import re
import typing
import markdown
from typedecorator import params, returns, Nullable
from typing import Any, List, TypedDict

class TableDict(TypedDict):
    columns: List[str]
    values: List[List[Any]]

class ParameterDoc(object):
    """The documentation data of a parameter or return value for an Eluna method."""

    # The integer ranges that each C++ type is valid for. None means valid for all numbers.
    valid_ranges = {
        'float': None,
        'double': None,
        'int': ('-2,147,483,647', '2,147,483,647'),  # This should be -32767..32767, but it's pretty safe to assume 32-bit.
        'int8': ('-127', '127'),
        'uint8': ('0', '255'),
        'int16': ('-32,767', '32,767'),
        'uint16': ('0', '65,535'),
        'int32': ('-2,147,483,647', '2,147,483,647'),
        'uint32': ('0', '4,294,967,295'),
        'int64': ('-9,223,372,036,854,775,808', '9,223,372,036,854,775,807'),
        'uint64': ('0', '18,446,744,073,709,551,615'),
        'ObjectGuid': ('0', '18,446,744,073,709,551,615'),
    }

    @params(self=object, name=Nullable(str), data_type=str, description=str, default_value=Nullable(str))
    def __init__(self, name, data_type, description, default_value=None):
        """If `name` is not provided, the Parameter is a returned value instead of a parameter."""
        self.name = name
        self.data_type = data_type
        self.default_value = default_value

        if self.data_type == '...':
            self.name = '...'
        else:
            assert(self.name is not None)

        if description:
            # Capitalize the first letter, add a period, and parse as Markdown.
            self.description = '{}{}. '.format(description[0].capitalize(), description[1:])
            self.description = markdown.markdown(self.description)
        else:
            self.description = ''

        # If the data type is a C++ number, convert to Lua number and add range info to description.
        if self.data_type in self.valid_ranges.keys():
            range = ParameterDoc.valid_ranges[self.data_type]
            if range:
                self.description += '<p><em>Valid numbers</em>: integers from {0} to {1}.</p>'.format(range[0], range[1])
            else:
                self.description += '<p><em>Valid numbers</em>: all decimal numbers.</p>'

            self.data_type = 'number'

        elif self.data_type == 'bool':
            self.data_type = 'boolean'

        elif self.data_type == 'int64' or self.data_type == 'uint64':
            self.data_type = '[' + self.data_type + ']'

        elif not self.data_type in ['nil', 'boolean', 'number', 'string', 'table', 'function', '...'] and self.data_type[:1] != '[':
            print(f"Missing angle brackets [] around the data type name: `{self.data_type}`")


class MethodDoc(object):
    """The documentation data of an Eluna method."""
    @params(self=object, name=str, description=str, tables=[TableDict], prototypes=[str], warning=[str], parameters=[ParameterDoc], returned=[ParameterDoc])
    def __init__(self, name, description, tables, prototypes, warning, parameters, returned):
        self.name = name
        self.prototypes = prototypes
        self.tables = tables
        self.parameters = parameters
        self.returned = returned

        if tables:
            html_tables = []
            
            for table in tables:
                # Generate Markdown Table for each table
                md_table = '| ' + ' | '.join(table['columns']) + ' |\n'  # Header
                md_table += '| ' + ' | '.join(['---'] * len(table['columns'])) + ' |\n'  # Separator

                for row in table['values']:
                    md_row = '| '
                    for value in row:
                        if isinstance(value, dict):
                            # If the value is a dictionary, format the values and preserve the type in the documentation
                            md_row += self._format_dict_values(value)
                        else:
                            md_row += value
                        md_row += ' | '
                    md_table += md_row + '\n'
                
                # Convert the generated Markdown table to HTML
                html_table = markdown.markdown(md_table, extensions=['tables'])
                
                # Append the HTML table to the list
                html_tables.append(html_table)

            # Combine all HTML tables into a single string (separated by two newlines)
            self.tables = ''.join(html_tables)
        
        # Parse the description as Markdown.
        self.description = markdown.markdown(description)
        # Pull the first paragraph out of the description as the short description.
        self.short_description = self.description.split('</p>')[0][3:]
        # If it has a description, it is "documented".
        self.documented = self.description != ''
        # Parse the warning as Markdown, but remote <p> tags
        self.warning = markdown.markdown(warning)
        self.warning = re.sub(r'^<p>(.*?)</p>$', r'\1', self.warning, flags=re.DOTALL)

    """Helper function to parse table dictionaries. Only used in Register methods for now."""
    def _format_dict_values(self, d):
        html_str = ""
        html_parts = []

        for key, value in d.items():
            html_parts.append(f'<span title="{value}">{key}</span>')

        html_str = ', '.join(html_parts)
        return html_str


class MangosClassDoc(object):
    """The documentation of a MaNGOS class that has Lua methods."""
    @params(self=object, name=str, description=str, methods=[MethodDoc])
    def __init__(self, name, description, methods):
        self.name = name
        # Parse the description as Markdown.
        self.description = markdown.markdown(description)
        # Pull the first paragraph out of the description as the short description.
        self.short_description = self.description.split('</p>')[0][3:]
        # Sort the methods by their names.
        self.methods = sorted(methods, key=lambda m: m.name)

        # If any of our methods are not documented, we aren't fully documented.
        for method in methods:
            if not method.documented:
                self.fully_documented = False
                break
        else:
            self.fully_documented = True

        # In the same vein, if any of our methods are documented, we aren't fully *un*documented.
        for method in methods:
            if method.documented:
                self.fully_undocumented = False
                break
        else:
            self.fully_undocumented = True


class ClassParser(object):
    """Parses a file line-by-line and returns methods when enough information is received to build them."""

    # Various regular expressions to parse different parts of the doc string.
    # There are used to parse the class's description.
    class_start_regex = re.compile(r"\s*/\*\*\*")  # The start of class documentation, i.e. /***
    class_body_regex = re.compile(r"\s*\*\s*(.*)")  # The "body", i.e. a * and optionally some descriptive text.
    class_end_regex = re.compile(r"\s*\*/")  # The end of the comment portion, i.e. */

    # These are used to parse method documentation.
    start_regex = re.compile(r"\s*/\*\*")  # The start of documentation, i.e. /**
    body_regex = re.compile(r"\s*\s?\*\s?(.*)")  # The "body", i.e. a * and optionally some descriptive text.
    # An extra optional space (\s?) was thrown in to make it different from `class_body_regex`.
    
    # Regular expressions for parsing a table.
    table_regex = re.compile(r"\s*\*\s@table")
    table_columns_regex = re.compile(r"\s*\*\s@columns\s*\[(.+)\]")
    table_values_regex = re.compile(r"\s*\*\s@values\s*\[(.+?)\]")
    
    # Regex for catching warning tags
    warning_regex = re.compile(r"""\s*\*\s*@warning\s+(.+)""", re.X)
    
    param_regex = re.compile(r"""\s*\*\s@param\s        # The @param tag starts with opt. whitespace followed by "* @param ".
                                 ([^\s]+)\s(\w+)?       # The data type, a space, and the name of the param.
                                 (?:\s=\s([^\s:]+))?    # The default value: a space, =, and a value that can include periods but stops at whitespace or a colon.
                                 (?:\s:\s(.+))?         # The description: a colon surrounded by spaces, followed by text.
                                 """, re.X)
    # This is the same as the @param tag, minus the default value part.
    return_regex = re.compile(r"""\s*\*\s@return\s
                                  ([\[\]\w]+)\s(\w+)
                                  (?:\s:\s(.+))?
                                  """, re.X)
    proto_regex = re.compile(r"""\s*\*\s@proto\s
                                 ([\w\s,]+)?            # The list of arguments.
                                 (?:=\s)?               # An equals sign and a space separate the args and returns.
                                 (?:\(([\w\s,]+)\))?    # The list of return values, in parens.
                                 """, re.X)

    comment_end_regex = re.compile(r"\s*\*/")  # The end of the comment portion, i.e. */
    end_regex = re.compile(r"\s*int\s(\w+)\s*\(")  # The end of the documentation, i.e. int MethodName(

    def __init__(self, class_name):
        assert ClassParser.class_body_regex is not ClassParser.body_regex
        # The methods that have been parsed.
        self.methods = []
        # The name of the class being parsed.
        self.class_name = class_name
        # The description of the class being parsed.
        self.class_description = ''
        # Reset the parser's state machine.
        self.reset()

    def reset(self):
        # What the last handled regex was, to determine what the next should be.
        self.last_regex = None

        # These are used to piece together the next `Method`.
        self.description = ''
        self.warning = ''
        self.params = []
        self.returned = []
        self.method_name = None
        self.prototypes = []
        self.tables = []

    def handle_class_body(self, match):
        text = match.group(1)
        self.class_description += text + '\n'

    def handle_body(self, match):
        text = match.group(1)
        self.description += text + '\n'

    def handle_table(self, line):
        new_table = {
            "columns": [],
            "values": []
        }
        self.tables.append(new_table)

    def handle_table_columns(self, match):
        if self.tables:
            self.tables[-1]["columns"] = match.group(1).split(", ")

    def handle_table_values(self, match):
        if self.tables:
            values = re.findall(r'(?:[^,<>"]|"(?:\\.|[^"])*"|<[^>]*>)+', match.group(1))
            processed_values = []

            for value in values:
                stripped_value = value.strip(' "')
                # Parse the content inside < >
                if stripped_value.startswith("<") and stripped_value.endswith(">"):
                    # Remove prefix and suffix
                    inner_content = stripped_value[1:-1]

                    # Convert inner key-value pairs to a dict
                    pair_regex = re.compile(r"(\w+):\s*([\w\s]+)")
                    stripped_value = dict(pair_regex.findall(inner_content))
                
                processed_values.append(stripped_value)
            
            # Append the processed values to the last table
            self.tables[-1]["values"].append(processed_values)

    def handle_warning(self, match):
        warning = match.group(1)
        self.warning += warning

    def handle_param(self, match):
        data_type, name, default, description = match.group(1), match.group(2), match.group(3), match.group(4)
        self.params.append(ParameterDoc(name, data_type, description, default))

    def handle_return(self, match):
        data_type, name, description = match.group(1), match.group(2), match.group(3)
        self.returned.append(ParameterDoc(name, data_type, description))

    def handle_proto(self, match):
        return_values, parameters = match.group(1), match.group(2)
        parameters = ' '+parameters+' ' if parameters else ''
        return_values = return_values + '= ' if return_values else ''

        if self.class_name == 'Global':
            prototype = '{0}{{0}}({1})'.format(return_values, parameters)
        else:
            prototype = '{0}{1}:{{0}}({2})'.format(return_values, self.class_name, parameters)

        self.prototypes.append(prototype)

    def handle_end(self, match):
        self.method_name = match.group(1)

        def make_prototype(parameters):
            if parameters != '':
                parameters = ' ' + parameters + ' '

            if self.class_name == 'Global':
                if self.returned:
                    return_values = ', '.join([param.name for param in self.returned])
                    prototype = '{0} = {1}({2})'.format(return_values, self.method_name, parameters)
                else:
                    prototype = '{0}({1})'.format(self.method_name, parameters)
            else:
                if self.returned:
                    return_values = ', '.join([param.name for param in self.returned])
                    prototype = '{0} = {1}:{2}({3})'.format(return_values, self.class_name, self.method_name, parameters)
                else:
                    prototype = '{0}:{1}({2})'.format(self.class_name, self.method_name, parameters)

            return prototype

        # If there's no prototype, make one with all params and returns.
        if not self.prototypes:
            # A list of all parameters with default values.
            params_with_default = []
            # The index of the last non-default parameter.
            last_non_default_i = 0
            # If False, a parameter WITHOUT a default value follows one WITH a default value.
            # In this case, don't bother generating prototypes.
            simple_order = True

            for i, param in enumerate(self.params):
                if param.default_value:
                    params_with_default.append(param)
                else:
                    last_non_default_i = i
                    if params_with_default:
                        simple_order = False

            if not params_with_default or not simple_order:
                # Just generate one prototype with all the parameters.
                parameters = ', '.join([param.name for param in self.params])
                self.prototypes.append(make_prototype(parameters))
            else:
                # Generate a prototype for all the non-default parameters,
                #   then one for each default parameter with all the previous parameters.
                for i in range(last_non_default_i, len(self.params)):
                    parameters = ', '.join([param.name for param in self.params[:i+1]])
                    self.prototypes.append(make_prototype(parameters))

        else:
            # Format the method name into each prototype.
            self.prototypes = [proto.format(self.method_name) for proto in self.prototypes]

        self.methods.append(MethodDoc(self.method_name, self.description, self.tables, self.prototypes, self.warning, self.params, self.returned))

    # Table of which handler is used to handle each regular expressions.
    regex_handlers = {
        class_start_regex: None,
        class_body_regex: handle_class_body,
        class_end_regex: None,
        start_regex: None,
        body_regex: handle_body,
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

    # Table of which regular expressions can follow the last handled regex.
    # `body_regex` must always come LAST when used, since it also matches param, return, and comment_end.
    next_regexes = {
        None: [class_start_regex, start_regex, end_regex],
        class_start_regex: [class_end_regex, class_body_regex],
        class_body_regex: [class_end_regex, class_body_regex],
        class_end_regex: [],
        start_regex: [table_regex, warning_regex, param_regex, return_regex, proto_regex, comment_end_regex, body_regex],
        body_regex: [table_regex, warning_regex, param_regex, return_regex, proto_regex, comment_end_regex, body_regex],
        proto_regex: [table_regex, warning_regex, param_regex, return_regex, proto_regex, comment_end_regex, body_regex],
        table_regex: [table_regex, table_columns_regex, warning_regex, param_regex, return_regex, comment_end_regex, body_regex],
        table_columns_regex: [table_values_regex, warning_regex, param_regex, return_regex, comment_end_regex, body_regex],
        table_values_regex: [table_values_regex, table_regex, warning_regex, param_regex, return_regex, comment_end_regex, body_regex],
        warning_regex: [table_values_regex, table_regex, warning_regex, param_regex, return_regex, comment_end_regex, body_regex],
        param_regex: [table_regex, warning_regex, param_regex, return_regex, comment_end_regex, body_regex],
        return_regex: [return_regex, comment_end_regex],
        comment_end_regex: [end_regex],
        end_regex: [],
    }

    @returns(Nullable(MethodDoc))
    @params(self=object, line=str)
    def next_line(self, line):
        """Parse the next line of the file.

        This method returns a `Method` when enough data to form a `Method` has been parsed.
        Otherwise, it returns None.
        """
        # Get the list of expected regular expressions using the last one handled.
        valid_regexes = self.next_regexes[self.last_regex]

        # Try to find a match.
        for regex in valid_regexes:
            match = regex.match(line)

            if match:
                handler = self.regex_handlers[regex]

                if handler:
                    handler(self, match)

                # Not every regex has a handler, but keep track of where we are anyway.
                self.last_regex = regex
                # Break at the first match.
                break
        else:
            # No valid regex was found, reset everything.
            self.reset()

    @returns(MangosClassDoc)
    def to_class_doc(self):
        """Create an instance of `MangosClassDoc` from the parser's data.

        Is called by `parse_file` once parsing is finished.
        """
        return MangosClassDoc(self.class_name, self.class_description, self.methods)

    @staticmethod
    @returns(MangosClassDoc)
    @params(file=typing.IO)
    def parse_file(file):
        """Parse the file `file` into a documented class."""
        # Get the class name from "ClassMethods.h" by stripping off "Methods.h".
        class_name = file.name[:-len('Methods.h')]
        parser = ClassParser(class_name)

        line = file.readline()

        while line:
            parser.next_line(line)
            line = file.readline()

        return parser.to_class_doc()
