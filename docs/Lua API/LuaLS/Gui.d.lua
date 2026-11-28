---@meta

---@class Gui
Gui = {}

-- Registers an ImGui function to be drawn in the menu.
--
-- NOTE: This is currently a work in progress and each script is only allowed one callback registration.
---@param callback function 
function Gui.RegisterImGui(callback) end

-- Registers an ImGui function to be drawn independently from the menu.
--
-- NOTE: Your function __MUST__ start with [ImGui.Begin](lua://ImGui.Begin) and end with [ImGui.End](lua://ImGui.End).
--
-- Please refer to the [ImGui](lua://ImGui) docs for more info.
---@param callback function 
function Gui.RegisterIndependentImGui(callback) end

-- Opens and closes the menu.
function Gui.Toggle() end

-- Shows/hides the mouse cursor.
---@param state boolean 
function Gui.OverrideMouse(state) end

-- Returns whether the UI is currently open.
---@return boolean 
function Gui.IsOpen() end

-- Returns whether the UI has keyboard focus.
---@return boolean 
function Gui.IsUsingKeyboard() end

-- Returns whether the mouse cursor is currently visible.
---@return boolean 
function Gui.IsMouseOverridden() end

-- Shows an info toast message.
---@param title string Notification title.
---@param msg string Notification message.
---@param duration integer? Optional notification duration in millis. Defaults to 5000 (5 seconds).
function Gui.ShowMessage(title, msg, duration) end

-- Shows a success toast message.
---@param title string Notification title.
---@param msg string Notification message.
---@param duration integer? Optional notification duration in millis. Defaults to 5000 (5 seconds).
function Gui.ShowSuccess(title, msg, duration) end

-- Shows a warning toast message.
---@param title string Notification title.
---@param msg string Notification message.
---@param duration integer? Optional notification duration in millis. Defaults to 5000 (5 seconds).
function Gui.ShowWarning(title, msg, duration) end

-- Shows an error toast message.
---@param title string Notification title.
---@param msg string Notification message.
---@param duration integer? Optional notification duration in millis. Defaults to 5000 (5 seconds).
function Gui.ShowError(title, msg, duration) end
