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

template<> inline int ElunaTemplate<unsigned long long>::Add(lua_State* L) { return ElunaTemplateHelper<unsigned long long>::PerformOp(L, std::plus()); }
template<> inline int ElunaTemplate<unsigned long long>::Subtract(lua_State* L) { return ElunaTemplateHelper<unsigned long long>::PerformOp(L, std::minus()); }
template<> inline int ElunaTemplate<unsigned long long>::Multiply(lua_State* L) { return ElunaTemplateHelper<unsigned long long>::PerformOp(L, std::multiplies()); }
template<> inline int ElunaTemplate<unsigned long long>::Divide(lua_State* L) { return ElunaTemplateHelper<unsigned long long>::PerformOp(L, std::divides()); }
template<> inline int ElunaTemplate<unsigned long long>::Mod(lua_State* L) { return ElunaTemplateHelper<unsigned long long>::PerformOp(L, std::modulus()); }
template<> inline int ElunaTemplate<unsigned long long>::Equal(lua_State* L) { return ElunaTemplateHelper<unsigned long long>::PerformOp(L, std::equal_to()); }
template<> inline int ElunaTemplate<unsigned long long>::Less(lua_State* L) { return ElunaTemplateHelper<unsigned long long>::PerformOp(L, std::less()); }
template<> inline int ElunaTemplate<unsigned long long>::LessOrEqual(lua_State* L) { return ElunaTemplateHelper<unsigned long long>::PerformOp(L, std::less_equal()); }
template<> inline int ElunaTemplate<unsigned long long>::ToString(lua_State* L) { return ElunaTemplateHelper<unsigned long long>::ToString(L); }
template<> inline int ElunaTemplate<unsigned long long>::Pow(lua_State* L) { return ElunaTemplateHelper<unsigned long long>::Pow(L); }

template<> inline int ElunaTemplate<long long>::Add(lua_State* L) { return ElunaTemplateHelper<long long>::PerformOp(L, std::plus()); }
template<> inline int ElunaTemplate<long long>::Subtract(lua_State* L) { return ElunaTemplateHelper<long long>::PerformOp(L, std::minus()); }
template<> inline int ElunaTemplate<long long>::Multiply(lua_State* L) { return ElunaTemplateHelper<long long>::PerformOp(L, std::multiplies()); }
template<> inline int ElunaTemplate<long long>::Divide(lua_State* L) { return ElunaTemplateHelper<long long>::PerformOp(L, std::divides()); }
template<> inline int ElunaTemplate<long long>::Mod(lua_State* L) { return ElunaTemplateHelper<long long>::PerformOp(L, std::modulus()); }
template<> inline int ElunaTemplate<long long>::UnaryMinus(lua_State* L) { return ElunaTemplateHelper<long long>::PerformOp(L, std::negate()); }
template<> inline int ElunaTemplate<long long>::Equal(lua_State* L) { return ElunaTemplateHelper<long long>::PerformOp(L, std::equal_to()); }
template<> inline int ElunaTemplate<long long>::Less(lua_State* L) { return ElunaTemplateHelper<long long>::PerformOp(L, std::less()); }
template<> inline int ElunaTemplate<long long>::LessOrEqual(lua_State* L) { return ElunaTemplateHelper<long long>::PerformOp(L, std::less_equal()); }
template<> inline int ElunaTemplate<long long>::ToString(lua_State* L) { return ElunaTemplateHelper<long long>::ToString(L); }
template<> inline int ElunaTemplate<long long>::Pow(lua_State* L) { return ElunaTemplateHelper<long long>::Pow(L); }

template<> inline int ElunaTemplate<ObjectGuid>::Equal(lua_State* L) { Eluna* E = Eluna::GetEluna(L); E->Push(E->CHECKVAL<ObjectGuid>(1) == E->CHECKVAL<ObjectGuid>(2)); return 1; }
template<> inline int ElunaTemplate<ObjectGuid>::ToString(lua_State* L)
{
    Eluna* E = Eluna::GetEluna(L);
#if defined ELUNA_TRINITY
    E->Push(E->CHECKVAL<ObjectGuid>(1).ToString());
#else
    E->Push(E->CHECKVAL<ObjectGuid>(1).GetString());
#endif
    return 1;
}
