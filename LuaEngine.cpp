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

// Some dummy includes containing BOOST_VERSION:
// ObjectAccessor.h Config.h Log.h
#ifdef BOOST_VERSION
#include <boost/filesystem.hpp>
#else
#include <ace/ACE.h>
#include <ace/Dirent.h>
#include <ace/OS_NS_sys_stat.h>
#endif

extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
};

Eluna::ScriptList Eluna::lua_scripts;
Eluna::ScriptList Eluna::lua_extensions;
std::string Eluna::lua_folderpath;
Eluna* Eluna::GEluna = NULL;
bool Eluna::reload = false;

extern void RegisterFunctions(lua_State* L);

void Eluna::Initialize()
{
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
    // GetScripts(lua_folderpath + "/extensions", lua_extensions);
    GetScripts(lua_folderpath, lua_scripts);

    ELUNA_LOG_DEBUG("[Eluna]: Loaded %u scripts in %u ms", uint32(lua_scripts.size() + lua_extensions.size()), ElunaUtil::GetTimeDiff(oldMSTime));

    // Create global eluna
    new Eluna();
}

void Eluna::Uninitialize()
{
    delete GEluna;
    GEluna = NULL;
    lua_scripts.clear();
    lua_extensions.clear();
}

void Eluna::ReloadEluna()
{
    eWorld->SendServerMessage(SERVER_MSG_STRING, "Reloading Eluna...");
    Uninitialize();
    Initialize();

#ifdef TRINITY
    // Re initialize creature AI restoring C++ AI or applying lua AI
    {
#ifdef BOOST_VERSION
        boost::shared_lock<boost::shared_mutex> lock(*HashMapHolder<Creature>::GetLock());
#else
        TRINITY_READ_GUARD(HashMapHolder<Creature>::LockType, *HashMapHolder<Creature>::GetLock());
#endif
        HashMapHolder<Creature>::MapType const& m = ObjectAccessor::GetCreatures();
        for (HashMapHolder<Creature>::MapType::const_iterator iter = m.begin(); iter != m.end(); ++iter)
            if (iter->second->IsInWorld())
                iter->second->AIM_Initialize();
    }
#endif

    reload = false;
}

Eluna::Eluna():
L(luaL_newstate()),

m_EventMgr(new EventMgr(*this)),

ServerEventBindings(new EventBind<HookMgr::ServerEvents>("ServerEvents", *this)),
PlayerEventBindings(new EventBind<HookMgr::PlayerEvents>("PlayerEvents", *this)),
GuildEventBindings(new EventBind<HookMgr::GuildEvents>("GuildEvents", *this)),
GroupEventBindings(new EventBind<HookMgr::GroupEvents>("GroupEvents", *this)),
VehicleEventBindings(new EventBind<HookMgr::VehicleEvents>("VehicleEvents", *this)),

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
    RegisterFunctions(L);

    // Create hidden table with weak values
    lua_newtable(L);
    lua_newtable(L);
    lua_pushstring(L, "v");
    lua_setfield(L, -2, "__mode");
    lua_setmetatable(L, -2);
    userdata_table = luaL_ref(L, LUA_REGISTRYINDEX);

    // Replace this with map insert if making multithread version
    ASSERT(!Eluna::GEluna);
    Eluna::GEluna = this;

    // run scripts
    RunScripts();
}

Eluna::~Eluna()
{
    OnLuaStateClose();

    delete m_EventMgr;

    // Replace this with map remove if making multithread version
    Eluna::GEluna = NULL;

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

    // Must close lua state after deleting stores and mgr
    lua_close(L);
}

