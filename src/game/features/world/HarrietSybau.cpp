#include "core/commands/BoolCommand.hpp"
#include "game/backend/NativeHooks.hpp"
#include "game/rdr/Natives.hpp"

namespace Terminus::Features
{
	static void DecorExistOnHook(rage::scrNativeCallContext* ctx);

	class HarrietSybau : public BoolCommand
	{
		using BoolCommand::BoolCommand;

		virtual void OnEnable() override
		{
			NativeHooks::AddHook("net_main_offline"_J, NativeIndex::DECOR_EXIST_ON, &DecorExistOnHook);
			NativeHooks::AddHook("net_main_tlg_offline"_J, NativeIndex::DECOR_EXIST_ON, &DecorExistOnHook);
		}
	};

	static HarrietSybau _HarrietSybau{"harrietsybau", "Shut Up, Harriet!", "Stops Harriet from bitching about you killing animals."};

	// credits to gir489 https://www.unknowncheats.me/forum/3878302-post635.html
	static void DecorExistOnHook(rage::scrNativeCallContext* ctx)
	{
		int entity             = ctx->GetArg<int>(0);
		const char* strPropery = ctx->GetArg<const char*>(1);

		if (_HarrietSybau.GetState() && strPropery && std::strcmp(strPropery, "ReputationFlags") == 0 && ENTITY::GET_IS_ANIMAL(entity))
		{
			int decor = DECORATOR::DECOR_GET_INT(entity, "ReputationFlags");
			decor |= 1;
			DECORATOR::DECOR_SET_INT(entity, "ReputationFlags", decor);
			ctx->SetReturnValue(TRUE);
			return;
		}

		NativeInvoker::GetNativeHandler(NativeIndex::DECOR_EXIST_ON)(ctx);
	}
}
