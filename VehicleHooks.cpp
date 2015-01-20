/*
 * Copyright (C) 2010 - 2015 Eluna Lua Engine <http://emudevs.com/>
 * This program is free software licensed under GPL version 3
 * Please see the included DOCS/LICENSE.md for more information
 */

#ifndef _VEHICLE_HOOKS_H
#define _VEHICLE_HOOKS_H

#include "Hooks.h"
#include "HookHelpers.h"
#include "LuaEngine.h"
#include "ElunaBinding.h"
#include "ElunaTemplate.h"

#ifndef CLASSIC
#ifndef TBC

using namespace Hooks;

// Vehicle
void Eluna::OnInstall(Vehicle* vehicle)
{
    if (!VehicleEventBindings->HasEvents(VEHICLE_EVENT_ON_INSTALL))
        return;

    LOCK_ELUNA;
    Push(vehicle);
    CallAllFunctions(VehicleEventBindings, VEHICLE_EVENT_ON_INSTALL);
}

void Eluna::OnUninstall(Vehicle* vehicle)
{
    if (!VehicleEventBindings->HasEvents(VEHICLE_EVENT_ON_UNINSTALL))
        return;

    LOCK_ELUNA;
    Push(vehicle);
    CallAllFunctions(VehicleEventBindings, VEHICLE_EVENT_ON_UNINSTALL);
}

void Eluna::OnInstallAccessory(Vehicle* vehicle, Creature* accessory)
{
    if (!VehicleEventBindings->HasEvents(VEHICLE_EVENT_ON_INSTALL_ACCESSORY))
        return;

    LOCK_ELUNA;
    Push(vehicle);
    Push(accessory);
    CallAllFunctions(VehicleEventBindings, VEHICLE_EVENT_ON_INSTALL_ACCESSORY);
}

void Eluna::OnAddPassenger(Vehicle* vehicle, Unit* passenger, int8 seatId)
{
    if (!VehicleEventBindings->HasEvents(VEHICLE_EVENT_ON_ADD_PASSENGER))
        return;

    LOCK_ELUNA;
    Push(vehicle);
    Push(passenger);
    Push(seatId);
    CallAllFunctions(VehicleEventBindings, VEHICLE_EVENT_ON_ADD_PASSENGER);
}

void Eluna::OnRemovePassenger(Vehicle* vehicle, Unit* passenger)
{
    if (!VehicleEventBindings->HasEvents(VEHICLE_EVENT_ON_REMOVE_PASSENGER))
        return;

    LOCK_ELUNA;
    Push(vehicle);
    Push(passenger);
    CallAllFunctions(VehicleEventBindings, VEHICLE_EVENT_ON_REMOVE_PASSENGER);
}

#endif // CLASSIC
#endif // TBC
#endif // _VEHICLE_HOOKS_H