void Eluna::AddScriptPath(std::string filename, std::string fullpath, ScriptList& scripts)
{
    ELUNA_LOG_DEBUG("[Eluna]: AddScriptPath Checking file `%s`", fullpath.c_str());

    // split file name
    std::size_t extDot = filename.find_last_of('.');
    if (extDot == std::string::npos)
        return;
    std::string ext = filename.substr(extDot);
    filename = filename.substr(0, extDot);

    // check extension and add path to scripts to load
    bool luascript = ext == ".lua" || ext == ".dll";
    bool extension = ext == ".ext" || (filename.length() >= 4 && filename.find_last_of("_ext") == filename.length() - 4);
    if (!luascript && !extension)
        return;

    LuaScript script;
    script.fileext = ext;
    script.filename = filename;
    script.filepath = fullpath;
    script.modulepath = fullpath.substr(0, fullpath.length() - ext.length());
    if (extension)
        lua_extensions.push_back(script);
    else
        scripts.push_back(script);
    ELUNA_LOG_DEBUG("[Eluna]: GetScripts add path `%s`", fullpath.c_str());
}

// Finds lua script files from given path (including subdirectories) and pushes them to scripts
void Eluna::GetScripts(std::string path, ScriptList& scripts)
{
    ELUNA_LOG_DEBUG("[Eluna]: GetScripts from path `%s`", path.c_str());

#ifdef BOOST_VERSION
    boost::filesystem::path someDir(path);
    boost::filesystem::directory_iterator end_iter;

    if (boost::filesystem::exists(someDir) && boost::filesystem::is_directory(someDir))
    {
        for (boost::filesystem::directory_iterator dir_iter(someDir); dir_iter != end_iter; ++dir_iter)
        {
            std::string fullpath = dir_iter->path().generic_string();

            // load subfolder
            if (boost::filesystem::is_directory(dir_iter->status()))
            {
                GetScripts(fullpath, scripts);
                continue;
            }

            if (boost::filesystem::is_regular_file(dir_iter->status()))
            {
                // was file, try add
                std::string filename = dir_iter->path().filename().generic_string();
                AddScriptPath(filename, fullpath, scripts);
            }
        }
    }
#else
    ACE_Dirent dir;
    if (dir.open(path.c_str()) == -1)
    {
        ELUNA_LOG_ERROR("[Eluna]: Error No `%s` directory found, creating it", path.c_str());
        ACE_OS::mkdir(path.c_str());
        return;
    }

    ACE_DIRENT *directory = 0;
    while ((directory = dir.read()))
    {
        // Skip the ".." and "." files.
        if (ACE::isdotdir(directory->d_name))
            continue;

        std::string fullpath = path + "/" + directory->d_name;

        ACE_stat stat_buf;
        if (ACE_OS::lstat(fullpath.c_str(), &stat_buf) == -1)
            continue;

        // load subfolder
        if ((stat_buf.st_mode & S_IFMT) == (S_IFDIR))
        {
            GetScripts(fullpath, scripts);
            continue;
        }

        // was file, try add
        std::string filename = directory->d_name;
        AddScriptPath(filename, fullpath, scripts);
    }
#endif
}

static bool ScriptpathComparator(const LuaScript& first, const LuaScript& second)
{
    return first.filepath.compare(second.filepath) < 0;
}

void Eluna::RunScripts()
{
    uint32 oldMSTime = ElunaUtil::GetCurrTime();
    uint32 count = 0;

    ScriptList scripts;
    lua_extensions.sort(ScriptpathComparator);
    lua_scripts.sort(ScriptpathComparator);
    scripts.insert(scripts.end(), lua_extensions.begin(), lua_extensions.end());
    scripts.insert(scripts.end(), lua_scripts.begin(), lua_scripts.end());

    lua_getglobal(L, "package");
    luaL_getsubtable(L, -1, "loaded");
    int modules = lua_gettop(L);
    for (ScriptList::const_iterator it = scripts.begin(); it != scripts.end(); ++it)
    {
        lua_getfield(L, modules, it->modulepath.c_str());
        if (!lua_isnoneornil(L, -1))
        {
            lua_pop(L, 1);
            ELUNA_LOG_DEBUG("[Eluna]: Extension was already loaded or required `%s`", it->filepath.c_str());
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
            lua_setfield(L, modules, it->modulepath.c_str());

            // successfully loaded and ran file
            ELUNA_LOG_DEBUG("[Eluna]: Successfully loaded `%s`", it->filepath.c_str());
            ++count;
            continue;
        }
        ELUNA_LOG_ERROR("[Eluna]: Error loading extension `%s`", it->filepath.c_str());
        report(L);
    }
    lua_pop(L, 2);

    ELUNA_LOG_INFO("[Eluna]: Executed %u Lua scripts in %u ms", count, ElunaUtil::GetTimeDiff(oldMSTime));
}

