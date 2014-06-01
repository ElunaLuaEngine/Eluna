/*
* Copyright (C) 2010 - 2014 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef SPELLMETHODS_H
#define SPELLMETHODS_H

namespace LuaSpell
{
    /* BOOLEAN */
    int IsAutoRepeat(lua_State* L, Spell* spell)
    {
        Eluna::Push(L, spell->IsAutoRepeat());
        return 1;
    }

    /* GETTERS */
    int GetCaster(lua_State* L, Spell* spell)
    {
        Eluna::Push(L, spell->GetCaster());
        return 1;
    }

    int GetCastTime(lua_State* L, Spell* spell)
    {
        Eluna::Push(L, spell->GetCastTime());
        return 1;
    }

    int GetId(lua_State* L, Spell* spell)
    {
        Eluna::Push(L, spell->m_spellInfo->Id);
        return 1;
    }

    int GetPowerCost(lua_State* L, Spell* spell)
    {
        Eluna::Push(L, spell->GetPowerCost());
        return 1;
    }

    int GetDuration(lua_State* L, Spell* spell)
    {
#ifdef MANGOS
        Eluna::Push(L, GetSpellDuration(spell->m_spellInfo));
#else
        Eluna::Push(L, spell->GetSpellInfo()->GetDuration());
#endif
        return 1;
    }

    int GetTargetDest(lua_State* L, Spell* spell)
    {
#ifdef MANGOS
        if (!(spell->m_targets.m_targetMask & TARGET_FLAG_DEST_LOCATION))
            return 3;
        float x, y, z;
        spell->m_targets.getDestination(x, y, z);
#else
        if (!spell->m_targets.HasDst())
            return 3;
        float x, y, z;
        spell->m_targets.GetDstPos()->GetPosition(x, y, z);
#endif
        Eluna::Push(L, x);
        Eluna::Push(L, y);
        Eluna::Push(L, z);
        return 3;
    }

    int GetTarget(lua_State* L, Spell* spell)
    {
#ifdef MANGOS
        if (GameObject* target = spell->m_targets.getGOTarget())
            Eluna::Push(L, target);
        else if (Item* target = spell->m_targets.getItemTarget())
            Eluna::Push(L, target);
        else if (Corpse* target = spell->GetCaster()->GetMap()->GetCorpse(spell->m_targets.getCorpseTargetGuid()))
            Eluna::Push(L, target);
        else if (Unit* target = spell->m_targets.getUnitTarget())
            Eluna::Push(L, target);
#else
        if (GameObject* target = spell->m_targets.GetGOTarget())
            Eluna::Push(L, target);
        else if (Item* target = spell->m_targets.GetItemTarget())
            Eluna::Push(L, target);
        else if (Corpse* target = spell->m_targets.GetCorpseTarget())
            Eluna::Push(L, target);
        else if (Unit* target = spell->m_targets.GetUnitTarget())
            Eluna::Push(L, target);
        else if (WorldObject* target = spell->m_targets.GetObjectTarget())
            Eluna::Push(L, target);
#endif
        return 1;
    }

    /* SETTERS */
    int SetAutoRepeat(lua_State* L, Spell* spell)
    {
        bool repeat = Eluna::CHECKVAL<bool>(L, 2);
        spell->SetAutoRepeat(repeat);
        return 0;
    }

    /* OTHER */
    int Cast(lua_State* L, Spell* spell)
    {
        bool skipCheck = Eluna::CHECKVAL<bool>(L, 2);
        spell->cast(skipCheck);
        return 0;
    }

    int cancel(lua_State* L, Spell* spell)
    {
        spell->cancel();
        return 0;
    }

    int Finish(lua_State* L, Spell* spell)
    {
        spell->finish();
        return 0;
    }
};
#endif
