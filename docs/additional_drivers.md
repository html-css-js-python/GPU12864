# Additional Drivers

The `cpu_soft/additional_drivers/` directory contains optional drivers and libraries that extend the functionality of the CPU software. These drivers are not required for the basic project, but can be added when additional features are needed.

## Current Additional Drivers

* [ComposeGLCD](ComposeGLCD.md) — GUI library providing widgets such as buttons, dialog boxes, menus, labels, titles, and progress bars.

## How to Use a Driver

To use any driver from the `additional_drivers` directory, simply copy all files of the selected driver (`.h` and `.cpp`) into the CPU project folder.

For example, to use `ComposeGLCD`, copy:

```text
ComposeGLCD.h
ComposeGLCD.cpp
```

into the folder containing your CPU source code (`.ino` file), then include the driver in your project:

```cpp
#include "ComposeGLCD.h"
```
