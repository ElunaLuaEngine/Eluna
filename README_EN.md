# mod-LuaEngine
[chinese](README.md) | english

a Eluna module for AzerothCore

To make Eluna compatible with Azerothcore.one lua Api has been changed.
```
OnConfigLoad(bool reload) => OnConfigLoad(bool reload, bool isBefore)
```

How to install:
* download this module:[download](https://github.com/AyaseCore/mod-LuaEngine/archive/master.zip)
* unzip this module.Put it in the modules folder of the Azerothcore.
* download ELUNA core file:[download](https://github.com/AyaseCore/Eluna/archive/ElunaAzerothWotlk.zip)
* unzip,Put it in the lua module folder:mod-LuaEngine/LuaEngine
* cmake again
* rebuild.
