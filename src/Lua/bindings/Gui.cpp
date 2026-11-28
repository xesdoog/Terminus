#pragma once

#include "../LuaLibrary.hpp"
#include "../LuaModule.hpp"
#include "game/frontend/GUI.hpp"
#include "core/frontend/Notifications.hpp"


namespace Terminus::LuaJIT
{
	class LuaGuiLib : public LuaLibrary
	{
		using LuaLibrary::LuaLibrary;

	public:
		void Register(sol::state& L) override
		{
			// clang-format off


			/*@terminus.table Gui
			* 
			@*/
			auto guiTable = L["Gui"].get_or_create<sol::table>();

			/*@terminus.function Gui.RegisterImGui Registers an ImGui function to be drawn in the menu.~~NOTE: This is currently a work in progress and each script is only allowed one callback registration.
			* param callback<function>
			@*/
			guiTable["RegisterImGui"] = [](sol::protected_function func, sol::this_state s) {
				sol::state_view lua(s);
				auto mod = GetModuleFromLuaState(lua);
				if (!mod)
					return;

				if (mod->m_GuiCallback.valid())
				{
					LOGF(WARNING, "Module '{}' already has an ImGui callback!", mod->GetName());
					return;
				}

				mod->m_GuiCallback = std::move(func);
			};

			/*@terminus.function Gui.RegisterIndependentImGui Registers an ImGui function to be drawn independently from the menu.~~NOTE: Your function __MUST__ start with [ImGui.Begin](lua://ImGui.Begin) and end with [ImGui.End](lua://ImGui.End).~~Please refer to the [ImGui](lua://ImGui) docs for more info.
			* param callback<function>
			@*/
			guiTable["RegisterIndependentImGui"] = [](sol::protected_function callback, sol::this_state s) {
				sol::state_view lua(s);
				if (auto mod = GetModuleFromLuaState(lua))
					mod->m_IndependentGuiCallbacks.push_back(std::move(callback));
			};

			/*@terminus.function Gui.Toggle Opens and closes the menu.
			*
			@*/
			guiTable["Toggle"] = []() { GUI::Toggle(); };

			/*@terminus.function Gui.OverrideMouse Shows/hides the mouse cursor.
			* param state<boolean>
			@*/
			guiTable["OverrideMouse"] = [](bool state) { GUI::OverrideMouse(state); };

			/*@terminus.function Gui.IsOpen Returns whether the UI is currently open.
			* return boolean
			@*/
			guiTable["IsOpen"] = []() { return GUI::IsOpen(); };

			/*@terminus.function Gui.IsUsingKeyboard Returns whether the UI has keyboard focus.
			* return boolean
			@*/
			guiTable["IsUsingKeyboard"] = []() { return GUI::IsUsingKeyboard(); };

			/*@terminus.function Gui.IsMouseOverridden Returns whether the mouse cursor is currently visible.
			* return boolean
			@*/
			guiTable["IsMouseOverridden"] = []() { return GUI::IsMouseOverridden(); };

			/*@terminus.function Gui.ShowMessage Shows an info toast message.
			* param title<string> Notification title.
			* param msg<string> Notification message.
			* param duration<integer?> Optional notification duration in millis. Defaults to 5000 (5 seconds).
			@*/
			guiTable["ShowMessage"] = [](sol::this_state s, const std::string& title, const std::string& msg, sol::optional<int> duration) {
				sol::state_view lua(s);
				Notifications::Show(title, msg, NotificationType::Info, duration.value_or(5000));
			};

			/*@terminus.function Gui.ShowSuccess Shows a success toast message.
			* param title<string> Notification title.
			* param msg<string> Notification message.
			* param duration<integer?> Optional notification duration in millis. Defaults to 5000 (5 seconds).
			@*/
			guiTable["ShowSuccess"] = [](sol::this_state s, const std::string& title, const std::string& msg, sol::optional<int> duration) {
				sol::state_view lua(s);
				Notifications::Show(title, msg, NotificationType::Success, duration.value_or(5000));
			};

			/*@terminus.function Gui.ShowWarning Shows a warning toast message.
			* param title<string> Notification title.
			* param msg<string> Notification message.
			* param duration<integer?> Optional notification duration in millis. Defaults to 5000 (5 seconds).
			@*/
			guiTable["ShowWarning"] = [](sol::this_state s, const std::string& title, const std::string& msg, sol::optional<int> duration) {
				sol::state_view lua(s);
				Notifications::Show(title, msg, NotificationType::Warning, duration.value_or(5000));
			};

			/*@terminus.function Gui.ShowError Shows an error toast message.
			* param title<string> Notification title.
			* param msg<string> Notification message.
			* param duration<integer?> Optional notification duration in millis. Defaults to 5000 (5 seconds).
			@*/
			guiTable["ShowError"] = [](sol::this_state s, const std::string& title, const std::string& msg, sol::optional<int> duration) {
				sol::state_view lua(s);
				Notifications::Show(title, msg, NotificationType::Error, duration.value_or(5000));
			};
		}
	};

	LuaGuiLib _LuaGuiLib;
}
