#Merging
1. You should have/get the source code of TrinityCore or MaNGOS.
2. Open `git bash` in the source folder.
3. Create a remote to our Eluna core repository with `git remote add Eluna <repoaddress>`, for example for TC WoTLK it would be
`git remote add Eluna https://github.com/ElunaLuaEngine/Eluna-TC-Wotlk.git`.
4. Pull (fetch and merge) the eluna core repository to your TC or MaNGOS source with `git pull Eluna master`.
5. Open `git bash` and do
`git submodule init`
`git submodule update`
6. Compile the core normally (use cmake if needed)
