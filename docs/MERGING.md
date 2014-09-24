#Merging Eluna with MaNGOS
Eluna is already merged with official MaNGOS by default

#Merging Eluna with TC
```
git clone --recursive https://github.com/ElunaLuaEngine/ElunaTrinityWotlk.git
cd ElunaTrinityWotlk
git pull https://github.com/TrinityCore/TrinityCore.git
```
Steps explained:

1. clone Eluna recursively
 * This will automatically pull the submodule (Eluna repo)
2. go to the source folder
3. pull (fetch and merge) TC with the Eluna source.
 * Adding Eluna core repository as a remote is recommended
