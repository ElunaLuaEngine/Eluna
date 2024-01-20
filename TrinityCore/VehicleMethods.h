/*
* Copyright (C) 2010 - 2024 Eluna Lua Engine <https://elunaluaengine.github.io/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef VEHICLEMETHODS_H
#define VEHICLEMETHODS_H

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

        E->Push(passenger->IsOnVehicle(vehicle->GetBase()));
        return 1;
    }

    /**
     * Returns the [Vehicle]'s owner
     *
     * @return [Unit] owner
     */
    int GetOwner(Eluna* E, Vehicle* vehicle)
    {
        E->Push(vehicle->GetBase());
        return 1;
    }

    /**
     * Returns the [Vehicle]'s entry
     *
     * @return uint32 entry
     */
    int GetEntry(Eluna* E, Vehicle* vehicle)
    {
        E->Push(vehicle->GetVehicleInfo()->ID);
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

#ifndef CATA
        vehicle->AddPassenger(passenger, seatId);
#else
        vehicle->AddVehiclePassenger(passenger, seatId);
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

        vehicle->RemovePassenger(passenger);
        return 0;
    }
    
    ElunaRegister<Vehicle> VehicleMethods[] =
    {
        // Getters
        { "GetOwner", &LuaVehicle::GetOwner, METHOD_REG_ALL },
        { "GetEntry", &LuaVehicle::GetEntry, METHOD_REG_ALL },
        { "GetPassenger", &LuaVehicle::GetPassenger, METHOD_REG_ALL },

        // Boolean
        { "IsOnBoard", &LuaVehicle::IsOnBoard, METHOD_REG_ALL },

        // Other
        { "AddPassenger", &LuaVehicle::AddPassenger, METHOD_REG_ALL },
        { "RemovePassenger", &LuaVehicle::RemovePassenger, METHOD_REG_ALL },

        { NULL, NULL, METHOD_REG_NONE }
    };
}

#endif // VEHICLEMETHODS_H
