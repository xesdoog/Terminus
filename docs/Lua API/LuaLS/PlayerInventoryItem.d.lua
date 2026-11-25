---@meta

---@class PlayerInventoryItem
PlayerInventoryItem = {}

---@return boolean 
function PlayerInventoryItem:IsValid() end

---@return Pointer 
function PlayerInventoryItem:GetPointer() end

-- RAGE JOAAT hash
---@return integer 
function PlayerInventoryItem:GetHash() end

-- RAGE JOAAT hash
---@return integer 
function PlayerInventoryItem:GetCategoryHash() end

---@return string 
function PlayerInventoryItem:GetName() end

-- Returns the current amount of this item.
---@return integer amount
function PlayerInventoryItem:GetAmount() end

---@param amount integer 
function PlayerInventoryItem:SetAmount(amount) end
