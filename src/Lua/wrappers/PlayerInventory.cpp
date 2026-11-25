#include "PlayerInventory.hpp"
#include "game/rdr/Natives.hpp"

namespace Terminus::LuaJIT
{
	bool LuaPlayerInventoryItem::IsValid() const noexcept
	{
		return m_Ptr != nullptr;
	}

	PointerCalculator LuaPlayerInventoryItem::GetPointer() const noexcept
	{
		return PointerCalculator(reinterpret_cast<void*>(m_Ptr));
	}

	uint32_t LuaPlayerInventoryItem::GetHash() const noexcept
	{
		if (!m_Ptr)
			return 0;

		auto* info = m_Ptr->m_info;
		return info ? info->m_hash : 0;
	}

	uint32_t LuaPlayerInventoryItem::GetCategoryHash() const noexcept
	{
		if (!m_Ptr)
			return 0;

		auto* info = m_Ptr->m_info;
		return info ? info->m_category_hash : 0;
	}

	uint32_t LuaPlayerInventoryItem::GetAmount() const noexcept
	{
		return m_Ptr ? m_Ptr->m_amount : 0;
	}

	std::string LuaPlayerInventoryItem::GetName()
	{
		if (m_Ptr && m_Name.empty())
		{
			uint32_t hash = GetHash();
			m_Name        = HUD::GET_STRING_FROM_HASH_KEY(hash);
			if (m_Name.empty())
				m_Name = std::to_string(hash);
		}

		return m_Name;
	}

	void LuaPlayerInventoryItem::SetAmount(uint32_t amount) const noexcept
	{
		if (m_Ptr)
			m_Ptr->m_amount = amount;
	}

	////////////////////////////////////// LuaPlayerInventory //////////////////////////////////////

	bool LuaPlayerInventory::IsValid() const noexcept
	{
		return m_Ptr != nullptr;
	}

	PointerCalculator LuaPlayerInventory::GetPointer() const noexcept
	{
		return PointerCalculator(reinterpret_cast<void*>(m_Ptr));
	}

	std::optional<LuaPlayerInventoryItem> LuaPlayerInventory::GetItem(uint32_t hash)
	{
		if (m_Ptr)
		{
			for (auto* item : m_Ptr->m_items)
			{
				if (item && item->m_info && item->m_info->m_hash == hash)
					return LuaPlayerInventoryItem(item);
			}
		}

		return std::nullopt;
	}
}
