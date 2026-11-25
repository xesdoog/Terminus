#pragma once

#include "../LuaLibrary.hpp"
#include "../LuaModule.hpp"
#include "../wrappers/PlayerInventory.hpp"
#include "game/backend/Self.hpp"
#include "game/pointers/Pointers.hpp"
#include "util/teleport.hpp"

namespace Terminus::LuaJIT
{
	class LuaSelfLib : public LuaLibrary
	{
		using LuaLibrary::LuaLibrary;

	public:
		void Register(sol::state& L) override
		{
			// clang-format off

			/*@terminus.class PlayerInventoryItem
			* description
				Represents an item in your inventory. Can not be constructed.

			* method IsValid
			* return boolean

			* method GetPointer
			* return Pointer

			* method GetHash RAGE JOAAT hash
			* return integer

			* method GetCategoryHash RAGE JOAAT hash
			* return integer

			* method GetName
			* return string

			* method GetAmount Returns the current amount of this item.
			* return integer amount
			
			* method SetAmount
			* param amount<integer>
			@*/
			L.new_usertype<LuaPlayerInventoryItem>("PlayerInventoryItem", sol::no_constructor, 
				"IsValid",         &LuaPlayerInventoryItem::IsValid,
				"GetPointer",      &LuaPlayerInventoryItem::GetPointer,
				"GetHash",	       &LuaPlayerInventoryItem::GetHash,
				"GetCategoryHash", &LuaPlayerInventoryItem::GetCategoryHash,
				"GetAmount",	   &LuaPlayerInventoryItem::GetAmount,
				"SetAmount",       &LuaPlayerInventoryItem::SetAmount
			);

			/*@terminus.class PlayerInventory
			* description
				Represents the player's inventory list. Can not be constructed.

			* method IsValid
			* return boolean

			* method GetPointer
			* return Pointer

			* method GetItem Searches for an item by hash and returns it if it exists.
			* param itemHash<integer> JOAAT hash of the item. Example `3559569999` for trader goods.
			* return PlayerInventoryItem?
			@*/
			L.new_usertype<LuaPlayerInventory>("PlayerInventory", sol::no_constructor,
				"IsValid",    &LuaPlayerInventory::IsValid,
				"GetPointer", &LuaPlayerInventory::GetPointer,
				"GetItem",    &LuaPlayerInventory::GetItem
			);

			// clang-format on

			/*@terminus.table LocalPlayer
			* description
				A simple Local Player wrapper.

			* function GetPed Returns the local player's [Ped](lua://Ped) class instance.
			* return Ped ped

			* function GetPlayer Returns the local player's [Player](lua://Player) class instance.
			* return Player player

			* function GetMount Returns the local player's mount if any.
			* return Ped mount

			* function GetVehicle Returns the local player's vehicle if any.
			* return Vehicle vehicle

			* function GetInventoryList Returns the local player's inventory list.
			* param inventoryType<integer?> Undocumented parameter. Defaults to 2.
			* return PlayerInventory list

			* function Teleport
			* param coords<Vector3>
			* param loadGround<boolean?> Optional: load ground at the coordinates before teleporting. Defaults to `true`
			@*/
			auto selfTbl = L["LocalPlayer"].get_or_create<sol::table>();
			
			selfTbl["GetPed"] = []() {
				return Self::GetPed();
			};
			
			selfTbl["GetPlayer"] = []() {
				return Self::GetPlayer();
			};
			
			selfTbl["GetMount"] = []() {
				return Self::GetMount();
			};
			
			selfTbl["GetVehicle"] = []() {
				return Self::GetVehicle();
			};
			
			selfTbl["GetInventoryList"] = [](sol::optional<int> inventoryType) {
				if (!(Pointers.InventoryPool && Pointers.GetInventoryList))
				{
					LOG(FATAL) << "inventory data is null!";
					return LuaPlayerInventory();
				}

				auto* list = Pointers.GetInventoryList(*reinterpret_cast<uint64_t*>(Pointers.InventoryPool), inventoryType.value_or(2));
				if (!list)
					LOG(FATAL) << "GetInventoryList returned garbage data!";

				return LuaPlayerInventory(list);
			};
			
			selfTbl["Teleport"] = [](Vector3 coords, sol::optional<bool> loadGround) {
				if (!Teleport::TeleportEntity(Self::GetPed().GetHandle(), coords, loadGround.value_or(true)))
					LOG(WARNING) << "Failed to teleport LocalPlayer to coordinates!";
			};
		}
	};

	LuaSelfLib _LuaSelfLib;
}
