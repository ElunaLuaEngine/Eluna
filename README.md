# ![logo](https://raw.githubusercontent.com/azerothcore/azerothcore.github.io/master/images/logo-github.png) mod-eluna-lua-engine for AzerothCore
- Latest build status with azerothcore: [![Build Status](https://github.com/azerothcore/mod-eluna-lua-engine/workflows/core-build/badge.svg?branch=master&event=push)](https://github.com/azerothcore/mod-eluna-lua-engine)

[english](README.md) | [中文说明](README_CN.md) | [Español](README_ES.md)

An [Eluna](https://github.com/ElunaLuaEngine/Eluna) module for AzerothCore.

## How to install:

### 1) Download the sources

You can get the sources using git.

#### download with git

1. open a terminal inside your `azerothcore-wotlk` folder
2. go inside the **modules** folder: `cd modules`
3. download the module sources using:
```
git clone https://github.com/azerothcore/mod-eluna-lua-engine.git
```
4. go inside the **mod-eluna-lua-engine** folder: `cd mod-eluna-lua-engine`
5. download the Eluna sources using `git submodule update --init`

Optional: if you need to update Eluna to the latest version, you can `cd src` and `cd LuaEngine` and run `git pull` from there.


### 2) Build

You need to run the cmake again and and rebuild the project.

Eluna API for AC: 
[https://www.azerothcore.org/pages/eluna/index.html](https://www.azerothcore.org/pages/eluna/index.html)

## How to update the Eluna version (for project mainteners)

1) `cd` into `mod-eluna-lua-engine`
2) `git checkout master`
3) cd `LuaEngine`
4) `git checkout master`
5) `git pull`
6) `cd ..` so you get back to `mod-eluna-lua-engine`
7) `git checkout -b some-new-unique-branch-name`
8) `git add LuaEngine`
9) `git commit -m "feat: update Eluna version"`
10) `git push`
11) The terminal will tell you something like `fatal: The current branch some-new-unique-branch-name has no upstream branch.` and suggest the command to use, for example: `git push --set-upstream origin some-new-unique-branch-name`
12) Open [the repo on Github](https://github.com/azerothcore/mod-eluna-lua-engine) and create a new PR
