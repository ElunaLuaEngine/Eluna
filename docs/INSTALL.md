#Installation

0. Since TrinityCore uses boost and our file loader uses boost file system, you need boost filesystem. On windows this should be available with the default package, __but on linux__ you may need to install it: `sudo apt-get install libboost-filesystem-dev`

1. Get the core:<br/>
[![Build Status](https://travis-ci.org/ElunaLuaEngine/ElunaTrinityWotlk.png?branch=master)](https://travis-ci.org/ElunaLuaEngine/ElunaTrinityWotlk) [Eluna TrinityCore WotLK](https://github.com/ElunaLuaEngine/ElunaTrinityWotlk)<br />
[![Build Status](https://travis-ci.org/ElunaLuaEngine/ElunaTrinityCata.png?branch=master)](https://travis-ci.org/ElunaLuaEngine/ElunaTrinityCata) [Eluna TrinityCore Cataclysm](https://github.com/ElunaLuaEngine/ElunaTrinityCata)<br />
<br />
[![Build Status](https://travis-ci.org/ElunaLuaEngine/ElunaMangosClassic.png?branch=master)](https://travis-ci.org/ElunaLuaEngine/ElunaMangosClassic) [Eluna cMaNGOS Classic](https://github.com/ElunaLuaEngine/ElunaMangosClassic)<br />
[![Build Status](https://travis-ci.org/ElunaLuaEngine/ElunaMangosTbc.png?branch=master)](https://travis-ci.org/ElunaLuaEngine/ElunaMangosTbc) [Eluna cMaNGOS TBC](https://github.com/ElunaLuaEngine/ElunaMangosTbc)<br />
[![Build Status](https://travis-ci.org/ElunaLuaEngine/ElunaMangosWotlk.png?branch=master)](https://travis-ci.org/ElunaLuaEngine/ElunaMangosWotlk) [Eluna cMaNGOS WotLK](https://github.com/ElunaLuaEngine/ElunaMangosWotlk)

2. Open `git bash` and do<br />
`git submodule init`<br />
`git submodule update`<br />
<br />
If you really dont get how to use git bash (and do try!), you can navigate to the LuaEngine folder and clone [the eluna repository](https://github.com/ElunaLuaEngine/Eluna) there. This is not suggested though.

3. Compile the core normally:<br />
[TrinityCore](http://collab.kpsn.org/display/tc/TrinityCore+Home)<br />
[cMaNGOS](https://github.com/cmangos/issues/wiki/Installation-Instructions)

#Updating
1. When updating you should take up the `commit hash` you are on, just in case.
You can get it from git with `git log` for example.
You should take note what are the newest SQL updates in `sql/updates/*` folders.
2. Use `git pull` to get the newest source changes.
3. Then use `git submodule init` `git submodule update` to update Eluna from github.
4. Try compiling and if you encounter errors, report to [support](https://github.com/ElunaLuaEngine/Eluna#links) or [issues](https://github.com/ElunaLuaEngine/Eluna/issues).
You can revert back to the old sources by using `git reset --hard 000000` `git submodule update`, where 000000 is the `commit hash`.
5. If the compiling was successful, you should update your database if needed.
You can do this by running all **new** SQL files in `sql/updates/*`.
You need to see your notes from before pulling the updates or you can use the old commit hash to see on github what were the last files you ran.
An easy way is to just look at the created/modified date on the files.
