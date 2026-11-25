---@meta

---@class LocalPlayer
LocalPlayer = {}

-- Returns the local player's [Ped](lua://Ped) class instance.
---@return Ped ped
function LocalPlayer.GetPed() end

-- Returns the local player's [Player](lua://Player) class instance.
---@return Player player
function LocalPlayer.GetPlayer() end

-- Returns the local player's mount if any.
---@return Ped mount
function LocalPlayer.GetMount() end

-- Returns the local player's vehicle if any.
---@return Vehicle vehicle
function LocalPlayer.GetVehicle() end

-- Returns the local player's inventory list.
---@param inventoryType integer? Undocumented parameter. Defaults to 2.
---@return PlayerInventory list
function LocalPlayer.GetInventoryList(inventoryType) end

---@param coords Vector3 
---@param loadGround boolean? Optional: load ground at the coordinates before teleporting. Defaults to `true`
function LocalPlayer.Teleport(coords, loadGround) end
