/*
* Copyright (C) 2010 - 2024 Eluna Lua Engine <https://elunaluaengine.github.io/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

// Eluna
#include "ElunaIncludes.h"
#include "ElunaTemplate.h"

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

template<> inline int ElunaTemplate<unsigned long long>::Add(lua_State* L) { return PerformBinaryOp<unsigned long long>(L, std::plus<unsigned long long>()); }
template<> inline int ElunaTemplate<unsigned long long>::Subtract(lua_State* L) { return PerformBinaryOp<unsigned long long>(L, std::minus<unsigned long long>()); }
template<> inline int ElunaTemplate<unsigned long long>::Multiply(lua_State* L) { return PerformBinaryOp<unsigned long long>(L, std::multiplies<unsigned long long>()); }
template<> inline int ElunaTemplate<unsigned long long>::Divide(lua_State* L) { return PerformBinaryOp<unsigned long long>(L, std::divides<unsigned long long>()); }
template<> inline int ElunaTemplate<unsigned long long>::Mod(lua_State* L) { return PerformBinaryOp<unsigned long long>(L, std::modulus<unsigned long long>()); }
template<> inline int ElunaTemplate<unsigned long long>::Equal(lua_State* L) { return PerformBinaryOp<unsigned long long>(L, std::equal_to<unsigned long long>()); }
template<> inline int ElunaTemplate<unsigned long long>::Less(lua_State* L) { return PerformBinaryOp<unsigned long long>(L, std::less<unsigned long long>()); }
template<> inline int ElunaTemplate<unsigned long long>::LessOrEqual(lua_State* L) { return PerformBinaryOp<unsigned long long>(L, std::less_equal<unsigned long long>()); }
template<> inline int ElunaTemplate<unsigned long long>::ToString(lua_State* L) { return ToStringHelper(L); }
template<> inline int ElunaTemplate<unsigned long long>::Pow(lua_State* L) { return PowHelper(L); }

template<> inline int ElunaTemplate<long long>::Add(lua_State* L) { return PerformBinaryOp<unsigned long long>(L, std::plus<long long>()); }
template<> inline int ElunaTemplate<long long>::Subtract(lua_State* L) { return PerformBinaryOp<unsigned long long>(L, std::minus<long long>()); }
template<> inline int ElunaTemplate<long long>::Multiply(lua_State* L) { return PerformBinaryOp<unsigned long long>(L, std::multiplies<long long>()); }
template<> inline int ElunaTemplate<long long>::Divide(lua_State* L) { return PerformBinaryOp<unsigned long long>(L, std::divides<long long>()); }
template<> inline int ElunaTemplate<long long>::Mod(lua_State* L) { return PerformBinaryOp<unsigned long long>(L, std::modulus<long long>()); }
template<> inline int ElunaTemplate<long long>::UnaryMinus(lua_State* L) { return PerformUnaryOp<unsigned long long>(L, std::negate<long long>()); }
template<> inline int ElunaTemplate<long long>::Equal(lua_State* L) { return PerformBinaryOp<unsigned long long>(L, std::equal_to<long long>()); }
template<> inline int ElunaTemplate<long long>::Less(lua_State* L) { return PerformBinaryOp<unsigned long long>(L, std::less<long long>()); }
template<> inline int ElunaTemplate<long long>::LessOrEqual(lua_State* L) { return PerformBinaryOp<unsigned long long>(L, std::less_equal<long long>()); }
template<> inline int ElunaTemplate<long long>::ToString(lua_State* L) { return ToStringHelper(L); }
template<> inline int ElunaTemplate<long long>::Pow(lua_State* L) { return PowHelper(L); }

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
