#Documentation generation

##Setting up
- install [python](https://www.python.org/)(2)
 - when installing, tick to install the path variable
 - may need restart after for installation to properly take effect
- install a package manager like [pip](https://pip.pypa.io/en/latest/)
 - if installed pip and doesnt work, restart or try easy_install command
- install the dependencies with manager
 - [Jinja2](https://pypi.python.org/pypi/Jinja2)
 - [typedecorator](https://pypi.python.org/pypi/typedecorator)
 - [markdown](https://pypi.python.org/pypi/Markdown)

##Generating
- Run in cmd `python -m ElunaDoc` when at `\LuaEngine\docs\`

##Documenting
You can document functions in the Eluna source code. For examples, simply open a method header file.

###Template
Here are basic templates for a function. When defining a parameter or a return value, the type and value name are mandatory.
```c++
/**
 * Description.
 *
 * @param Type paramName
 * @return Type returnName
 */
```
```c++
/**
 * Description.
 *
 * @param Type paramName = defaultValue : parameter description
 * @return Type returnName : return value description
 */
```

This is a template for a function that takes in different parameters. When defining a parameter or a return value, the type and value name are mandatory.
```c++
/**
 * Description.
 *
 * @proto returnValue = (object)
 * @proto returnValue = (x, y, z)
 * @param Type paramName = defaultValue : parameter description
 * @return Type returnName : return value description
 */
```

###Standard
A documentation comment block will always start with `/**` and end with `*/`.
All lines start with `*` character followed by one space before any content.

The main description will start with uppercase letter and end with a dot. All paragraphs should end with a dot as well.
The parameter and return value descriptions should start with a lowercase letter and at the end there should be no dot.

Any class, enum or function can be referenced (made a link to) with square brackets.
`[Player]` will reference a player. `[WeatherType]` will reference an enum. `[Player:GetName]` will reference a function.

Use correct indentation with documentation comments
```c++
/**
 * Correct indentation.
 * @param Type paramName = defaultValue : parameter description
 * @return Type returnName : return value description
 */
```
```c++
/**
* Invalid indentation.
* @param Type paramName = defaultValue : parameter description
* @return Type returnName : return value description
*/
```

###Markdown
You can use [markdown](http://pythonhosted.org//Markdown/) in your descriptions.
For syntax see http://daringfireball.net/projects/markdown/syntax and http://pythonhosted.org//Markdown/#differences
```
/**
 * Description.
 *
 * * list item
 * * list item
 * * list item
 *
 * <pre>
 * codeblock
 * </pre>
 *
 * `code line`
 *
 * *italic*
 * **bold**
 */
```
Produces<br/>
Description.

* list item
* list item
* list item

<pre>
codeblock
</pre>

`code line`

*italic*
**bold**
