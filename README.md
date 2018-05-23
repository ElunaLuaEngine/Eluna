# mod-LuaEngine
中文|[english](README_EN.md)

一个用于AzerothCore的ELUNA模块.

为了兼容AzerothCore.更改了一个eluna的api
```
OnConfigLoad(bool reload) => OnConfigLoad(bool reload, bool isBefore)
```

如何安装:
* 下载这个模块:[download](https://github.com/AyaseCore/mod-LuaEngine/archive/master.zip)
* 解压并放到Azerothcore源码的modules文件夹中.
* 下载ELUNA的核心文件:[download](https://github.com/AyaseCore/Eluna/archive/ElunaAzerothWotlk.zip)
* 解压并放置到模块的LuaEngine文件夹中:mod-LuaEngine/LuaEngine
* 重新cmake.
* 重新生成.
