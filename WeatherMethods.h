/*
* Copyright (C) 2010 - 2014 Eluna Lua Engine <http://emudevs.com/>
* This program is free software licensed under GPL version 3
* Please see the included DOCS/LICENSE.md for more information
*/

#ifndef WEATHERMETHODS_H
#define WEATHERMETHODS_H

namespace LuaWeather
{
    /**
     * Returns the zone id of the [Weather]
     *
     * @return uint32 zoneId
     */
    int GetZoneId(lua_State* L, Weather* weather)
    {
        Eluna::Push(L, weather->GetZone());
        return 1;
    }

    /**
     * Sets the [Weather] type based on [WeatherType] and grade supplied.
     *
     * <pre>
     * enum WeatherType
     * {
     *     WEATHER_TYPE_FINE       = 0,
     *     WEATHER_TYPE_RAIN       = 1,
     *     WEATHER_TYPE_SNOW       = 2,
     *     WEATHER_TYPE_STORM      = 3,
     *     WEATHER_TYPE_THUNDERS   = 86,
     *     WEATHER_TYPE_BLACKRAIN  = 90
     * };
     * </pre>
     *
     * @param WeatherType type : the [WeatherType], see above available weather types
     * @param float grade : the intensity/grade of the [Weather], ranges from 0 to 1
     */
    int SetWeather(lua_State* L, Weather* weather)
    {
        uint32 weatherType = Eluna::CHECKVAL<uint32>(L, 2);
        float grade = Eluna::CHECKVAL<float>(L, 3);

        weather->SetWeather((WeatherType)weatherType, grade);
        return 0;
    }

    /**
     * Sends a [Weather] update to the [Player] supplied.
     *
     * @param [Player] player
     */
    int SendWeatherUpdateToPlayer(lua_State* L, Weather* weather)
    {
        Player* player = Eluna::CHECKOBJ<Player>(L, 2);

        weather->SendWeatherUpdateToPlayer(player);
        return 0;
    }

    /**
     * Regenerates the [Weather], causing it to change based on the below statistics.
     * 
     * * 30% chance of no change
     * * 30% chance of [Weather] getting better (if not fine) or changing [Weather] type
     * * 30% chance of [Weather] getting worse (if not fine)
     * * 10% chance of radical change (if not fine)
     *
     * @return bool changed : returns 'true' if [Weather] changed
     */
    int Regenerate(lua_State* L, Weather* weather)
    {
        Eluna::Push(L, weather->ReGenerate());
        return 1;
    }

    /**
     * Sends a [Weather] update to the all [Player] in the zone.
     *
     * @param bool changed : returns 'true' if weather changed for any [Player] in the zone, 'false' if no [Player] is within the zone
     */
    int UpdateWeather(lua_State* L, Weather* weather)
    {
        Eluna::Push(L, weather->UpdateWeather());
        return 1;
    }
};

#endif
