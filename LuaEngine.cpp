/*
* Copyright (C) 2010 - 2015 Eluna Lua Engine <http://emudevs.com/>
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
// Base lua libraries
#include "lualib.h"
#include "lauxlib.h"

// Additional lua libraries
};

Eluna::ScriptList Eluna::lua_scripts;
Eluna::ScriptList Eluna::lua_extensions;
std::string Eluna::lua_folderpath;
std::string Eluna::lua_requirepath;
Eluna* Eluna::GEluna = NULL;
bool Eluna::reload = false;
bool Eluna::initialized = false;
Eluna::LockType Eluna::lock;

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
    lua_requirepath.clear();
    GetScripts(lua_folderpath);
    // Erase last ;
    if (!lua_requirepath.empty())
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
        EventMgr::ReadGuard guard(sEluna->eventMgr->GetLock());
        oldProcessors = sEluna->eventMgr->processors;
    }
    Uninitialize();
    Initialize();
    {
        EventMgr::WriteGuard guard(sEluna->eventMgr->GetLock());
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
push_counter(0),

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
playerGossipBindings(new EntryBind<HookMgr::GossipEvents>("GossipEvents (player)", *this)),

CreatureUniqueBindings(new UniqueBind<HookMgr::CreatureEvents>("CreatureEvents", *this))
{
    // open base lua libraries
    luaL_openlibs(L);

    // open additional lua libraries

    // Register methods and functions
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

void Eluna::AddScriptPath(std::string filename, const std::string& fullpath)
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
            path + "/?.ext;" +
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
        path + "/?.ext;" +
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
            if (lua_isnoneornil(L, -1) || (lua_isboolean(L, -1) && !lua_toboolean(L, -1)))
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

void Eluna::report(lua_State* luastate)
{
    const char* msg = lua_tostring(luastate, -1);
    ELUNA_LOG_ERROR("%s", msg);
    lua_pop(luastate, 1);
}

void Eluna::ExecuteCall(int params, int res)
{
    int top = lua_gettop(L);

    // Expected: function, [parameters]
    ASSERT(top > params);

    // Check function type
    int type = lua_type(L, top - params);
    if (type != LUA_TFUNCTION)
    {
        ELUNA_LOG_ERROR("[Eluna]: Cannot execute call: registered value is %s, not a function.", lua_typename(L, type));
        ASSERT(false);
    }

    // Objects are invalidated when event level hits 0
    ++event_level;
    int result = lua_pcall(L, params, res, 0);
    --event_level;

    // lua_pcall returns 0 on success.
    // On error we report errors and push nils for expected amount of returned values
    if (result)
    {
        report(L);
        for (int i = 0; i < res; ++i)
            lua_pushnil(L);
    }
}

void Eluna::Push(lua_State* luastate)
{
    lua_pushnil(luastate);
}
void Eluna::Push(lua_State* luastate, const long long l)
{
    ElunaTemplate<long long>::Push(luastate, new long long(l));
}
void Eluna::Push(lua_State* luastate, const unsigned long long l)
{
    ElunaTemplate<unsigned long long>::Push(luastate, new unsigned long long(l));
}
void Eluna::Push(lua_State* luastate, const long l)
{
    Push(luastate, static_cast<long long>(l));
}
void Eluna::Push(lua_State* luastate, const unsigned long l)
{
    Push(luastate, static_cast<unsigned long long>(l));
}
void Eluna::Push(lua_State* luastate, const int i)
{
    lua_pushinteger(luastate, i);
}
void Eluna::Push(lua_State* luastate, const unsigned int u)
{
    lua_pushunsigned(luastate, u);
}
void Eluna::Push(lua_State* luastate, const double d)
{
    lua_pushnumber(luastate, d);
}
void Eluna::Push(lua_State* luastate, const float f)
{
    lua_pushnumber(luastate, f);
}
void Eluna::Push(lua_State* luastate, const bool b)
{
    lua_pushboolean(luastate, b);
}
void Eluna::Push(lua_State* luastate, const std::string& str)
{
    lua_pushstring(luastate, str.c_str());
}
void Eluna::Push(lua_State* luastate, const char* str)
{
    lua_pushstring(luastate, str);
}
void Eluna::Push(lua_State* luastate, Pet const* pet)
{
    Push(luastate, pet->ToCreature());
}
void Eluna::Push(lua_State* luastate, TempSummon const* summon)
{
    Push(luastate, summon->ToCreature());
}
void Eluna::Push(lua_State* luastate, Unit const* unit)
{
    if (!unit)
    {
        Push(luastate);
        return;
    }
    switch (unit->GetTypeId())
    {
        case TYPEID_UNIT:
            Push(luastate, unit->ToCreature());
            break;
        case TYPEID_PLAYER:
            Push(luastate, unit->ToPlayer());
            break;
        default:
            ElunaTemplate<Unit>::Push(luastate, unit);
    }
}
void Eluna::Push(lua_State* luastate, WorldObject const* obj)
{
    if (!obj)
    {
        Push(luastate);
        return;
    }
    switch (obj->GetTypeId())
    {
        case TYPEID_UNIT:
            Push(luastate, obj->ToCreature());
            break;
        case TYPEID_PLAYER:
            Push(luastate, obj->ToPlayer());
            break;
        case TYPEID_GAMEOBJECT:
            Push(luastate, obj->ToGameObject());
            break;
        case TYPEID_CORPSE:
            Push(luastate, obj->ToCorpse());
            break;
        default:
            ElunaTemplate<WorldObject>::Push(luastate, obj);
    }
}
void Eluna::Push(lua_State* luastate, Object const* obj)
{
    if (!obj)
    {
        Push(luastate);
        return;
    }
    switch (obj->GetTypeId())
    {
        case TYPEID_UNIT:
            Push(luastate, obj->ToCreature());
            break;
        case TYPEID_PLAYER:
            Push(luastate, obj->ToPlayer());
            break;
        case TYPEID_GAMEOBJECT:
            Push(luastate, obj->ToGameObject());
            break;
        case TYPEID_CORPSE:
            Push(luastate, obj->ToCorpse());
            break;
        default:
            ElunaTemplate<Object>::Push(luastate, obj);
    }
}

static int CheckIntegerRange(lua_State* luastate, int narg, int min, int max)
{
    double value = luaL_checknumber(luastate, narg);
    char error_buffer[64];

    if (value > max)
    {
        snprintf(error_buffer, 64, "value must be less than or equal to %i", max);
        return luaL_argerror(luastate, narg, error_buffer);
    }

    if (value < min)
    {
        snprintf(error_buffer, 64, "value must be greater than or equal to %i", min);
        return luaL_argerror(luastate, narg, error_buffer);
    }

    return static_cast<int>(value);
}

static unsigned int CheckUnsignedRange(lua_State* luastate, int narg, unsigned int max)
{
    double value = luaL_checknumber(luastate, narg);
    char error_buffer[64];

    if (value < 0)
        return luaL_argerror(luastate, narg, "value must be greater than or equal to 0");

    if (value > max)
    {
        snprintf(error_buffer, 64, "value must be less than or equal to %u", max);
        return luaL_argerror(luastate, narg, error_buffer);
    }

    return static_cast<unsigned int>(value);
}

template<> bool Eluna::CHECKVAL<bool>(lua_State* luastate, int narg)
{
    return lua_toboolean(luastate, narg) != 0;
}
template<> float Eluna::CHECKVAL<float>(lua_State* luastate, int narg)
{
    return luaL_checknumber(luastate, narg);
}
template<> double Eluna::CHECKVAL<double>(lua_State* luastate, int narg)
{
    return luaL_checknumber(luastate, narg);
}
template<> signed char Eluna::CHECKVAL<signed char>(lua_State* luastate, int narg)
{
    return CheckIntegerRange(luastate, narg, SCHAR_MIN, SCHAR_MAX);
}
template<> unsigned char Eluna::CHECKVAL<unsigned char>(lua_State* luastate, int narg)
{
    return CheckUnsignedRange(luastate, narg, UCHAR_MAX);
}
template<> short Eluna::CHECKVAL<short>(lua_State* luastate, int narg)
{
    return CheckIntegerRange(luastate, narg, SHRT_MIN, SHRT_MAX);
}
template<> unsigned short Eluna::CHECKVAL<unsigned short>(lua_State* luastate, int narg)
{
    return CheckUnsignedRange(luastate, narg, USHRT_MAX);
}
template<> int Eluna::CHECKVAL<int>(lua_State* luastate, int narg)
{
    return CheckIntegerRange(luastate, narg, INT_MIN, INT_MAX);
}
template<> unsigned int Eluna::CHECKVAL<unsigned int>(lua_State* luastate, int narg)
{
    return CheckUnsignedRange(luastate, narg, UINT_MAX);
}
template<> const char* Eluna::CHECKVAL<const char*>(lua_State* luastate, int narg)
{
    return luaL_checkstring(luastate, narg);
}
template<> std::string Eluna::CHECKVAL<std::string>(lua_State* luastate, int narg)
{
    return luaL_checkstring(luastate, narg);
}
template<> long long Eluna::CHECKVAL<long long>(lua_State* luastate, int narg)
{
    if (lua_isnumber(luastate, narg))
        return static_cast<long long>(CHECKVAL<double>(luastate, narg));
    return *(Eluna::CHECKOBJ<long long>(luastate, narg, true));
}
template<> unsigned long long Eluna::CHECKVAL<unsigned long long>(lua_State* luastate, int narg)
{
    if (lua_isnumber(luastate, narg))
        return static_cast<unsigned long long>(CHECKVAL<uint32>(luastate, narg));
    return *(Eluna::CHECKOBJ<unsigned long long>(luastate, narg, true));
}
template<> long Eluna::CHECKVAL<long>(lua_State* luastate, int narg)
{
    return static_cast<long>(CHECKVAL<long long>(luastate, narg));
}
template<> unsigned long Eluna::CHECKVAL<unsigned long>(lua_State* luastate, int narg)
{
    return static_cast<unsigned long>(CHECKVAL<unsigned long long>(luastate, narg));
}

template<> Object* Eluna::CHECKOBJ<Object>(lua_State* luastate, int narg, bool error)
{
    Object* obj = CHECKOBJ<WorldObject>(luastate, narg, false);
    if (!obj)
        obj = CHECKOBJ<Item>(luastate, narg, false);
    if (!obj)
        obj = ElunaTemplate<Object>::Check(luastate, narg, error);
    return obj;
}
template<> WorldObject* Eluna::CHECKOBJ<WorldObject>(lua_State* luastate, int narg, bool error)
{
    WorldObject* obj = CHECKOBJ<Unit>(luastate, narg, false);
    if (!obj)
        obj = CHECKOBJ<GameObject>(luastate, narg, false);
    if (!obj)
        obj = CHECKOBJ<Corpse>(luastate, narg, false);
    if (!obj)
        obj = ElunaTemplate<WorldObject>::Check(luastate, narg, error);
    return obj;
}
template<> Unit* Eluna::CHECKOBJ<Unit>(lua_State* luastate, int narg, bool error)
{
    Unit* obj = CHECKOBJ<Player>(luastate, narg, false);
    if (!obj)
        obj = CHECKOBJ<Creature>(luastate, narg, false);
    if (!obj)
        obj = ElunaTemplate<Unit>::Check(luastate, narg, error);
    return obj;
}

template<> ElunaObject* Eluna::CHECKOBJ<ElunaObject>(lua_State* luastate, int narg, bool error)
{
    return CHECKTYPE(luastate, narg, NULL, error);
}

ElunaObject* Eluna::CHECKTYPE(lua_State* luastate, int narg, const char* tname, bool error)
{
    bool valid = false;
    ElunaObject** ptrHold = NULL;

    if (!tname)
    {
        valid = true;
        ptrHold = static_cast<ElunaObject**>(lua_touserdata(luastate, narg));
    }
    else
    {
        if (lua_getmetatable(luastate, narg))
        {
            luaL_getmetatable(luastate, tname);
            if (lua_rawequal(luastate, -1, -2) == 1)
            {
                valid = true;
                ptrHold = static_cast<ElunaObject**>(lua_touserdata(luastate, narg));
            }
            lua_pop(luastate, 2);
        }
    }

    if (!valid || !ptrHold)
    {
        if (error)
        {
            char buff[256];
            snprintf(buff, 256, "bad argument : %s expected, got %s", tname ? tname : "userdata", luaL_typename(luastate, narg));
            luaL_argerror(luastate, narg, buff);
        }
        return NULL;
    }
    return *ptrHold;
}

// Saves the function reference ID given to the register type's store for given entry under the given event
void Eluna::Register(uint8 regtype, uint32 id, uint64 guid, uint32 instanceId, uint32 evt, int functionRef, uint32 shots)
{
    switch (regtype)
    {
        case HookMgr::REGTYPE_SERVER:
            if (evt < HookMgr::SERVER_EVENT_COUNT)
            {
                ServerEventBindings->Insert(evt, functionRef, shots);
                return;
            }
            break;

        case HookMgr::REGTYPE_PLAYER:
            if (evt < HookMgr::PLAYER_EVENT_COUNT)
            {
                PlayerEventBindings->Insert(evt, functionRef, shots);
                return;
            }
            break;

        case HookMgr::REGTYPE_GUILD:
            if (evt < HookMgr::GUILD_EVENT_COUNT)
            {
                GuildEventBindings->Insert(evt, functionRef, shots);
                return;
            }
            break;

        case HookMgr::REGTYPE_GROUP:
            if (evt < HookMgr::GROUP_EVENT_COUNT)
            {
                GroupEventBindings->Insert(evt, functionRef, shots);
                return;
            }
            break;

        case HookMgr::REGTYPE_VEHICLE:
            if (evt < HookMgr::VEHICLE_EVENT_COUNT)
            {
                VehicleEventBindings->Insert(evt, functionRef, shots);
                return;
            }
            break;

        case HookMgr::REGTYPE_BG:
            if (evt < HookMgr::BG_EVENT_COUNT)
            {
                BGEventBindings->Insert(evt, functionRef, shots);
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

                PacketEventBindings->Insert(id, evt, functionRef, shots);
                return;
            }
            break;

        case HookMgr::REGTYPE_CREATURE:
            if (evt < HookMgr::CREATURE_EVENT_COUNT)
            {
                if (id != 0)
                {
                    if (!eObjectMgr->GetCreatureTemplate(id))
                    {
                        luaL_unref(L, LUA_REGISTRYINDEX, functionRef);
                        luaL_error(L, "Couldn't find a creature with (ID: %d)!", id);
                        return;
                    }

                    CreatureEventBindings->Insert(id, evt, functionRef, shots);
                }
                else
                {
                    ASSERT(guid != 0);
                    CreatureUniqueBindings->Insert(guid, instanceId, evt, functionRef, shots);
                }
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

                CreatureGossipBindings->Insert(id, evt, functionRef, shots);
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

                GameObjectEventBindings->Insert(id, evt, functionRef, shots);
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

                GameObjectGossipBindings->Insert(id, evt, functionRef, shots);
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

                ItemEventBindings->Insert(id, evt, functionRef, shots);
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

                ItemGossipBindings->Insert(id, evt, functionRef, shots);
                return;
            }
            break;

        case HookMgr::REGTYPE_PLAYER_GOSSIP:
            if (evt < HookMgr::GOSSIP_EVENT_COUNT)
            {
                playerGossipBindings->Insert(id, evt, functionRef, shots);
                return;
            }
            break;
    }
    luaL_unref(L, LUA_REGISTRYINDEX, functionRef);
    luaL_error(L, "Unknown event type (regtype %d, id %d, event %d)", regtype, id, evt);
}
