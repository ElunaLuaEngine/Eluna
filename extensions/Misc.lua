-- Set correct require paths
package.path = package.path.."lua_scripts\\?;lua_scripts\\?.dll;lua_scripts\\?.lua;lua_scripts\\extensions\\?;lua_scripts\\extensions\\?.dll;lua_scripts\\extensions\\?.lua"
-- Randomize random
math.randomseed(tonumber(tostring(os.time()):reverse():sub(1,6)))
