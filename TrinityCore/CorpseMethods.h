/*
* Copyright (C) 2010 - 2024 Eluna Lua Engine <https://elunaluaengine.github.io/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef CORPSEMETHODS_H
#define CORPSEMETHODS_H

/***
 * The remains of a [Player] that has died.
 *
 * Inherits all methods from: [Object], [WorldObject]
 */
namespace LuaCorpse
{
    /**
     * Returns the GUID of the [Player] that left the [Corpse] behind.
     *
     * @return ObjectGuid ownerGUID
     */
    int GetOwnerGUID(Eluna* E, Corpse* corpse)
    {
        E->Push(corpse->GetOwnerGUID());
        return 1;
    }

    /**
     * Returns the time when the [Player] became a ghost and spawned this [Corpse].
     *
     * @return uint32 ghostTime
     */
    int GetGhostTime(Eluna* E, Corpse* corpse)
    {
        E->Push(corpse->GetGhostTime());
        return 1;
    }

    /**
     * Returns the [CorpseType] of a [Corpse].
     *
     *     enum CorpseType
     *     {
     *         CORPSE_BONES             = 0,
     *         CORPSE_RESURRECTABLE_PVE = 1,
     *         CORPSE_RESURRECTABLE_PVP = 2
     *     };
     *
     * @return [CorpseType] corpseType
     */
    int GetType(Eluna* E, Corpse* corpse)
    {
        E->Push(corpse->GetType());
        return 1;
    }

    /**
     * Sets the "ghost time" to the current time.
     *
     * See [Corpse:GetGhostTime].
     */
    int ResetGhostTime(Eluna* /*E*/, Corpse* corpse)
    {
        corpse->ResetGhostTime();
        return 0;
    }

    /**
     * Saves the [Corpse] to the database.
     */
    int SaveToDB(Eluna* /*E*/, Corpse* corpse)
    {
        corpse->SaveToDB();
        return 0;
    }
    
    ElunaRegister<Corpse> CorpseMethods[] =
    {
        // Getters
        { "GetOwnerGUID", &LuaCorpse::GetOwnerGUID },
        { "GetGhostTime", &LuaCorpse::GetGhostTime },
        { "GetType", &LuaCorpse::GetType },

        // Other
        { "ResetGhostTime", &LuaCorpse::ResetGhostTime },
        { "SaveToDB", &LuaCorpse::SaveToDB },

        { NULL, NULL, METHOD_REG_NONE }
    };
};
#endif
