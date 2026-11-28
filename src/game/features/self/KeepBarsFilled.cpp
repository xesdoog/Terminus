#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"
#include "game/rdr/Natives.hpp"

namespace Terminus::Features
{
	static BoolCommand _Deadeye{"keepdeadeyefilled", "Deadeye##bars", "Keep Deadeye Bar Filled", true};
	static BoolCommand _Stamina{"keepstaminafilled", "Stamina##bars", "Keep Stamina Bar Filled", true};
	static BoolCommand _Health{"keephealthfilled", "Health##bars", "Keep Health Bar Filled", true};

	class KeepBarsFilled : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnTick() override
		{
			auto ped = Self::GetPed();
			if (!ped || ped.IsDead())
				return;

			int player_id    = Self::GetPlayer().GetId();
			auto health_bar  = ped.GetHealth();
			auto stamina_bar = PLAYER::_GET_PLAYER_STAMINA(player_id);
			auto deadeye_bar = PLAYER::_GET_PLAYER_DEAD_EYE(player_id);

			auto max_health  = ped.GetMaxHealth();
			auto max_stamina = PED::_GET_PED_MAX_STAMINA(ped.GetHandle());
			auto max_deadeye = PLAYER::_GET_PLAYER_MAX_DEAD_EYE(player_id, false);

			if (health_bar < max_health && _Health.GetState())
				ped.SetHealth(max_health);

			if (stamina_bar < max_stamina && _Stamina.GetState())
				PED::_CHANGE_PED_STAMINA(ped.GetHandle(), max_stamina - stamina_bar);

			if (deadeye_bar < max_deadeye && _Deadeye.GetState())
				PLAYER::_SPECIAL_ABILITY_RESTORE_BY_AMOUNT(player_id, max_deadeye, 0, 0, 1);
		}
	};

	static KeepBarsFilled _KeepBarsFilled{"keepbarsfilled", "Keep Bars Filled", "Keeps your Health, Stamina and Deadeye filled"};
}