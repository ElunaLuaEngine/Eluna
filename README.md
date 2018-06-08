# mod-LuaEngine
 english | [chinese](README_CN.md)

a Eluna module for AzerothCore

To make Eluna compatible with Azerothcore.one lua Api has been changed.
```
OnConfigLoad(bool reload) => OnConfigLoad(bool reload, bool isBefore)
```

How to install:
* download or clone this module:  
>   [download zip file.](https://github.com/azerothcore/mod-eluna-lua-engine/archive/master.zip)  
>   clone `git clone https://github.com/azerothcore/mod-eluna-lua-engine.git`  
* Put it in the modules folder of the Azerothcore.  
* download or clone the ELUNA core file:  
>   [download zip file.](https://github.com/ElunaLuaEngine/Eluna/archive/master.zip)  
>   clone `git clone https://github.com/ElunaLuaEngine/Eluna.git`  
* Put it in the lua module folder:mod-LuaEngine/LuaEngine  
* cmake again  
* rebuild. 