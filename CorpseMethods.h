/*
* Copyright (C) 2010 - 2014 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef CORPSEMETHODS_H
#define CORPSEMETHODS_H

namespace LuaCorpse
{
    /**
     * Returns the [Corpse] Owner GUID.
     *
     * @return uint64 ownerGUID
     */
    int GetOwnerGUID(lua_State* L, Corpse* corpse)
    {
#ifndef TRINITY
        Eluna::Push(L, corpse->GetOwnerGuid());
#else
        Eluna::Push(L, corpse->GetOwnerGUID());
#endif
        return 1;
    }

    /**
     * Returns the ghost time of a [Corpse].
     *
     * @return uint32 ghostTime
     */
    int GetGhostTime(lua_State* L, Corpse* corpse)
    {
        Eluna::Push(L, uint32(corpse->GetGhostTime()));
        return 1;
    }

    /**
     * Returns the [CorpseType] of a [Corpse].
     *
     * <pre>
     * enum CorpseType
     * {
     *     CORPSE_BONES             = 0,
     *     CORPSE_RESURRECTABLE_PVE = 1,
     *     CORPSE_RESURRECTABLE_PVP = 2
     * };
     * </pre>
     *
     * @return [CorpseType] corpseType
     */
    int GetType(lua_State* L, Corpse* corpse)
    {
        Eluna::Push(L, corpse->GetType());
        return 1;
    }

    /**
     * Resets the [Corpse] ghost time.
     *
     */
    int ResetGhostTime(lua_State* /*L*/, Corpse* corpse)
    {
        corpse->ResetGhostTime();
        return 0;
    }

    /**
     * Saves the [Corpse] to the database.
     *
     */
    int SaveToDB(lua_State* /*L*/, Corpse* corpse)
    {
        corpse->SaveToDB();
        return 0;
    }

    /**
     * Deletes the [Corpse] from the world.
     *
     */
    int DeleteBonesFromWorld(lua_State* /*L*/, Corpse* corpse)
    {
        corpse->DeleteBonesFromWorld();
        return 0;
    }
};
#endif
