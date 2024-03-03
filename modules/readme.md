This directory is used for custom C modules. Quick guide below:

- Create a subdirectory with your module name.
- Add your module files (.c, .h etc).
- Run cmake, this will automatically add a new project which compiles the appropriate .dll or .so file.
- Place the .dll or .so file inside your lua_scripts directory.
- Use "require modulename" in whichever script you use the module.