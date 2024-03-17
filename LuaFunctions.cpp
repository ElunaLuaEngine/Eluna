/*
* Copyright (C) 2010 - 2023 Eluna Lua Engine <https://elunaluaengine.github.io/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

extern "C"
{
#include "lua.h"
};

// Eluna
#include "LuaEngine.h"
#include "ElunaEventMgr.h"
#include "ElunaIncludes.h"
#include "ElunaTemplate.h"
#include "ElunaUtility.h"

// Method includes
#include "GlobalMethods.h"
#include "ObjectMethods.h"
#include "WorldObjectMethods.h"
#include "UnitMethods.h"
#include "PlayerMethods.h"
#include "CreatureMethods.h"
#include "GroupMethods.h"
#include "GuildMethods.h"
#include "GameObjectMethods.h"
#include "ElunaQueryMethods.h"
#include "AuraMethods.h"
#include "ItemMethods.h"
#include "WorldPacketMethods.h"
#include "SpellMethods.h"
#include "QuestMethods.h"
#include "MapMethods.h"
#include "CorpseMethods.h"
#include "VehicleMethods.h"
#include "BattleGroundMethods.h"

// Template by Mud from http://stackoverflow.com/questions/4484437/lua-integer-type/4485511#4485511
template<> int ElunaTemplate<unsigned long long>::Add(lua_State* L) { Eluna* E = Eluna::GetEluna(L); E->Push(E->CHECKVAL<unsigned long long>(1) + E->CHECKVAL<unsigned long long>(2)); return 1; }
template<> int ElunaTemplate<unsigned long long>::Substract(lua_State* L) { Eluna* E = Eluna::GetEluna(L); E->Push(E->CHECKVAL<unsigned long long>(1) - E->CHECKVAL<unsigned long long>(2)); return 1; }
template<> int ElunaTemplate<unsigned long long>::Multiply(lua_State* L) { Eluna* E = Eluna::GetEluna(L); E->Push(E->CHECKVAL<unsigned long long>(1) * E->CHECKVAL<unsigned long long>(2)); return 1; }
template<> int ElunaTemplate<unsigned long long>::Divide(lua_State* L) { Eluna* E = Eluna::GetEluna(L); E->Push(E->CHECKVAL<unsigned long long>(1) / E->CHECKVAL<unsigned long long>(2)); return 1; }
template<> int ElunaTemplate<unsigned long long>::Mod(lua_State* L) { Eluna* E = Eluna::GetEluna(L); E->Push(E->CHECKVAL<unsigned long long>(1) % E->CHECKVAL<unsigned long long>(2)); return 1; }
// template<> int ElunaTemplate<unsigned long long>::UnaryMinus(lua_State* L) { Eluna::GetEluna(L)->Push(-E->CHECKVAL<unsigned long long>(L, 1)); return 1; }
template<> int ElunaTemplate<unsigned long long>::Equal(lua_State* L) { Eluna* E = Eluna::GetEluna(L); E->Push(E->CHECKVAL<unsigned long long>(1) == E->CHECKVAL<unsigned long long>(2)); return 1; }
template<> int ElunaTemplate<unsigned long long>::Less(lua_State* L) { Eluna* E = Eluna::GetEluna(L); E->Push(E->CHECKVAL<unsigned long long>(1) < E->CHECKVAL<unsigned long long>(2)); return 1; }
template<> int ElunaTemplate<unsigned long long>::LessOrEqual(lua_State* L) { Eluna* E = Eluna::GetEluna(L); E->Push(E->CHECKVAL<unsigned long long>(1) <= E->CHECKVAL<unsigned long long>(2)); return 1; }
template<> int ElunaTemplate<unsigned long long>::Pow(lua_State* L)
{
    Eluna* E = Eluna::GetEluna(L);
    E->Push(static_cast<unsigned long long>(powl(static_cast<long double>(E->CHECKVAL<unsigned long long>(1)), static_cast<long double>(E->CHECKVAL<unsigned long long>(2)))));
    return 1;
}
template<> int ElunaTemplate<unsigned long long>::ToString(lua_State* L)
{
    Eluna* E = Eluna::GetEluna(L);

    unsigned long long l = E->CHECKVAL<unsigned long long>(1);
    std::ostringstream ss;
    ss << l;
    E->Push(ss.str());
    return 1;
}

template<> int ElunaTemplate<long long>::Add(lua_State* L) { Eluna* E = Eluna::GetEluna(L); E->Push(E->CHECKVAL<long long>(1) + E->CHECKVAL<long long>(2)); return 1; }
template<> int ElunaTemplate<long long>::Substract(lua_State* L) { Eluna* E = Eluna::GetEluna(L); E->Push(E->CHECKVAL<long long>(1) - E->CHECKVAL<long long>(2)); return 1; }
template<> int ElunaTemplate<long long>::Multiply(lua_State* L) { Eluna* E = Eluna::GetEluna(L); E->Push(E->CHECKVAL<long long>(1) * E->CHECKVAL<long long>(2)); return 1; }
template<> int ElunaTemplate<long long>::Divide(lua_State* L) { Eluna* E = Eluna::GetEluna(L); E->Push(E->CHECKVAL<long long>(1) / E->CHECKVAL<long long>(2)); return 1; }
template<> int ElunaTemplate<long long>::Mod(lua_State* L) { Eluna* E = Eluna::GetEluna(L); E->Push(E->CHECKVAL<long long>(1) % E->CHECKVAL<long long>(2)); return 1; }
template<> int ElunaTemplate<long long>::UnaryMinus(lua_State* L) { Eluna* E = Eluna::GetEluna(L); E->Push(-E->CHECKVAL<long long>(1)); return 1; }
template<> int ElunaTemplate<long long>::Equal(lua_State* L) { Eluna* E = Eluna::GetEluna(L); E->Push(E->CHECKVAL<long long>(1) == E->CHECKVAL<long long>(2)); return 1; }
template<> int ElunaTemplate<long long>::Less(lua_State* L) { Eluna* E = Eluna::GetEluna(L); E->Push(E->CHECKVAL<long long>(1) < E->CHECKVAL<long long>(2)); return 1; }
template<> int ElunaTemplate<long long>::LessOrEqual(lua_State* L) { Eluna* E = Eluna::GetEluna(L); E->Push(E->CHECKVAL<long long>(1) <= E->CHECKVAL<long long>(2)); return 1; }
template<> int ElunaTemplate<long long>::Pow(lua_State* L)
{
    Eluna* E = Eluna::GetEluna(L);
    E->Push(static_cast<long long>(powl(static_cast<long double>(E->CHECKVAL<long long>(1)), static_cast<long double>(E->CHECKVAL<long long>(2)))));
    return 1;
}
template<> int ElunaTemplate<long long>::ToString(lua_State* L)
{
    Eluna* E = Eluna::GetEluna(L);

    long long l = E->CHECKVAL<long long>(1);
    std::ostringstream ss;
    ss << l;
    E->Push(ss.str());
    return 1;
}

template<> int ElunaTemplate<ObjectGuid>::Equal(lua_State* L) { Eluna* E = Eluna::GetEluna(L); E->Push(E->CHECKVAL<ObjectGuid>(1) == E->CHECKVAL<ObjectGuid>(2)); return 1; }
template<> int ElunaTemplate<ObjectGuid>::ToString(lua_State* L)
{
    Eluna* E = Eluna::GetEluna(L);
#if defined(TRINITY)
    E->Push(E->CHECKVAL<ObjectGuid>(1).ToString());
#else
    E->Push(E->CHECKVAL<ObjectGuid>(1).GetString());
#endif
    return 1;
}

void RegisterFunctions(Eluna* E)
{
    ElunaGlobal::SetMethods(E, LuaGlobalFunctions::GlobalMethods);

    ElunaTemplate<Object>::Register(E, "Object");
    ElunaTemplate<Object>::SetMethods(E, LuaObject::ObjectMethods);

    ElunaTemplate<WorldObject>::Register(E, "WorldObject");
    ElunaTemplate<WorldObject>::SetMethods(E, LuaObject::ObjectMethods);
    ElunaTemplate<WorldObject>::SetMethods(E, LuaWorldObject::WorldObjectMethods);

    ElunaTemplate<Unit>::Register(E, "Unit");
    ElunaTemplate<Unit>::SetMethods(E, LuaObject::ObjectMethods);
    ElunaTemplate<Unit>::SetMethods(E, LuaWorldObject::WorldObjectMethods);
    ElunaTemplate<Unit>::SetMethods(E, LuaUnit::UnitMethods);

    ElunaTemplate<Player>::Register(E, "Player");
    ElunaTemplate<Player>::SetMethods(E, LuaObject::ObjectMethods);
    ElunaTemplate<Player>::SetMethods(E, LuaWorldObject::WorldObjectMethods);
    ElunaTemplate<Player>::SetMethods(E, LuaUnit::UnitMethods);
    ElunaTemplate<Player>::SetMethods(E, LuaPlayer::PlayerMethods);

    ElunaTemplate<Creature>::Register(E, "Creature");
    ElunaTemplate<Creature>::SetMethods(E, LuaObject::ObjectMethods);
    ElunaTemplate<Creature>::SetMethods(E, LuaWorldObject::WorldObjectMethods);
    ElunaTemplate<Creature>::SetMethods(E, LuaUnit::UnitMethods);
    ElunaTemplate<Creature>::SetMethods(E, LuaCreature::CreatureMethods);

    ElunaTemplate<GameObject>::Register(E, "GameObject");
    ElunaTemplate<GameObject>::SetMethods(E, LuaObject::ObjectMethods);
    ElunaTemplate<GameObject>::SetMethods(E, LuaWorldObject::WorldObjectMethods);
    ElunaTemplate<GameObject>::SetMethods(E, LuaGameObject::GameObjectMethods);

    ElunaTemplate<Corpse>::Register(E, "Corpse");
    ElunaTemplate<Corpse>::SetMethods(E, LuaObject::ObjectMethods);
    ElunaTemplate<Corpse>::SetMethods(E, LuaWorldObject::WorldObjectMethods);
    ElunaTemplate<Corpse>::SetMethods(E, LuaCorpse::CorpseMethods);

    ElunaTemplate<Item>::Register(E, "Item");
    ElunaTemplate<Item>::SetMethods(E, LuaObject::ObjectMethods);
    ElunaTemplate<Item>::SetMethods(E, LuaItem::ItemMethods);

#ifndef CLASSIC
#ifndef TBC
    ElunaTemplate<Vehicle>::Register(E, "Vehicle");
    ElunaTemplate<Vehicle>::SetMethods(E, LuaVehicle::VehicleMethods);
#endif
#endif

    ElunaTemplate<Group>::Register(E, "Group");
    ElunaTemplate<Group>::SetMethods(E, LuaGroup::GroupMethods);

    ElunaTemplate<Guild>::Register(E, "Guild");
    ElunaTemplate<Guild>::SetMethods(E, LuaGuild::GuildMethods);

    ElunaTemplate<Aura>::Register(E, "Aura");
    ElunaTemplate<Aura>::SetMethods(E, LuaAura::AuraMethods);

    ElunaTemplate<Spell>::Register(E, "Spell");
    ElunaTemplate<Spell>::SetMethods(E, LuaSpell::SpellMethods);

    ElunaTemplate<Quest>::Register(E, "Quest");
    ElunaTemplate<Quest>::SetMethods(E, LuaQuest::QuestMethods);

    ElunaTemplate<Map>::Register(E, "Map");
    ElunaTemplate<Map>::SetMethods(E, LuaMap::MapMethods);

    ElunaTemplate<BattleGround>::Register(E, "BattleGround");
    ElunaTemplate<BattleGround>::SetMethods(E, LuaBattleGround::BattleGroundMethods);

    ElunaTemplate<WorldPacket>::Register(E, "WorldPacket");
    ElunaTemplate<WorldPacket>::SetMethods(E, LuaPacket::PacketMethods);

    ElunaTemplate<ElunaQuery>::Register(E, "ElunaQuery");
    ElunaTemplate<ElunaQuery>::SetMethods(E, LuaQuery::QueryMethods);

    ElunaTemplate<long long>::Register(E, "long long");

    ElunaTemplate<unsigned long long>::Register(E, "unsigned long long");

    ElunaTemplate<ObjectGuid>::Register(E, "ObjectGuid");

    LuaVal::Register(E->L);
}
