#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"
#include "game/rdr/Ped.hpp"
#include "game/rdr/Natives.hpp"

namespace Terminus::Features
{
	class HorseSuperRun : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnTick() override
		{
			auto mount = Self::GetMount();
			if (!mount || mount.GetRagdoll())
					return;

			int handle = mount.GetHandle();
			if (TASK::IS_PED_RUNNING(handle) || TASK::IS_PED_SPRINTING(handle))
				ENTITY::APPLY_FORCE_TO_ENTITY(handle, 1, 0.0f, 20.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1, 1, 1, TRUE, FALSE, TRUE);
		}
	};

	static HorseSuperRun _HorseSuperRun{"horsesuperrun", "Super Run", "Your horse will run faster than normal"};
}