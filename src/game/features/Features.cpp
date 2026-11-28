#include "Features.hpp"

#include "core/commands/BoolCommand.hpp"
#include "core/commands/Commands.hpp"
#include "core/commands/HotkeySystem.hpp"
#include "core/frontend/Notifications.hpp"
#include "game/backend/FiberPool.hpp"
#include "game/backend/Players.hpp"
#include "game/backend/ScriptMgr.hpp"
#include "game/frontend/ContextMenu.hpp"
#include "game/frontend/GUI.hpp"
#include "game/rdr/Enums.hpp"
#include "game/rdr/Natives.hpp"
#include "game/backend/Self.hpp"

namespace Terminus
{
	static std::vector<Hash> controlsToDisable{
	    (Hash)NativeInputs::INPUT_LOOK_LR,
	    (Hash)NativeInputs::INPUT_LOOK_UD,
	    (Hash)NativeInputs::INPUT_AIM,
	    (Hash)NativeInputs::INPUT_MELEE_ATTACK,
	    (Hash)NativeInputs::INPUT_VEH_DRIVE_LOOK,
	    (Hash)NativeInputs::INPUT_VEH_AIM,
	    (Hash)NativeInputs::INPUT_VEH_ATTACK,
	    (Hash)NativeInputs::INPUT_VEH_ATTACK2,
	    (Hash)NativeInputs::INPUT_VEH_PASSENGER_AIM,
	    (Hash)NativeInputs::INPUT_VEH_PASSENGER_ATTACK,
	    (Hash)NativeInputs::INPUT_HORSE_AIM,
	    (Hash)NativeInputs::INPUT_HORSE_ATTACK,
	    (Hash)NativeInputs::INPUT_HORSE_ATTACK2,
	    (Hash)NativeInputs::INPUT_HORSE_GUN_LR,
	    (Hash)NativeInputs::INPUT_HORSE_GUN_UD,
	    (Hash)NativeInputs::INPUT_VEH_DRIVE_LOOK2,
	    (Hash)NativeInputs::INPUT_ATTACK,
	    (Hash)NativeInputs::INPUT_ATTACK2,
	    (Hash)NativeInputs::INPUT_NEXT_WEAPON,
	    (Hash)NativeInputs::INPUT_PREV_WEAPON,
	    (Hash)NativeInputs::INPUT_VEH_CAR_AIM,
	    (Hash)NativeInputs::INPUT_VEH_CAR_ATTACK,
	    (Hash)NativeInputs::INPUT_VEH_CAR_ATTACK2,
	    (Hash)NativeInputs::INPUT_VEH_CAR_ATTACK2,
	    (Hash)NativeInputs::INPUT_VEH_BOAT_AIM,
	    (Hash)NativeInputs::INPUT_VEH_BOAT_ATTACK,
	    (Hash)NativeInputs::INPUT_VEH_BOAT_ATTACK2,
	    (Hash)NativeInputs::INPUT_VEH_FLY_ATTACK,
	    (Hash)NativeInputs::INPUT_VEH_FLY_ATTACK2,
	    (Hash)NativeInputs::INPUT_VEH_FLY_ATTACK_CAMERA,
	    (Hash)NativeInputs::INPUT_VEH_DRAFT_ATTACK,
	    (Hash)NativeInputs::INPUT_VEH_DRAFT_ATTACK2,
	};

	void SpectateTick()
	{
		if (g_SpectateId != Players::GetSelected().GetId() && g_Spectating)
		{
			g_SpectateId = Players::GetSelected().GetId();
			NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(true, Players::GetSelected().GetPed().GetHandle());
		}

		if (g_Spectating && g_Running)
		{
			if (!Players::GetSelected().IsValid() || !Players::GetSelected().GetPed())
			{
				STREAMING::CLEAR_FOCUS();
				NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(false, Self::GetPed().GetHandle());
				g_Spectating = false;
				return;
			}

			auto playerPed = Players::GetSelected().GetPed().GetHandle();

			if (!STREAMING::IS_ENTITY_FOCUS(playerPed))
				STREAMING::SET_FOCUS_ENTITY(playerPed);

			CAM::_FORCE_LETTER_BOX_THIS_UPDATE();
			CAM::_DISABLE_CINEMATIC_MODE_THIS_FRAME();

			if (!NETWORK::NETWORK_IS_IN_SPECTATOR_MODE() && ENTITY::DOES_ENTITY_EXIST(playerPed))
			{
				NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(true, playerPed);
			}
		}
		else
		{
			if (NETWORK::NETWORK_IS_IN_SPECTATOR_MODE())
			{
				STREAMING::CLEAR_FOCUS();
				NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(false, Self::GetPed().GetHandle());
				CAM::_FORCE_LETTER_BOX_THIS_UPDATE();
				CAM::_DISABLE_CINEMATIC_MODE_THIS_FRAME();
			}
		}
	}

	void FeatureLoop()
	{
		Commands::EnableBoolCommands();
		while (true)
		{
			SpectateTick();
			*Pointers.RageSecurityInitialized = false;
			if (g_Running)
			{
				*Pointers.ExplosionBypass = true;
				Commands::RunLoopedCommands();
				if (GetForegroundWindow() == *Pointers.Hwnd && !HUD::IS_PAUSE_MENU_ACTIVE() && !GUI::IsOpen())
					g_HotkeySystem.Update();
				Self::Update();
			}
			ScriptMgr::Yield();
		}
	}

	void BlockControlsForUI()
	{
		while (g_Running)
		{
			if (GUI::IsOpen() || GUI::IsMouseOverridden() /* for Lua mouse overrides */)
			{
				if (GUI::IsUsingKeyboard())
				{
					PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
				}
				else
				{
					for (const auto& control : controlsToDisable)
						PAD::DISABLE_CONTROL_ACTION(0, control, 1);
				}
			}

			ScriptMgr::Yield();
		}
	}

	void ContextMenuTick()
	{
		while (g_Running)
		{
			ContextMenu::GameTick();
			ScriptMgr::Yield();
		}
	}
}
