---@meta

---@class PlayerInventory
PlayerInventory = {}

---@return boolean 
function PlayerInventory:IsValid() end

---@return Pointer 
function PlayerInventory:GetPointer() end

-- Searches for an item by hash and returns it if it exists.
---@param itemHash integer JOAAT hash of the item. Example `3559569999` for trader goods.
---@return PlayerInventoryItem? 
function PlayerInventory:GetItem(itemHash) end
