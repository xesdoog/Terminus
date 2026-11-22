#pragma once
#include <rage/atArray.hpp>


// this stores some of the same data as the struct returned by ITEMDATABASE_FILLOUT_ITEM_INFO
// but doesn't have the same alignment and layout
class CInventoryItemInfo
{
public:
	uint32_t m_unk_000;
	uint32_t m_unk_004; // some flags? 0x7FF6 for trader goods (TODO)
	uint32_t m_hash; // 0x0008 ex: joaat("character_role_trader_goods")
	uint32_t m_category_hash; // 0x000C ex: joaat("ci_category_role_item")
	uint32_t m_unk_hash; // 0x0010 ex: joaat("core_item")
};

class CInventoryItem
{
public:
	char pad_0000[0x0018]; // 0x0 looks like a pointer to a vtable
	uint32_t m_amount; // 0x0018
	char pad_001C[0x001C];
	CInventoryItemInfo* m_info; // 0x0038
};

class CInventoryItemList
{
public:
	char pad_0000[0x0048];
	rage::atArray<CInventoryItem*> m_items; // 0x0048
};

class CInventoryNode
{
public:
	uint32_t m_id;
	char pad_0004[0x0004];
	CInventoryItemList* m_item_list; // 0x0008
	CInventoryNode* m_next_node; // 0x0010
};

class CInventoryPool
{
public:
	char pad_0000[0x1640];
	CInventoryNode** m_nodes; // 0x1640
	uint32_t m_count; // 0x1648
};
