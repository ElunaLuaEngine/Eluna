/*
* Copyright (C) 2010 - 2024 Eluna Lua Engine <https://elunaluaengine.github.io/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef VEHICLEMETHODS_H
#define VEHICLEMETHODS_H
#ifndef CLASSIC
#ifndef TBC

/***
 * Inherits all methods from: none
 */
namespace LuaVehicle
{
    /**
     * Returns true if the [Unit] passenger is on board
     *
     * @param [Unit] passenger
     * @return bool isOnBoard
     */
    int IsOnBoard(Eluna* E, Vehicle* vehicle)
    {
        Unit* passenger = Eluna::CHECKOBJ<Unit>(E->L, 2);
#if defined TRINITY || AZEROTHCORE
        E->Push(passenger->IsOnVehicle(vehicle->GetBase()));
#else
        E->Push(vehicle->HasOnBoard(passenger));
#endif
        return 1;
    }

    /**
     * Returns the [Vehicle]'s owner
     *
     * @return [Unit] owner
     */
    int GetOwner(Eluna* E, Vehicle* vehicle)
    {
#if defined TRINITY || AZEROTHCORE
        E->Push(vehicle->GetBase());
#else
        E->Push(vehicle->GetOwner());
#endif
        return 1;
    }

    /**
     * Returns the [Vehicle]'s entry
     *
     * @return uint32 entry
     */
    int GetEntry(Eluna* E, Vehicle* vehicle)
    {
#ifdef TRINITY
        E->Push(vehicle->GetVehicleInfo()->ID);
#elif AZEROTHCORE
        E->Push(vehicle->GetVehicleInfo()->m_ID);
#else
        E->Push(vehicle->GetVehicleEntry()->m_ID);
#endif
        return 1;
    }

    /**
     * Returns the [Vehicle]'s passenger in the specified seat
     *
     * @param int8 seat
     * @return [Unit] passenger
     */
    int GetPassenger(Eluna* E, Vehicle* vehicle)
    {
        int8 seatId = Eluna::CHECKVAL<int8>(E->L, 2);
        E->Push(vehicle->GetPassenger(seatId));
        return 1;
    }

    /**
     * Adds [Unit] passenger to a specified seat in the [Vehicle]
     *
     * @param [Unit] passenger
     * @param int8 seat
     */
    int AddPassenger(Eluna* E, Vehicle* vehicle)
    {
        Unit* passenger = Eluna::CHECKOBJ<Unit>(E->L, 2);
        int8 seatId = Eluna::CHECKVAL<int8>(E->L, 3);
#if defined TRINITY || AZEROTHCORE
        vehicle->AddPassenger(passenger, seatId);
#else
        if (vehicle->CanBoard(passenger))
            vehicle->Board(passenger, seatId);
#endif
        return 0;
    }

    /**
     * Removes [Unit] passenger from the [Vehicle]
     *
     * @param [Unit] passenger
     */
    int RemovePassenger(Eluna* E, Vehicle* vehicle)
    {
        Unit* passenger = Eluna::CHECKOBJ<Unit>(E->L, 2);
#if defined TRINITY || AZEROTHCORE
        vehicle->RemovePassenger(passenger);
#else
        vehicle->UnBoard(passenger, false);
#endif
        return 0;
    }
    
    ElunaRegister<Vehicle> VehicleMethods[] =
    {
        // Getters
        { "GetOwner", &LuaVehicle::GetOwner },
        { "GetEntry", &LuaVehicle::GetEntry },
        { "GetPassenger", &LuaVehicle::GetPassenger },

        // Boolean
        { "IsOnBoard", &LuaVehicle::IsOnBoard },

        // Other
        { "AddPassenger", &LuaVehicle::AddPassenger },
        { "RemovePassenger", &LuaVehicle::RemovePassenger },

        { NULL, NULL }
    };
}

#endif // CLASSIC
#endif // TBC
#endif // VEHICLEMETHODS_H
