/*
* Copyright (C) 2010 - 2024 Eluna Lua Engine <https://elunaluaengine.github.io/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/
#ifndef _ELUNA_PROCINFO_H
#define _ELUNA_PROCINFO_H
#include "LuaEngine.h"
class Unit;
class Spell;
class Map;
class SpellInfo;
class ProcEventInfo;
class DamageInfo;
class HealInfo;
#ifdef ELUNA_TRINITY
enum SpellSchoolMask : uint32;
#else
enum SpellSchoolMask;
#endif
enum DamageEffectType : uint8;
enum WeaponAttackType : uint8;
#ifdef ELUNA_TRINITY
namespace Trinity
{
    template<typename T>
    class unique_trackable_ptr;

    template<typename T>
    class unique_weak_ptr;
}
#endif

class ElunaProcInfo
{
private:
    Unit* _actor;
    Unit* _actionTarget;
    uint32 _typeMask;
    uint32 _spellTypeMask;
    uint32 _spellPhaseMask;
    uint32 _hitMask;
    Spell* _spell;

    SpellInfo const* _spellInfo;
    SpellSchoolMask _schoolMask;

    uint32 _damage;
    DamageEffectType _damageType;
    WeaponAttackType _attackType;
    uint32 _damageAbsorb;
    uint32 _resist;
    uint32 _block;

    uint32 _heal;
    uint32 _effectiveHeal;
    uint32 _healAbsorb;
    Map* _map;

    struct NoopAuraDeleter { void operator()(ElunaProcInfo*) const { } };
#ifdef ELUNA_TRINITY
    Trinity::unique_trackable_ptr<ElunaProcInfo> m_scriptRef;
#endif

public:
    ElunaProcInfo(Unit* actor, Unit* actionTarget, uint32 typeMask,
        uint32 spellTypeMask, uint32 spellPhaseMask, uint32 hitMask,
        Spell* spell, SpellInfo const* spellInfo, SpellSchoolMask schoolMask, Map* map);

    explicit ElunaProcInfo(ProcEventInfo& procInfo, Map* map);
    ~ElunaProcInfo()
    {
#ifdef TRACKABLE_PTR_NAMESPACE
        m_scriptRef = nullptr;
#endif
    }
    Unit* GetActor() const { return _actor; }
    Unit* GetActionTarget() const { return _actionTarget; }
    uint32 GetTypeMask() const { return _typeMask; }
    uint32 GetSpellTypeMask() const { return _spellTypeMask; }
    uint32 GetSpellPhaseMask() const { return _spellPhaseMask; }
    uint32 GetHitMask() const { return _hitMask; }
    Spell const* GetProcSpell() const { return _spell; }

    SpellInfo const* GetSpellInfo() const;
    SpellSchoolMask GetSchoolMask() const { return _schoolMask; }

    uint32 GetDamage() const { return _damage; }
    DamageEffectType GetDamageType() const { return _damageType; }
    WeaponAttackType GetAttackType() const { return _attackType; }
    uint32 GetDamageAbsorb() const { return _damageAbsorb; }
    uint32 GetResist() const { return _resist; }
    uint32 GetBlock() const { return _block; }

    uint32 GetHeal() const { return _heal; }
    uint32 GetEffectiveHeal() const { return _effectiveHeal; }
    uint32 GetHealAbsorb() const { return _healAbsorb; }

    bool HasDamage() const { return _damage > 0; }
    bool HasHeal() const { return _heal > 0; }

    void SetDamage(int32 amount) { _damage = amount; }
    void SetAbsorbDamage(uint32 amount) { _damageAbsorb = amount; }
    void SetResistDamage(uint32 amount) { _resist = amount; }
    void SetBlockDamage(uint32 amount) { _block = amount; }

    void SetAbsorbHeal(uint32 amount) { _healAbsorb = amount; }
    void SetEffectiveHeal(uint32 amount) { _effectiveHeal = amount; }
    void SetHeal(int32 amount) { _heal = amount; }

    void SetDamage(uint32 damage, DamageEffectType damageType, WeaponAttackType attackType);
    void SetHeal(uint32 heal);

    const Map* GetMap() const { return _map; }
#ifdef ELUNA_TRINITY
    Trinity::unique_weak_ptr<ElunaProcInfo> GetWeakPtr() const { return m_scriptRef; }
#endif
    void ApplyToProcEventInfo(ProcEventInfo& procInfo) const;
};

class ElunaSpellInfo
{
private:
    SpellInfo const* _spellInfo;
    struct NoopAuraDeleter { void operator()(ElunaSpellInfo*) const {} };
#ifdef ELUNA_TRINITY
    Trinity::unique_trackable_ptr<ElunaSpellInfo> m_scriptRef;
#endif
public:
    ElunaSpellInfo(uint32 spellId);
    ~ElunaSpellInfo()
    {
#ifdef TRACKABLE_PTR_NAMESPACE
        m_scriptRef = nullptr;
#endif
    }
    SpellInfo const* GetSpellInfo() const { return _spellInfo; }
#ifdef ELUNA_TRINITY
    Trinity::unique_weak_ptr<ElunaSpellInfo> GetWeakPtr() const { return m_scriptRef; }
#endif
};

#endif
