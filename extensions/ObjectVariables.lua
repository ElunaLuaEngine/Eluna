--[[
Functions:
Object:GetData(instance) -- returns a table unique for the object or it's instance
Object:RemoveData(instance) -- deletes the unique table for the object or it's instance

Usage:
-- Set a variable
creature:GetData().escorted = true
-- Check a variable
if(creature:GetData().escorted) then
    print(creature:GetName().." has been escorted")
end
-- Remove all variables (on death, logout etc)
creature:RemoveData()
]]

local T = {}
function Object:GetData(instance)
    assert(self, "ObjectVariables: self was nil")
    if(instance) then
        if(not self.GetInstanceId or not self.GetMapId) then
            error("instance is true and object is not worldobject", 2)
        end
        local map = -self:GetMapId()
        local ID = self:GetInstanceId()
        if(not T[map]) then
            T[map] = {}
        end
        if(not T[map][ID]) then
            T[map][ID] = {}
        end
        return T[map][ID]
    else
        local ID = self:GetGUID()
        if(not T[ID]) then
            T[ID] = {}
        end
        return T[ID]
    end
end
function Object:RemoveData(instance)
    assert(self, "ObjectVariables: self was nil")
    if(instance) then
        if(not self.GetInstance or not self.GetMapId) then
            error("instance or map is true and object is not worldobject", 2)
        end
        local map = -self:GetMapId()
        local ID = self:GetInstanceId()
        if(T[map]) then
            T[map][ID] = nil
        end
    else
        T[self:GetGUID()] = nil
    end
end
