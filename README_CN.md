# mod-LuaEngine
[english](README.md) | 中文

一个用于AzerothCore的ELUNA模块.

为了兼容AzerothCore.更改了一个eluna的api
```
OnConfigLoad(bool reload) => OnConfigLoad(bool reload, bool isBefore)
```

如何安装:
* 下载或者克隆这个模块:  
>   [下载zip压缩包](https://github.com/azerothcore/mod-eluna-lua-engine/archive/master.zip)  
>   或者克隆 `git clone https://github.com/azerothcore/mod-eluna-lua-engine.git`  
* 解压并放到Azerothcore源码的modules文件夹中.  
* 下载或者克隆ELUNA的核心文件:  
>   [download zip file.](https://github.com/ElunaLuaEngine/Eluna/archive/master.zip)  
>   clone `git clone https://github.com/ElunaLuaEngine/Eluna.git`  
* 解压并放置到模块的LuaEngine文件夹中:mod-LuaEngine/LuaEngine  
* 重新cmake.  
* 重新生成. 