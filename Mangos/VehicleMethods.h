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
        Unit* passenger = E->CHECKOBJ<Unit>(2);

        E->Push(vehicle->HasOnBoard(passenger));
        return 1;
    }

    /**
     * Returns the [Vehicle]'s owner
     *
     * @return [Unit] owner
     */
    int GetOwner(Eluna* E, Vehicle* vehicle)
    {
        E->Push(vehicle->GetOwner());
        return 1;
    }

    /**
     * Returns the [Vehicle]'s entry
     *
     * @return uint32 entry
     */
    int GetEntry(Eluna* E, Vehicle* vehicle)
    {
        E->Push(vehicle->GetVehicleEntry()->m_ID);
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
        int8 seatId = E->CHECKVAL<int8>(2);
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
        Unit* passenger = E->CHECKOBJ<Unit>(2);
        int8 seatId = E->CHECKVAL<int8>(3);

        if (vehicle->CanBoard(passenger))
            vehicle->Board(passenger, seatId);

        return 0;
    }

    /**
     * Removes [Unit] passenger from the [Vehicle]
     *
     * @param [Unit] passenger
     */
    int RemovePassenger(Eluna* E, Vehicle* vehicle)
    {
        Unit* passenger = E->CHECKOBJ<Unit>(2);

        vehicle->UnBoard(passenger, false);
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

        { NULL, NULL, METHOD_REG_NONE }
    };
}

#endif // CLASSIC
#endif // TBC
#endif // VEHICLEMETHODS_H
