# ![logo](https://raw.githubusercontent.com/azerothcore/azerothcore.github.io/master/images/logo-github.png) AzerothCore
## mod-LuaEngine
- Latest build status with azerothcore: [![Build Status](https://github.com/azerothcore/mod-eluna-lua-engine/workflows/core-build/badge.svg?branch=master&event=push)](https://github.com/azerothcore/mod-eluna-lua-engine)

[english](README.md) | [中文说明](README_CN.md) | [Español](README_ES.md)

a Eluna module for AzerothCore.

How to install:

1. download or clone this module:  
>   [download zip file.](https://github.com/azerothcore/mod-eluna-lua-engine/archive/master.zip)  
>   or clone `git clone https://github.com/azerothcore/mod-eluna-lua-engine.git`  
2. Put it in the modules folder of the Azerothcore.  
3. download or clone the ELUNA core file:  
>   [download zip file.](https://github.com/ElunaLuaEngine/Eluna/archive/master.zip)  
>   or clone `git clone https://github.com/ElunaLuaEngine/Eluna.git .`  
4. Put it in the lua module folder:mod-LuaEngine/LuaEngine. (If you downloaded the zip-file you'll want to move all the files inside the `Eluna-master` folder into the `mod-eluna-lua-engine/LuaEngine` folder. `LuaEngine.h` needs to be directly under `mod-eluna-lua-engine/LuaEngine` without any extra sub-folders.)
5. cmake again  
6. rebuild. 

Eluna API : 
[http://elunaluaengine.github.io/](http://elunaluaengine.github.io/)
