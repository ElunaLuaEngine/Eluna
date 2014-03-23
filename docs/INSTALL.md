#Installation
Get the core:<br/>
[![Build Status](https://travis-ci.org/ElunaLuaEngine/Eluna-TC-Wotlk.png?branch=master)](https://travis-ci.org/ElunaLuaEngine/Eluna-TC-Wotlk) [Eluna TrinityCore WOTLK](https://github.com/ElunaLuaEngine/Eluna-TC-Wotlk)<br />
[![Build Status](https://travis-ci.org/ElunaLuaEngine/Eluna-TC-Cata.png?branch=master)](https://travis-ci.org/ElunaLuaEngine/Eluna-TC-Cata) [Eluna TrinityCore Cataclysm](https://github.com/ElunaLuaEngine/Eluna-TC-Cata)

[![Build Status](https://travis-ci.org/eluna-dev-mangos/ElunaCoreClassic.png?branch=master)](https://travis-ci.org/eluna-dev-mangos/ElunaCoreClassic) [Eluna cMaNGOS Classic](https://github.com/eluna-dev-mangos/ElunaCoreClassic)<br />
[![Build Status](https://travis-ci.org/eluna-dev-mangos/ElunaCoreTbc.png?branch=master)](https://travis-ci.org/eluna-dev-mangos/ElunaCoreTbc) [Eluna cMaNGOS TBC](https://github.com/eluna-dev-mangos/ElunaCoreTbc)<br />
[![Build Status](https://travis-ci.org/eluna-dev-mangos/ElunaCoreWotlk.png?branch=master)](https://travis-ci.org/eluna-dev-mangos/ElunaCoreWotlk) [Eluna cMaNGOS WotLK](https://github.com/eluna-dev-mangos/ElunaCoreWotlk)

Open `git bash` and do

1. `git submodule init`
2. `git submodule update`
3. additionally to get latest Eluna code you can do `git submodule foreach git pull origin master`

Compile the core normally (use cmake if needed)

#Updating
When updating you should take up the `commit hash` you are on, just in case.
You can get it from git with `git log` for example.
You should take note what are the newest SQL updates in `sql/updates/*` folders.

1. Use `git pull` to get the newest source changes.
2. Then use `git submodule update` to update Eluna from github.
3. additionally to get latest Eluna code you can do `git submodule foreach git pull origin master`
Try compiling and if you encounter errors, report to [support](https://github.com/ElunaLuaEngine/Eluna#links) or [issues](https://github.com/ElunaLuaEngine/Eluna/issues).
You can revert back to the old sources by using `git reset --hard 000000` `git submodule update`, where 000000 is the `commit hash`.

If the compiling was successful, you should update your database if needed.
You can do this by running all **new** SQL files in `sql/updates/*`.
You need to see your notes from before pulling the updates or you can use the old commit hash to see on github what were the last files you ran.
An easy way is to just look at the created/modified date on the files.
