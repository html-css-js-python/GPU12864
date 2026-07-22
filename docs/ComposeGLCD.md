# ComposeGLCD

ComposeGLCD is an additional GUI driver for the CPU software, built on top of the `GPU12864` graphics driver. It provides a simple and lightweight API for creating user interfaces on a 128×64 monochrome graphics display.

## Features

* Screen initialization and clearing
* Text labels and titles
* Dialog boxes with shadow effect
* Buttons with active/inactive states
* Progress bars
* Scrollable menus with selection highlight
* Centering utilities for objects and text
* Built-in error screen for invalid UI parameters

## Installation

To use ComposeGLCD, copy all driver files (`ComposeGLCD.h` and `ComposeGLCD.cpp`) from `cpu_soft/additional_drivers/ComposeGLCD/` into the folder containing your CPU project (`.ino` file).

Then include the driver in your Arduino sketch:

```cpp
#include "GPU12864.h"
#include "ComposeGLCD.h"
```

## Basic Usage

```cpp
#include "GPU12864.h"
#include "ComposeGLCD.h"

void setup()
{
    initScreen();

    uiDialogBox(centerX(110), centerY(40), 110, 40);
    uiTitle(15, "Hello");
    uiLabel(centerTextX(16), 30, "ComposeGLCD Demo");

    draw();
}

void loop()
{
}
```

## API Reference

### Screen Control

#### `initScreen()`

Initializes the GPU12864 driver, clears the screen, and updates the display.

```cpp
initScreen();
```

#### `clearScreen()`

Clears the screen and immediately updates the display.

```cpp
clearScreen();
```

#### `draw()`

Updates the display with the current contents of the graphics buffer.

```cpp
draw();
```

### System Functions

#### `uiRaiseError(const char* err1, const char* err2, const char* err3 = "")`

Displays a full-screen error message and stops program execution. This is used internally when UI elements exceed screen boundaries or have invalid sizes.

```cpp
uiRaiseError("Error line 1", "Error line 2");
```

### Positioning Utilities

#### `centerX(uint8_t objectWidth)`

Returns the X coordinate required to center an object horizontally on the screen.

```cpp
uint8_t x = centerX(50);
```

#### `centerY(uint8_t objectHeight)`

Returns the Y coordinate required to center an object vertically on the screen.

```cpp
uint8_t y = centerY(20);
```

#### `centerTextX(uint8_t len, bool font8x8 = false)`

Returns the X coordinate required to center a text string horizontally on the screen.

Parameters:

* `len` — length of the text string
* `font8x8` — set to `true` for 8×8 font, `false` for 5×7 font

```cpp
uint8_t x = centerTextX(strlen("Hello"));
```

### Text Elements

#### `uiTitle(uint8_t y, const char* text)`

Draws a centered title using the 8×8 font.

```cpp
uiTitle(10, "Settings");
```

#### `uiLabel(uint8_t x, uint8_t y, const char* text, bool color = true)`

Draws a text label using the 5×7 font.

Parameters:

* `x` — X position
* `y` — Y position
* `text` — text to display
* `color` — `true` for black text, `false` for white text

```cpp
uiLabel(5, 20, "Hello World");
```

### UI Elements

#### `uiDialogBox(uint8_t x, uint8_t y, uint8_t w, uint8_t h)`

Draws a dialog box with a shadow effect.

```cpp
uiDialogBox(10, 10, 100, 40);
```

#### `uiButton(uint8_t x, uint8_t y, uint8_t w, uint8_t h, const char* text, bool active = false)`

Draws a button with centered text.

Parameters:

* `x`, `y` — button position
* `w`, `h` — button size
* `text` — button label
* `active` — `true` for highlighted button, `false` for normal button

```cpp
uiButton(20, 20, 80, 20, "OK", true);
```

#### `uiProgressBar(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t perc)`

Draws a progress bar. The percentage value is automatically clamped to the range `0–100`.

```cpp
uiProgressBar(10, 40, 100, 12, 75);
```

#### `uiMenu(const char* items[], uint8_t itemCount, uint8_t selectedIndex)`

Draws a scrollable menu with a highlighted selected item. The menu can display up to 6 items at once and automatically scrolls when the selected item moves beyond the visible range.

Parameters:

* `items` — array of menu item strings
* `itemCount` — number of items in the array
* `selectedIndex` — index of the currently selected item

```cpp
const char* menuItems[] = {
    "Start",
    "Settings",
    "About",
    "Exit"
};

uiMenu(menuItems, 4, 0);
```

## Notes

* ComposeGLCD requires the `GPU12864` driver to be included in the project.
* All drawing operations are performed in the graphics buffer; call `draw()` to update the physical display.
* The library uses a 5×7 font for labels and an 8×8 font for titles.
* If a UI element exceeds the screen boundaries, ComposeGLCD will display an error screen using `uiRaiseError()`.
* The menu system is optimized for a 128×64 display and shows a maximum of 6 visible items at a time.
