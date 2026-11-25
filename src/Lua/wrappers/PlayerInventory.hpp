#include "game/rdr/Inventory.hpp"
#include "core/memory/PointerCalculator.hpp"

namespace Terminus::LuaJIT
{
	class LuaPlayerInventoryItem final
	{
	public:
		LuaPlayerInventoryItem() = default;

		explicit LuaPlayerInventoryItem(CInventoryItem* ptr) :
		    m_Ptr(ptr)
		{
		};

		bool IsValid() const noexcept;

		PointerCalculator GetPointer() const noexcept;

		uint32_t GetHash() const noexcept;
		uint32_t GetCategoryHash() const noexcept;
		uint32_t GetAmount() const noexcept;

		std::string GetName();

		void SetAmount(uint32_t amount) const noexcept;

	private:
		CInventoryItem* m_Ptr{nullptr};
		std::string m_Name{};
	};

	class LuaPlayerInventory final
	{
	public:
		LuaPlayerInventory() = default;
		explicit LuaPlayerInventory(CInventoryItemList* ptr) :
		    m_Ptr(ptr)
		{
		};

		bool IsValid() const noexcept;

		PointerCalculator GetPointer() const noexcept;
		std::optional<LuaPlayerInventoryItem> GetItem(uint32_t hash);

	private:
		CInventoryItemList* m_Ptr{nullptr};
	};
}
