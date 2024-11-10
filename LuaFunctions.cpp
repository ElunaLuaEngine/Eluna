/*
* Copyright (C) 2010 - 2024 Eluna Lua Engine <https://elunaluaengine.github.io/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

// Eluna
#include "LuaEngine.h"
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

#if defined TRACKABLE_PTR_NAMESPACE
ElunaConstrainedObjectRef<Aura> GetWeakPtrFor(Aura const* obj)
{
#if defined ELUNA_TRINITY
    Map* map = obj->GetOwner()->GetMap();
#elif defined ELUNA_CMANGOS
    Map* map = obj->GetTarget()->GetMap();
#endif
    return { obj->GetWeakPtr(), map };
}
ElunaConstrainedObjectRef<BattleGround> GetWeakPtrFor(BattleGround const* obj) { return { obj->GetWeakPtr(), obj->GetBgMap() }; }
ElunaConstrainedObjectRef<Group> GetWeakPtrFor(Group const* obj) { return { obj->GetWeakPtr(), nullptr }; }
ElunaConstrainedObjectRef<Guild> GetWeakPtrFor(Guild const* obj) { return { obj->GetWeakPtr(), nullptr }; }
ElunaConstrainedObjectRef<Map> GetWeakPtrFor(Map const* obj) { return { obj->GetWeakPtr(), obj }; }
ElunaConstrainedObjectRef<Object> GetWeakPtrForObjectImpl(Object const* obj)
{
    if (obj->isType(TYPEMASK_WORLDOBJECT))
        return { obj->GetWeakPtr(), static_cast<WorldObject const*>(obj)->GetMap() };

    if (obj->GetTypeId() == TYPEID_ITEM)
        if (Player const* player = static_cast<Item const*>(obj)->GetOwner())
            return { obj->GetWeakPtr(), player->GetMap() };

    // possibly dangerous item
    return { obj->GetWeakPtr(), nullptr };
}
ElunaConstrainedObjectRef<Quest> GetWeakPtrFor(Quest const* obj) { return { obj->GetWeakPtr(), nullptr }; }
ElunaConstrainedObjectRef<Spell> GetWeakPtrFor(Spell const* obj) { return { obj->GetWeakPtr(), obj->GetCaster()->GetMap() }; }
#if ELUNA_EXPANSION >= EXP_WOTLK
ElunaConstrainedObjectRef<Vehicle> GetWeakPtrFor(Vehicle const* obj)
{
#if defined ELUNA_TRINITY
    Map* map = obj->GetBase()->GetMap();
#elif defined ELUNA_CMANGOS
    Map* map = obj->GetOwner()->GetMap();
#endif
    return { obj->GetWeakPtr(), map };
}
#endif
#endif

template<> int ElunaTemplate<unsigned long long>::Add(lua_State* L) { return ElunaTemplateHelper<unsigned long long>::PerformOp(L, std::plus()); }
template<> int ElunaTemplate<unsigned long long>::Subtract(lua_State* L) { return ElunaTemplateHelper<unsigned long long>::PerformOp(L, std::minus()); }
template<> int ElunaTemplate<unsigned long long>::Multiply(lua_State* L) { return ElunaTemplateHelper<unsigned long long>::PerformOp(L, std::multiplies()); }
template<> int ElunaTemplate<unsigned long long>::Divide(lua_State* L) { return ElunaTemplateHelper<unsigned long long>::PerformOp(L, std::divides()); }
template<> int ElunaTemplate<unsigned long long>::Mod(lua_State* L) { return ElunaTemplateHelper<unsigned long long>::PerformOp(L, std::modulus()); }
template<> int ElunaTemplate<unsigned long long>::Equal(lua_State* L) { return ElunaTemplateHelper<unsigned long long>::PerformOp(L, std::equal_to()); }
template<> int ElunaTemplate<unsigned long long>::Less(lua_State* L) { return ElunaTemplateHelper<unsigned long long>::PerformOp(L, std::less()); }
template<> int ElunaTemplate<unsigned long long>::LessOrEqual(lua_State* L) { return ElunaTemplateHelper<unsigned long long>::PerformOp(L, std::less_equal()); }
template<> int ElunaTemplate<unsigned long long>::ToString(lua_State* L) { return ElunaTemplateHelper<unsigned long long>::ToString(L); }
template<> int ElunaTemplate<unsigned long long>::Pow(lua_State* L) { return ElunaTemplateHelper<unsigned long long>::Pow(L); }

template<> int ElunaTemplate<long long>::Add(lua_State* L) { return ElunaTemplateHelper<long long>::PerformOp(L, std::plus()); }
template<> int ElunaTemplate<long long>::Subtract(lua_State* L) { return ElunaTemplateHelper<long long>::PerformOp(L, std::minus()); }
template<> int ElunaTemplate<long long>::Multiply(lua_State* L) { return ElunaTemplateHelper<long long>::PerformOp(L, std::multiplies()); }
template<> int ElunaTemplate<long long>::Divide(lua_State* L) { return ElunaTemplateHelper<long long>::PerformOp(L, std::divides()); }
template<> int ElunaTemplate<long long>::Mod(lua_State* L) { return ElunaTemplateHelper<long long>::PerformOp(L, std::modulus()); }
template<> int ElunaTemplate<long long>::UnaryMinus(lua_State* L) { return ElunaTemplateHelper<long long>::PerformOp(L, std::negate()); }
template<> int ElunaTemplate<long long>::Equal(lua_State* L) { return ElunaTemplateHelper<long long>::PerformOp(L, std::equal_to()); }
template<> int ElunaTemplate<long long>::Less(lua_State* L) { return ElunaTemplateHelper<long long>::PerformOp(L, std::less()); }
template<> int ElunaTemplate<long long>::LessOrEqual(lua_State* L) { return ElunaTemplateHelper<long long>::PerformOp(L, std::less_equal()); }
template<> int ElunaTemplate<long long>::ToString(lua_State* L) { return ElunaTemplateHelper<long long>::ToString(L); }
template<> int ElunaTemplate<long long>::Pow(lua_State* L) { return ElunaTemplateHelper<long long>::Pow(L); }

template<> int ElunaTemplate<ObjectGuid>::Equal(lua_State* L) { Eluna* E = Eluna::GetEluna(L); E->Push(E->CHECKVAL<ObjectGuid>(1) == E->CHECKVAL<ObjectGuid>(2)); return 1; }
template<> int ElunaTemplate<ObjectGuid>::ToString(lua_State* L)
{
    Eluna* E = Eluna::GetEluna(L);
#if defined ELUNA_TRINITY
    E->Push(E->CHECKVAL<ObjectGuid>(1).ToString());
#else
    E->Push(E->CHECKVAL<ObjectGuid>(1).GetString());
#endif
    return 1;
}

void RegisterFunctions(Eluna* E)
{
    ElunaTemplate<>::SetMethods(E, LuaGlobalFunctions::GlobalMethods);

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

#if ELUNA_EXPANSION >= EXP_WOTLK
    ElunaTemplate<Vehicle>::Register(E, "Vehicle");
    ElunaTemplate<Vehicle>::SetMethods(E, LuaVehicle::VehicleMethods);
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
