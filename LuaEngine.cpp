/*
* Copyright (C) 2010 - 2014 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#include "HookMgr.h"
#include "LuaEngine.h"
#include "ElunaBinding.h"
#include "ElunaEventMgr.h"
#include "ElunaIncludes.h"
#include "ElunaTemplate.h"
#include "ElunaUtility.h"

#ifdef USING_BOOST
#include <boost/filesystem.hpp>
#else
#include <ace/ACE.h>
#include <ace/Dirent.h>
#include <ace/OS_NS_sys_stat.h>
#endif

extern "C"
{
#include "lualib.h"
#include "lauxlib.h"
};

Eluna::ScriptList Eluna::lua_scripts;
Eluna::ScriptList Eluna::lua_extensions;
std::string Eluna::lua_folderpath;
std::string Eluna::lua_requirepath;
Eluna* Eluna::GEluna = NULL;
bool Eluna::reload = false;
bool Eluna::initialized = false;

extern void RegisterFunctions(Eluna* E);

void Eluna::Initialize()
{
    ASSERT(!initialized);

    uint32 oldMSTime = ElunaUtil::GetCurrTime();

    lua_scripts.clear();
    lua_extensions.clear();

    lua_folderpath = eConfigMgr->GetStringDefault("Eluna.ScriptPath", "lua_scripts");
#if PLATFORM == PLATFORM_UNIX || PLATFORM == PLATFORM_APPLE
    if (lua_folderpath[0] == '~')
        if (const char* home = getenv("HOME"))
            lua_folderpath.replace(0, 1, home);
#endif
    ELUNA_LOG_INFO("[Eluna]: Searching scripts from `%s`", lua_folderpath.c_str());
    lua_requirepath = "";
    GetScripts(lua_folderpath);
    lua_requirepath.erase(lua_requirepath.end() - 1);

    ELUNA_LOG_DEBUG("[Eluna]: Loaded %u scripts in %u ms", uint32(lua_scripts.size() + lua_extensions.size()), ElunaUtil::GetTimeDiff(oldMSTime));

    initialized = true;

    // Create global eluna
    GEluna = new Eluna();
}

void Eluna::Uninitialize()
{
    ASSERT(initialized);

    delete GEluna;
    GEluna = NULL;

    lua_scripts.clear();
    lua_extensions.clear();

    initialized = false;
}

void Eluna::ReloadEluna()
{
    eWorld->SendServerMessage(SERVER_MSG_STRING, "Reloading Eluna...");

    EventMgr::ProcessorSet oldProcessors;
    {
        EventMgr::ReadGuard lock(sEluna->eventMgr->GetLock());
        oldProcessors = sEluna->eventMgr->processors;
    }
    Uninitialize();
    Initialize();
    {
        EventMgr::WriteGuard lock(sEluna->eventMgr->GetLock());
        sEluna->eventMgr->processors.insert(oldProcessors.begin(), oldProcessors.end());
    }

    // in multithread foreach: run scripts
    sEluna->RunScripts();

#ifdef TRINITY
    // Re initialize creature AI restoring C++ AI or applying lua AI
    {
        HashMapHolder<Creature>::MapType const m = ObjectAccessor::GetCreatures();
        for (HashMapHolder<Creature>::MapType::const_iterator iter = m.begin(); iter != m.end(); ++iter)
            if (iter->second->IsInWorld())
                iter->second->AIM_Initialize();
    }
#endif

    reload = false;
}

Eluna::Eluna() :
L(luaL_newstate()),

event_level(0),

eventMgr(NULL),

ServerEventBindings(new EventBind<HookMgr::ServerEvents>("ServerEvents", *this)),
PlayerEventBindings(new EventBind<HookMgr::PlayerEvents>("PlayerEvents", *this)),
GuildEventBindings(new EventBind<HookMgr::GuildEvents>("GuildEvents", *this)),
GroupEventBindings(new EventBind<HookMgr::GroupEvents>("GroupEvents", *this)),
VehicleEventBindings(new EventBind<HookMgr::VehicleEvents>("VehicleEvents", *this)),
BGEventBindings(new EventBind<HookMgr::BGEvents>("BGEvents", *this)),

PacketEventBindings(new EntryBind<HookMgr::PacketEvents>("PacketEvents", *this)),
CreatureEventBindings(new EntryBind<HookMgr::CreatureEvents>("CreatureEvents", *this)),
CreatureGossipBindings(new EntryBind<HookMgr::GossipEvents>("GossipEvents (creature)", *this)),
GameObjectEventBindings(new EntryBind<HookMgr::GameObjectEvents>("GameObjectEvents", *this)),
GameObjectGossipBindings(new EntryBind<HookMgr::GossipEvents>("GossipEvents (gameobject)", *this)),
ItemEventBindings(new EntryBind<HookMgr::ItemEvents>("ItemEvents", *this)),
ItemGossipBindings(new EntryBind<HookMgr::GossipEvents>("GossipEvents (item)", *this)),
playerGossipBindings(new EntryBind<HookMgr::GossipEvents>("GossipEvents (player)", *this))
{
    // open base lua
    luaL_openlibs(L);
    RegisterFunctions(this);

    // Create hidden table with weak values
    lua_newtable(L);
    lua_newtable(L);
    lua_pushstring(L, "v");
    lua_setfield(L, -2, "__mode");
    lua_setmetatable(L, -2);
    lua_setglobal(L, ELUNA_OBJECT_STORE);

    // Set lua require folder paths (scripts folder structure)
    lua_getglobal(L, "package");
    lua_pushstring(L, lua_requirepath.c_str());
    lua_setfield(L, -2, "path");
    lua_pushstring(L, ""); // erase cpath
    lua_setfield(L, -2, "cpath");
    lua_pop(L, 1);

    // Replace this with map insert if making multithread version
    //

    // Set event manager. Must be after setting sEluna
    // on multithread have a map of state pointers and here insert this pointer to the map and then save a pointer of that pointer to the EventMgr
    eventMgr = new EventMgr(&Eluna::GEluna);
}

Eluna::~Eluna()
{
    OnLuaStateClose();

    delete eventMgr;
    eventMgr = NULL;

    // Replace this with map remove if making multithread version
    //

    delete ServerEventBindings;
    delete PlayerEventBindings;
    delete GuildEventBindings;
    delete GroupEventBindings;
    delete VehicleEventBindings;

    delete PacketEventBindings;
    delete CreatureEventBindings;
    delete CreatureGossipBindings;
    delete GameObjectEventBindings;
    delete GameObjectGossipBindings;
    delete ItemEventBindings;
    delete ItemGossipBindings;
    delete playerGossipBindings;
    delete BGEventBindings;

    ServerEventBindings = NULL;
    PlayerEventBindings = NULL;
    GuildEventBindings = NULL;
    GroupEventBindings = NULL;
    VehicleEventBindings = NULL;

    PacketEventBindings = NULL;
    CreatureEventBindings = NULL;
    CreatureGossipBindings = NULL;
    GameObjectEventBindings = NULL;
    GameObjectGossipBindings = NULL;
    ItemEventBindings = NULL;
    ItemGossipBindings = NULL;
    playerGossipBindings = NULL;
    BGEventBindings = NULL;

    // Must close lua state after deleting stores and mgr
    lua_close(L);
}

void Eluna::AddScriptPath(std::string filename, std::string fullpath)
{
    ELUNA_LOG_DEBUG("[Eluna]: AddScriptPath Checking file `%s`", fullpath.c_str());

    // split file name
    std::size_t extDot = filename.find_last_of('.');
    if (extDot == std::string::npos)
        return;
    std::string ext = filename.substr(extDot);
    filename = filename.substr(0, extDot);

    // check extension and add path to scripts to load
    if (ext != ".lua" && ext != ".dll" && ext != ".ext")
        return;
    bool extension = ext == ".ext";

    LuaScript script;
    script.fileext = ext;
    script.filename = filename;
    script.filepath = fullpath;
    script.modulepath = fullpath.substr(0, fullpath.length() - filename.length() - ext.length());
    if (extension)
        lua_extensions.push_back(script);
    else
        lua_scripts.push_back(script);
    ELUNA_LOG_DEBUG("[Eluna]: AddScriptPath add path `%s`", fullpath.c_str());
}

// Finds lua script files from given path (including subdirectories) and pushes them to scripts
void Eluna::GetScripts(std::string path)
{
    ELUNA_LOG_DEBUG("[Eluna]: GetScripts from path `%s`", path.c_str());

#ifdef USING_BOOST
    boost::filesystem::path someDir(path);
    boost::filesystem::directory_iterator end_iter;

    if (boost::filesystem::exists(someDir) && boost::filesystem::is_directory(someDir))
    {
        lua_requirepath +=
            path + "/?;" +
            path + "/?.lua;" +
            path + "/?.dll;" +
            path + "/?.so;";

        for (boost::filesystem::directory_iterator dir_iter(someDir); dir_iter != end_iter; ++dir_iter)
        {
            std::string fullpath = dir_iter->path().generic_string();

            // Check if file is hidden
#ifdef WIN32
            DWORD dwAttrib = GetFileAttributes(fullpath.c_str());
            if (dwAttrib != INVALID_FILE_ATTRIBUTES && (dwAttrib & FILE_ATTRIBUTE_HIDDEN))
                continue;
#endif
#ifdef UNIX
            const char* name = dir_iter->path().filename().generic_string().c_str();
            if (name != ".." || name != "." || name[0] == '.')
                continue;
#endif

            // load subfolder
            if (boost::filesystem::is_directory(dir_iter->status()))
            {
                GetScripts(fullpath);
                continue;
            }

            if (boost::filesystem::is_regular_file(dir_iter->status()))
            {
                // was file, try add
                std::string filename = dir_iter->path().filename().generic_string();
                AddScriptPath(filename, fullpath);
            }
        }
    }
#else
    ACE_Dirent dir;
    if (dir.open(path.c_str()) == -1) // Error opening directory, return
        return;

    lua_requirepath +=
        path + "/?;" +
        path + "/?.lua;" +
        path + "/?.dll;" +
        path + "/?.so;";

    ACE_DIRENT *directory = 0;
    while ((directory = dir.read()))
    {
        // Skip the ".." and "." files.
        if (ACE::isdotdir(directory->d_name))
            continue;

        std::string fullpath = path + "/" + directory->d_name;

        // Check if file is hidden
#ifdef WIN32
        DWORD dwAttrib = GetFileAttributes(fullpath.c_str());
        if (dwAttrib != INVALID_FILE_ATTRIBUTES && (dwAttrib & FILE_ATTRIBUTE_HIDDEN))
            continue;
#endif
#ifdef UNIX
        const char* name = directory->d_name.c_str();
        if (name != ".." || name != "." || name[0] == '.')
            continue;
#endif

        ACE_stat stat_buf;
        if (ACE_OS::lstat(fullpath.c_str(), &stat_buf) == -1)
            continue;

        // load subfolder
        if ((stat_buf.st_mode & S_IFMT) == (S_IFDIR))
        {
            GetScripts(fullpath);
            continue;
        }

        // was file, try add
        std::string filename = directory->d_name;
        AddScriptPath(filename, fullpath);
    }
#endif
}

static bool ScriptPathComparator(const LuaScript& first, const LuaScript& second)
{
    return first.filepath.compare(second.filepath) < 0;
}

void Eluna::RunScripts()
{
    uint32 oldMSTime = ElunaUtil::GetCurrTime();
    uint32 count = 0;

    ScriptList scripts;
    lua_extensions.sort(ScriptPathComparator);
    lua_scripts.sort(ScriptPathComparator);
    scripts.insert(scripts.end(), lua_extensions.begin(), lua_extensions.end());
    scripts.insert(scripts.end(), lua_scripts.begin(), lua_scripts.end());

    UNORDERED_MAP<std::string, std::string> loaded; // filename, path

    lua_getglobal(L, "package");
    luaL_getsubtable(L, -1, "loaded");
    int modules = lua_gettop(L);
    for (ScriptList::const_iterator it = scripts.begin(); it != scripts.end(); ++it)
    {
        // Check that no duplicate names exist
        if (loaded.find(it->filename) != loaded.end())
        {
            ELUNA_LOG_ERROR("[Eluna]: Error loading `%s`. File with same name already loaded from `%s`, rename either file", it->filepath.c_str(), loaded[it->filename].c_str());
            continue;
        }
        loaded[it->filename] = it->filepath;

        lua_getfield(L, modules, it->filename.c_str());
        if (!lua_isnoneornil(L, -1))
        {
            lua_pop(L, 1);
            ELUNA_LOG_DEBUG("[Eluna]: `%s` was already loaded or required", it->filepath.c_str());
            continue;
        }
        lua_pop(L, 1);
        if (!luaL_loadfile(L, it->filepath.c_str()) && !lua_pcall(L, 0, 1, 0))
        {
            if (!lua_toboolean(L, -1))
            {
                lua_pop(L, 1);
                Push(L, true);
            }
            lua_setfield(L, modules, it->filename.c_str());

            // successfully loaded and ran file
            ELUNA_LOG_DEBUG("[Eluna]: Successfully loaded `%s`", it->filepath.c_str());
            ++count;
            continue;
        }
        ELUNA_LOG_ERROR("[Eluna]: Error loading `%s`", it->filepath.c_str());
        report(L);
    }
    lua_pop(L, 2);

    ELUNA_LOG_INFO("[Eluna]: Executed %u Lua scripts in %u ms", count, ElunaUtil::GetTimeDiff(oldMSTime));

    OnLuaStateOpen();
}

void Eluna::InvalidateObjects()
{
    lua_getglobal(L, ELUNA_OBJECT_STORE);
    ASSERT(lua_istable(L, -1));

    lua_pushnil(L);
    while (lua_next(L, -2))
    {
        if (ElunaObject* elunaObj = CHECKOBJ<ElunaObject>(L, -1, false))
            elunaObj->Invalidate();
        lua_pop(L, 1);
    }
    lua_pop(L, 1);
}

void Eluna::report(lua_State* L)
{
    const char* msg = lua_tostring(L, -1);
    ELUNA_LOG_ERROR("%s", msg);
    lua_pop(L, 1);
}

void Eluna::ExecuteCall(int params, int res)
{
    int top = lua_gettop(L);
    int type = lua_type(L, top - params);

    if (type != LUA_TFUNCTION)
    {
        lua_pop(L, params + 1);  // Cleanup the stack.
        ELUNA_LOG_ERROR("[Eluna]: Cannot execute call: registered value is %s, not a function.", lua_typename(L, type));
        return;
    }

    ++event_level;
    if (lua_pcall(L, params, res, 0))
        report(L);
    --event_level;
}

void Eluna::Push(lua_State* L)
{
    lua_pushnil(L);
}
void Eluna::Push(lua_State* L, const uint64 l)
{
    std::ostringstream ss;
    ss << l;
    Push(L, ss.str());
}
void Eluna::Push(lua_State* L, const int64 l)
{
    std::ostringstream ss;
    ss << l;
    Push(L, ss.str());
}
void Eluna::Push(lua_State* L, const uint32 u)
{
    lua_pushunsigned(L, u);
}
void Eluna::Push(lua_State* L, const int32 i)
{
    lua_pushinteger(L, i);
}
void Eluna::Push(lua_State* L, const double d)
{
    lua_pushnumber(L, d);
}
void Eluna::Push(lua_State* L, const float f)
{
    lua_pushnumber(L, f);
}
void Eluna::Push(lua_State* L, const bool b)
{
    lua_pushboolean(L, b);
}
void Eluna::Push(lua_State* L, const std::string str)
{
    lua_pushstring(L, str.c_str());
}
void Eluna::Push(lua_State* L, const char* str)
{
    lua_pushstring(L, str);
}
void Eluna::Push(lua_State* L, Pet const* pet)
{
    Push(L, pet->ToCreature());
}
void Eluna::Push(lua_State* L, TempSummon const* summon)
{
    Push(L, summon->ToCreature());
}
void Eluna::Push(lua_State* L, Unit const* unit)
{
    if (!unit)
    {
        Push(L);
        return;
    }
    switch (unit->GetTypeId())
    {
        case TYPEID_UNIT:
            Push(L, unit->ToCreature());
            break;
        case TYPEID_PLAYER:
            Push(L, unit->ToPlayer());
            break;
        default:
            ElunaTemplate<Unit>::push(L, unit);
    }
}
void Eluna::Push(lua_State* L, WorldObject const* obj)
{
    if (!obj)
    {
        Push(L);
        return;
    }
    switch (obj->GetTypeId())
    {
        case TYPEID_UNIT:
            Push(L, obj->ToCreature());
            break;
        case TYPEID_PLAYER:
            Push(L, obj->ToPlayer());
            break;
        case TYPEID_GAMEOBJECT:
            Push(L, obj->ToGameObject());
            break;
        case TYPEID_CORPSE:
            Push(L, obj->ToCorpse());
            break;
        default:
            ElunaTemplate<WorldObject>::push(L, obj);
    }
}
void Eluna::Push(lua_State* L, Object const* obj)
{
    if (!obj)
    {
        Push(L);
        return;
    }
    switch (obj->GetTypeId())
    {
        case TYPEID_UNIT:
            Push(L, obj->ToCreature());
            break;
        case TYPEID_PLAYER:
            Push(L, obj->ToPlayer());
            break;
        case TYPEID_GAMEOBJECT:
            Push(L, obj->ToGameObject());
            break;
        case TYPEID_CORPSE:
            Push(L, obj->ToCorpse());
            break;
        default:
            ElunaTemplate<Object>::push(L, obj);
    }
}

static int32 CheckIntegerRange(lua_State* L, int narg, int32 min, int32 max)
{
    int64 value = static_cast<int64>(luaL_checknumber(L, narg));
    char error_buffer[64];

    if (value > max)
    {
        snprintf(error_buffer, 64, "value must be less than or equal to %d", max);
        return luaL_argerror(L, narg, error_buffer);
    }

    if (value < min)
    {
        snprintf(error_buffer, 64, "value must be greater than or equal to %d", min);
        return luaL_argerror(L, narg, error_buffer);
    }

    return static_cast<int32>(value);
}

static uint32 CheckUnsignedRange(lua_State* L, int narg, uint32 max)
{
    int64 value = static_cast<int64>(luaL_checknumber(L, narg));
    char error_buffer[64];

    if (value < 0)
        return luaL_argerror(L, narg, "value must be greater than or equal to 0");

    if (value > max)
    {
        snprintf(error_buffer, 64, "value must be less than or equal to %u", max);
        return luaL_argerror(L, narg, error_buffer);
    }

    return static_cast<uint32>(value);
}

template<> bool Eluna::CHECKVAL<bool>(lua_State* L, int narg)
{
    return lua_toboolean(L, narg) != 0;
}
template<> float Eluna::CHECKVAL<float>(lua_State* L, int narg)
{
    return luaL_checknumber(L, narg);
}
template<> double Eluna::CHECKVAL<double>(lua_State* L, int narg)
{
    return luaL_checknumber(L, narg);
}
template<> int8 Eluna::CHECKVAL<int8>(lua_State* L, int narg)
{
    return CheckIntegerRange(L, narg, SCHAR_MIN, SCHAR_MAX);
}
template<> uint8 Eluna::CHECKVAL<uint8>(lua_State* L, int narg)
{
    return CheckUnsignedRange(L, narg, UCHAR_MAX);
}
template<> int16 Eluna::CHECKVAL<int16>(lua_State* L, int narg)
{
    return CheckIntegerRange(L, narg, SHRT_MIN, SHRT_MAX);
}
template<> uint16 Eluna::CHECKVAL<uint16>(lua_State* L, int narg)
{
    return CheckUnsignedRange(L, narg, USHRT_MAX);
}
template<> int32 Eluna::CHECKVAL<int32>(lua_State* L, int narg)
{
    return CheckIntegerRange(L, narg, INT_MIN, INT_MAX);
}
template<> uint32 Eluna::CHECKVAL<uint32>(lua_State* L, int narg)
{
    return CheckUnsignedRange(L, narg, UINT_MAX);
}
template<> const char* Eluna::CHECKVAL<const char*>(lua_State* L, int narg)
{
    return luaL_checkstring(L, narg);
}
template<> std::string Eluna::CHECKVAL<std::string>(lua_State* L, int narg)
{
    return luaL_checkstring(L, narg);
}
template<> int64 Eluna::CHECKVAL<int64>(lua_State* L, int narg)
{
    const char* c_str = CHECKVAL<const char*>(L, narg, NULL);
    if (!c_str)
        return luaL_argerror(L, narg, "int64 (as string) expected");

    int64 l = 0;
    int parsed_count = sscanf(c_str, SI64FMTD, &l);
    if (parsed_count != 1)
        return luaL_argerror(L, narg, "int64 (as string) could not be converted");

    return l;
}
template<> uint64 Eluna::CHECKVAL<uint64>(lua_State* L, int narg)
{
    const char* c_str = CHECKVAL<const char*>(L, narg, NULL);
    if (!c_str)
        return luaL_argerror(L, narg, "uint64 (as string) expected");

    uint64 l = 0;
    int parsed_count = sscanf(c_str, UI64FMTD, &l);
    if (parsed_count != 1)
        return luaL_argerror(L, narg, "uint64 (as string) could not be converted");

    return l;
}

#define TEST_OBJ(T, O, R, F)\
{\
    if (!O || !O->F())\
    {\
        if (R)\
        {\
            std::string errmsg(ElunaTemplate<T>::tname);\
            errmsg += " expected";\
            luaL_argerror(L, narg, errmsg.c_str());\
        }\
        return NULL;\
    }\
    return O->F();\
}

template<> Unit* Eluna::CHECKOBJ<Unit>(lua_State* L, int narg, bool error)
{
    WorldObject* obj = CHECKOBJ<WorldObject>(L, narg, false);
    TEST_OBJ(Unit, obj, error, ToUnit);
}
template<> Player* Eluna::CHECKOBJ<Player>(lua_State* L, int narg, bool error)
{
    WorldObject* obj = CHECKOBJ<WorldObject>(L, narg, false);
    TEST_OBJ(Player, obj, error, ToPlayer);
}
template<> Creature* Eluna::CHECKOBJ<Creature>(lua_State* L, int narg, bool error)
{
    WorldObject* obj = CHECKOBJ<WorldObject>(L, narg, false);
    TEST_OBJ(Creature, obj, error, ToCreature);
}
template<> GameObject* Eluna::CHECKOBJ<GameObject>(lua_State* L, int narg, bool error)
{
    WorldObject* obj = CHECKOBJ<WorldObject>(L, narg, false);
    TEST_OBJ(GameObject, obj, error, ToGameObject);
}
template<> Corpse* Eluna::CHECKOBJ<Corpse>(lua_State* L, int narg, bool error)
{
    WorldObject* obj = CHECKOBJ<WorldObject>(L, narg, false);
    TEST_OBJ(Corpse, obj, error, ToCorpse);
}
#undef TEST_OBJ

template<> ElunaObject* Eluna::CHECKOBJ<ElunaObject>(lua_State* L, int narg, bool error)
{
    ElunaObject** ptrHold = static_cast<ElunaObject**>(lua_touserdata(L, narg));
    if (!ptrHold)
    {
        if (error)
        {
            char buff[256];
            snprintf(buff, 256, "Error fetching object index %i", narg);
            luaL_argerror(L, narg, buff);
        }
        return NULL;
    }
    return *ptrHold;
}

// Saves the function reference ID given to the register type's store for given entry under the given event
void Eluna::Register(uint8 regtype, uint32 id, uint32 evt, int functionRef)
{
    switch (regtype)
    {
        case HookMgr::REGTYPE_SERVER:
            if (evt < HookMgr::SERVER_EVENT_COUNT)
            {
                ServerEventBindings->Insert(evt, functionRef);
                return;
            }
            break;

        case HookMgr::REGTYPE_PLAYER:
            if (evt < HookMgr::PLAYER_EVENT_COUNT)
            {
                PlayerEventBindings->Insert(evt, functionRef);
                return;
            }
            break;

        case HookMgr::REGTYPE_GUILD:
            if (evt < HookMgr::GUILD_EVENT_COUNT)
            {
                GuildEventBindings->Insert(evt, functionRef);
                return;
            }
            break;

        case HookMgr::REGTYPE_GROUP:
            if (evt < HookMgr::GROUP_EVENT_COUNT)
            {
                GroupEventBindings->Insert(evt, functionRef);
                return;
            }
            break;

        case HookMgr::REGTYPE_VEHICLE:
            if (evt < HookMgr::VEHICLE_EVENT_COUNT)
            {
                VehicleEventBindings->Insert(evt, functionRef);
                return;
            }
            break;

        case HookMgr::REGTYPE_BG:
            if (evt < HookMgr::BG_EVENT_COUNT)
            {
                BGEventBindings->Insert(evt, functionRef);
                return;
            }
            break;

        case HookMgr::REGTYPE_PACKET:
            if (evt < HookMgr::PACKET_EVENT_COUNT)
            {
                if (id >= NUM_MSG_TYPES)
                {
                    luaL_unref(L, LUA_REGISTRYINDEX, functionRef);
                    luaL_error(L, "Couldn't find a creature with (ID: %d)!", id);
                    return;
                }

                PacketEventBindings->Insert(id, evt, functionRef);
                return;
            }
            break;

        case HookMgr::REGTYPE_CREATURE:
            if (evt < HookMgr::CREATURE_EVENT_COUNT)
            {
                if (!eObjectMgr->GetCreatureTemplate(id))
                {
                    luaL_unref(L, LUA_REGISTRYINDEX, functionRef);
                    luaL_error(L, "Couldn't find a creature with (ID: %d)!", id);
                    return;
                }

                CreatureEventBindings->Insert(id, evt, functionRef);
                return;
            }
            break;

        case HookMgr::REGTYPE_CREATURE_GOSSIP:
            if (evt < HookMgr::GOSSIP_EVENT_COUNT)
            {
                if (!eObjectMgr->GetCreatureTemplate(id))
                {
                    luaL_unref(L, LUA_REGISTRYINDEX, functionRef);
                    luaL_error(L, "Couldn't find a creature with (ID: %d)!", id);
                    return;
                }

                CreatureGossipBindings->Insert(id, evt, functionRef);
                return;
            }
            break;

        case HookMgr::REGTYPE_GAMEOBJECT:
            if (evt < HookMgr::GAMEOBJECT_EVENT_COUNT)
            {
                if (!eObjectMgr->GetGameObjectTemplate(id))
                {
                    luaL_unref(L, LUA_REGISTRYINDEX, functionRef);
                    luaL_error(L, "Couldn't find a gameobject with (ID: %d)!", id);
                    return;
                }

                GameObjectEventBindings->Insert(id, evt, functionRef);
                return;
            }
            break;

        case HookMgr::REGTYPE_GAMEOBJECT_GOSSIP:
            if (evt < HookMgr::GOSSIP_EVENT_COUNT)
            {
                if (!eObjectMgr->GetGameObjectTemplate(id))
                {
                    luaL_unref(L, LUA_REGISTRYINDEX, functionRef);
                    luaL_error(L, "Couldn't find a gameobject with (ID: %d)!", id);
                    return;
                }

                GameObjectGossipBindings->Insert(id, evt, functionRef);
                return;
            }
            break;

        case HookMgr::REGTYPE_ITEM:
            if (evt < HookMgr::ITEM_EVENT_COUNT)
            {
                if (!eObjectMgr->GetItemTemplate(id))
                {
                    luaL_unref(L, LUA_REGISTRYINDEX, functionRef);
                    luaL_error(L, "Couldn't find a item with (ID: %d)!", id);
                    return;
                }

                ItemEventBindings->Insert(id, evt, functionRef);
                return;
            }
            break;

        case HookMgr::REGTYPE_ITEM_GOSSIP:
            if (evt < HookMgr::GOSSIP_EVENT_COUNT)
            {
                if (!eObjectMgr->GetItemTemplate(id))
                {
                    luaL_unref(L, LUA_REGISTRYINDEX, functionRef);
                    luaL_error(L, "Couldn't find a item with (ID: %d)!", id);
                    return;
                }

                ItemGossipBindings->Insert(id, evt, functionRef);
                return;
            }
            break;

        case HookMgr::REGTYPE_PLAYER_GOSSIP:
            if (evt < HookMgr::GOSSIP_EVENT_COUNT)
            {
                playerGossipBindings->Insert(id, evt, functionRef);
                return;
            }
            break;
    }
    luaL_unref(L, LUA_REGISTRYINDEX, functionRef);
    luaL_error(L, "Unknown event type (regtype %d, id %d, event %d)", regtype, id, evt);
}
