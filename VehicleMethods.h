/*
* Copyright (C) 2010 - 2014 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef VEHICLEMETHODS_H
#define VEHICLEMETHODS_H
#ifndef CLASSIC
#ifndef TBC

namespace LuaVehicle
{
    /* BOOLEAN */
    int IsOnBoard(Eluna* E, Vehicle* vehicle)
    {
        Unit* passenger = Eluna::CHECKOBJ<Unit>(E->L, 2);
#ifndef TRINITY
        Eluna::Push(E->L, vehicle->HasOnBoard(passenger));
#else
        Eluna::Push(E->L, passenger->IsOnVehicle(vehicle->GetBase()));
#endif
        return 1;
    }

    /* GETTERS */
    int GetOwner(Eluna* E, Vehicle* vehicle)
    {
#ifndef TRINITY
        Eluna::Push(E->L, vehicle->GetOwner());
#else
        Eluna::Push(E->L, vehicle->GetBase());
#endif
        return 1;
    }

    int GetEntry(Eluna* E, Vehicle* vehicle)
    {
#ifndef TRINITY
        Eluna::Push(E->L, vehicle->GetVehicleEntry()->m_ID);
#else
        Eluna::Push(E->L, vehicle->GetVehicleInfo()->m_ID);
#endif
        return 1;
    }

    int GetPassenger(Eluna* E, Vehicle* vehicle)
    {
        int8 seatId = Eluna::CHECKVAL<int8>(E->L, 2);
        Eluna::Push(E->L, vehicle->GetPassenger(seatId));
        return 1;
    }

    /* OTHER */
    int AddPassenger(Eluna* E, Vehicle* vehicle)
    {
        Unit* passenger = Eluna::CHECKOBJ<Unit>(E->L, 2);
        int8 seatId = Eluna::CHECKVAL<int8>(E->L, 3);
#ifndef TRINITY
        if (vehicle->CanBoard(passenger))
            vehicle->Board(passenger, seatId);
#else
        vehicle->AddPassenger(passenger, seatId);
#endif
        return 0;
    }

    int RemovePassenger(Eluna* E, Vehicle* vehicle)
    {
        Unit* passenger = Eluna::CHECKOBJ<Unit>(E->L, 2);
#ifndef TRINITY
        vehicle->UnBoard(passenger, false);
#else
        vehicle->RemovePassenger(passenger);
#endif
        return 0;
    }
}

#endif
#endif
#endif