<!-- markdownlint-disable -->

# Gui

## Methods

## `RegisterImGui`

```lua
function Gui.RegisterImGui(callback) end
```

Registers an ImGui function to be drawn in the menu.

NOTE: This is currently a work in progress and each script is only allowed one callback registration.

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `callback` | `function` |  |

## `RegisterIndependentImGui`

```lua
function Gui.RegisterIndependentImGui(callback) end
```

Registers an ImGui function to be drawn independently from the menu.

NOTE: Your function __MUST__ start with [ImGui.Begin](./ImGui.md.Begin) and end with [ImGui.End](./ImGui.md.End).

Please refer to the [ImGui](./ImGui.md) docs for more info.

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `callback` | `function` |  |

## `Toggle`

```lua
function Gui.Toggle() end
```

Opens and closes the menu.

## `OverrideMouse`

```lua
function Gui.OverrideMouse(state) end
```

Shows/hides the mouse cursor.

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `state` | `boolean` |  |

## `IsOpen`

```lua
function Gui.IsOpen() end
```

Returns whether the UI is currently open.

### Returns

| Type | Description |
| --- | --- |
| `boolean` |  |

## `IsUsingKeyboard`

```lua
function Gui.IsUsingKeyboard() end
```

Returns whether the UI has keyboard focus.

### Returns

| Type | Description |
| --- | --- |
| `boolean` |  |

## `IsMouseOverridden`

```lua
function Gui.IsMouseOverridden() end
```

Returns whether the mouse cursor is currently visible.

### Returns

| Type | Description |
| --- | --- |
| `boolean` |  |

## `ShowMessage`

```lua
function Gui.ShowMessage(title, msg, duration) end
```

Shows an info toast message.

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `title` | `string` | Notification title. |
| `msg` | `string` | Notification message. |
| `duration` | `integer?` | Optional notification duration in millis. Defaults to 5000 (5 seconds). |

## `ShowSuccess`

```lua
function Gui.ShowSuccess(title, msg, duration) end
```

Shows a success toast message.

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `title` | `string` | Notification title. |
| `msg` | `string` | Notification message. |
| `duration` | `integer?` | Optional notification duration in millis. Defaults to 5000 (5 seconds). |

## `ShowWarning`

```lua
function Gui.ShowWarning(title, msg, duration) end
```

Shows a warning toast message.

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `title` | `string` | Notification title. |
| `msg` | `string` | Notification message. |
| `duration` | `integer?` | Optional notification duration in millis. Defaults to 5000 (5 seconds). |

## `ShowError`

```lua
function Gui.ShowError(title, msg, duration) end
```

Shows an error toast message.

### Parameters

| Name | Type | Description |
| --- | --- | --- |
| `title` | `string` | Notification title. |
| `msg` | `string` | Notification message. |
| `duration` | `integer?` | Optional notification duration in millis. Defaults to 5000 (5 seconds). |
