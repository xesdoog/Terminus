<!-- markdownlint-disable -->

# PlayerInventory

## Methods

## `IsValid`

```lua
function PlayerInventory:IsValid() end
```

### Returns

| Type | Description |
| --- | --- |
| `boolean` |  |

## `GetPointer`

```lua
function PlayerInventory:GetPointer() end
```

### Returns

| Type | Description |
| --- | --- |
| `Pointer` |  |

## `GetItem`

```lua
function PlayerInventory:GetItem(itemHash) end
```

Searches for an item by hash and returns it if it exists.

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `itemHash` | `integer` | JOAAT hash of the item. Example `3559569999` for trader goods. |

### Returns

| Type | Description |
| --- | --- |
| `PlayerInventoryItem?` |  |