void Eluna::RemoveRef(const void* obj)
{
    if (!sEluna)
        return;
    lua_rawgeti(sEluna->L, LUA_REGISTRYINDEX, sEluna->userdata_table);
    lua_pushfstring(sEluna->L, "%p", obj);
    lua_gettable(sEluna->L, -2);
    if (!lua_isnoneornil(sEluna->L, -1))
    {
        lua_pushfstring(sEluna->L, "%p", obj);
        lua_pushnil(sEluna->L);
        lua_settable(sEluna->L, -4);
    }
    lua_pop(sEluna->L, 2);
}

void Eluna::report(lua_State* L)
{
    const char* msg = lua_tostring(L, -1);
    while (msg)
    {
        lua_pop(L, 1);
        ELUNA_LOG_ERROR("%s", msg);
        msg = lua_tostring(L, -1);
    }
}

void Eluna::ExecuteCall(lua_State* L, int params, int res)
{
    int top = lua_gettop(L);
    luaL_checktype(L, top - params, LUA_TFUNCTION);
    if (lua_pcall(L, params, res, 0))
        report(L);
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
template<> bool Eluna::CHECKVAL<bool>(lua_State* L, int narg)
{
    return lua_isnumber(L, narg) != 0 ? luaL_optnumber(L, narg, 1) ? true : false : lua_toboolean(L, narg) != 0;
}
template<> bool Eluna::CHECKVAL<bool>(lua_State* L, int narg, bool def)
{
    return lua_isnone(L, narg) != 0 ? def : lua_isnumber(L, narg) != 0 ? luaL_optnumber(L, narg, 1) != 0 ? true : false : lua_toboolean(L, narg) != 0;
}
template<> float Eluna::CHECKVAL<float>(lua_State* L, int narg)
{
    return luaL_checknumber(L, narg);
}
template<> float Eluna::CHECKVAL<float>(lua_State* L, int narg, float def)
{
    if (lua_isnoneornil(L, narg) || !lua_isnumber(L, narg))
        return def;
    return luaL_optnumber(L, narg, def);
}
template<> double Eluna::CHECKVAL<double>(lua_State* L, int narg)
{
    return luaL_checknumber(L, narg);
}
template<> double Eluna::CHECKVAL<double>(lua_State* L, int narg, double def)
{
    if (lua_isnoneornil(L, narg) || !lua_isnumber(L, narg))
        return def;
    return luaL_optnumber(L, narg, def);
}
template<> int8 Eluna::CHECKVAL<int8>(lua_State* L, int narg)
{
    return luaL_checkint(L, narg);
}
template<> int8 Eluna::CHECKVAL<int8>(lua_State* L, int narg, int8 def)
{
    if (lua_isnoneornil(L, narg) || !lua_isnumber(L, narg))
        return def;
    return luaL_optint(L, narg, def);
}
template<> uint8 Eluna::CHECKVAL<uint8>(lua_State* L, int narg)
{
    return luaL_checkunsigned(L, narg);
}
template<> uint8 Eluna::CHECKVAL<uint8>(lua_State* L, int narg, uint8 def)
{
    if (lua_isnoneornil(L, narg) || !lua_isnumber(L, narg))
        return def;
    return luaL_optunsigned(L, narg, def);
}
template<> int16 Eluna::CHECKVAL<int16>(lua_State* L, int narg)
{
    return luaL_checkint(L, narg);
}
template<> int16 Eluna::CHECKVAL<int16>(lua_State* L, int narg, int16 def)
{
    if (lua_isnoneornil(L, narg) || !lua_isnumber(L, narg))
        return def;
    return luaL_optint(L, narg, def);
}
template<> uint16 Eluna::CHECKVAL<uint16>(lua_State* L, int narg)
{
    return luaL_checkunsigned(L, narg);
}
template<> uint16 Eluna::CHECKVAL<uint16>(lua_State* L, int narg, uint16 def)
{
    if (lua_isnoneornil(L, narg) || !lua_isnumber(L, narg))
        return def;
    return luaL_optunsigned(L, narg, def);
}
template<> uint32 Eluna::CHECKVAL<uint32>(lua_State* L, int narg)
{
    return luaL_checkunsigned(L, narg);
}
template<> uint32 Eluna::CHECKVAL<uint32>(lua_State* L, int narg, uint32 def)
{
    if (lua_isnoneornil(L, narg) || !lua_isnumber(L, narg))
        return def;
    return luaL_optunsigned(L, narg, def);
}
template<> int32 Eluna::CHECKVAL<int32>(lua_State* L, int narg)
{
    return luaL_checklong(L, narg);
}
template<> int32 Eluna::CHECKVAL<int32>(lua_State* L, int narg, int32 def)
{
    if (lua_isnoneornil(L, narg) || !lua_isnumber(L, narg))
        return def;
    return luaL_optlong(L, narg, def);
}
template<> const char* Eluna::CHECKVAL<const char*>(lua_State* L, int narg)
{
    return luaL_checkstring(L, narg);
}
template<> const char* Eluna::CHECKVAL<const char*>(lua_State* L, int narg, const char* def)
{
    if (lua_isnoneornil(L, narg) || !lua_isstring(L, narg))
        return def;
    return luaL_optstring(L, narg, def);
}
template<> std::string Eluna::CHECKVAL<std::string>(lua_State* L, int narg)
{
    return luaL_checkstring(L, narg);
}
template<> std::string Eluna::CHECKVAL<std::string>(lua_State* L, int narg, std::string def)
{
    if (lua_isnoneornil(L, narg) || !lua_isstring(L, narg))
        return def;
    return luaL_optstring(L, narg, def.c_str());
}
template<> uint64 Eluna::CHECKVAL<uint64>(lua_State* L, int narg)
{
    const char* c_str = CHECKVAL<const char*>(L, narg, NULL);
    if (!c_str)
        return luaL_argerror(L, narg, "uint64 (as string) expected");
    uint64 l = 0;
    sscanf(c_str, UI64FMTD, &l);
    return l;
}
template<> uint64 Eluna::CHECKVAL<uint64>(lua_State* L, int narg, uint64 def)
{
    const char* c_str = CHECKVAL<const char*>(L, narg, NULL);
    if (!c_str)
        return def;
    uint64 l = 0;
    sscanf(c_str, UI64FMTD, &l);
    return l;
}
template<> int64 Eluna::CHECKVAL<int64>(lua_State* L, int narg)
{
    const char* c_str = CHECKVAL<const char*>(L, narg, NULL);
    if (!c_str)
        return luaL_argerror(L, narg, "int64 (as string) expected");
    int64 l = 0;
    sscanf(c_str, SI64FMTD, &l);
    return l;
}
template<> int64 Eluna::CHECKVAL<int64>(lua_State* L, int narg, int64 def)
{
    const char* c_str = CHECKVAL<const char*>(L, narg, NULL);
    if (!c_str)
        return def;
    int64 l = 0;
    sscanf(c_str, SI64FMTD, &l);
    return l;
}
#define TEST_OBJ(T, O, E, F)\
{\
    if (!O || !O->F())\
    {\
    if (E)\
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
