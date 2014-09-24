#Merging Eluna with MaNGOS
Eluna is already merged with official MaNGOS by default

#Merging Eluna with TC
```
git clone https://github.com/TrinityCore/TrinityCore.git
cd TrinityCore
git pull --recurse-submodules https://github.com/ElunaLuaEngine/ElunaTrinityWotlk.git
```
Steps explained:

1. clone TrinityCore
2. go to the source folder
3. pull (fetch and merge) Eluna with the source.
 * recurse-submodules will automatically pull the submodule (Eluna repo)
 * Adding Eluna core repository as a remote is recommended
