# mod-LuaEngine
azerothcore 的 eluna 模块


Not sure:
src\server\game\Maps\MapInstanced.cpp
```
#ifdef ELUNA
    sEluna->FreeInstanceId(instanceId);
#endif
```
Eluna API changes:
OnConfigLoad(bool reload) => OnConfigLoad(bool reload, bool isBefore)


No Settings related to eluna are added in the <worldserver.conf> .
No configuration files are added to the module.

----------------------------------------------------------
写英文老费劲了.原谅我英文水平差.没办法..天生的.
有木有英语帝翻译一下

折腾这个az+eluna,有几个地方是需要注意的,如何你要使用的话

1.src\server\game\Maps\MapInstanced.cpp
```
#ifdef ELUNA
    sEluna->FreeInstanceId(instanceId);
#endif
```
这一句我不确定加的是不是正确的

2.改了eluna的一个api
```
OnConfigLoad(bool reload) => OnConfigLoad(bool reload, bool isBefore)
```
为了兼容az的OnBeforeConfigLoad和OnAfterConfigLoad

3.没有把这部分加到配置文件<worldserver.conf>里,因为打算把这部分写到模块的配置文件里,目前没有弄.
```
###################################################################################################
#  ELUNA SETTINGS
#
#   Eluna.Enabled
#       Description: Enable or disable Eluna LuaEngine
#       Default:    true  - (enabled)
#                   false - (disabled)
#
#   Eluna.TraceBack
#       Description: Sets whether to use debug.traceback function on a lua error or not.
#                    Notice that you can redefine the function.
#       Default:    false - (use default error output)
#                   true  - (use debug.traceback function)
#
#   Eluna.ScriptPath
#       Description: Sets the location of the script folder to load scripts from
#                    The path can be relative or absolute.
#       Default:    "lua_scripts"
#

Eluna.Enabled = true
Eluna.TraceBack = false
Eluna.ScriptPath = "lua_scripts"
```
4.据说最近的eluna可以去掉单线程限制,目前我还没去掉,如果需要去掉的话
src\server\game\Maps\MapManager.cpp
```
#ifdef ELUNA
    if (num_threads > 1)
    {
        // Force 1 thread for Eluna as lua is single threaded. By default thread count is 1
        // This should allow us not to use mutex locks
        ELUNA_LOG_ERROR("MAP:Map update threads set to %i, when Eluna only allows 1, changing to 1", num_threads);
        num_threads = 1;
    }
#endif
```
把这段去掉



