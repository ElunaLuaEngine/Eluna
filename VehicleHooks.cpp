/*
 * Copyright (C) 2010 - 2024 Eluna Lua Engine <https://elunaluaengine.github.io/>
 * This program is free software licensed under GPL version 3
 * Please see the included DOCS/LICENSE.md for more information
 */

#include "Hooks.h"
#include "HookHelpers.h"
#include "LuaEngine.h"
#include "BindingMap.h"
#include "ElunaTemplate.h"

#ifndef CLASSIC
#ifndef TBC

using namespace Hooks;

#define START_HOOK(EVENT) \
    auto key = EventKey<VehicleEvents>(EVENT);\
    if (!VehicleEventBindings->HasBindingsFor(key))\
        return;

void Eluna::OnInstall(Vehicle* vehicle)
{
    START_HOOK(VEHICLE_EVENT_ON_INSTALL);
    HookPush(vehicle);
    CallAllFunctions(VehicleEventBindings, key);
}

void Eluna::OnUninstall(Vehicle* vehicle)
{
    START_HOOK(VEHICLE_EVENT_ON_UNINSTALL);
    HookPush(vehicle);
    CallAllFunctions(VehicleEventBindings, key);
}

void Eluna::OnInstallAccessory(Vehicle* vehicle, Creature* accessory)
{
    START_HOOK(VEHICLE_EVENT_ON_INSTALL_ACCESSORY);
    HookPush(vehicle);
    HookPush(accessory);
    CallAllFunctions(VehicleEventBindings, key);
}

void Eluna::OnAddPassenger(Vehicle* vehicle, Unit* passenger, int8 seatId)
{
    START_HOOK(VEHICLE_EVENT_ON_ADD_PASSENGER);
    HookPush(vehicle);
    HookPush(passenger);
    HookPush(seatId);
    CallAllFunctions(VehicleEventBindings, key);
}

void Eluna::OnRemovePassenger(Vehicle* vehicle, Unit* passenger)
{
    START_HOOK(VEHICLE_EVENT_ON_REMOVE_PASSENGER);
    HookPush(vehicle);
    HookPush(passenger);
    CallAllFunctions(VehicleEventBindings, key);
}

#endif // CLASSIC
#endif // TBC
