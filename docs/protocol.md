# RT-X12864 I2C Communication Protocol

This document describes the communication protocol between the CPU and the VidiaG Force RT-X12864 graphics processor.

The CPU communicates with the GPU using the I2C interface.

# Default Configuration

| Parameter | Value |
|---|---|
| Interface | I2C |
| Device Address | `0x08` |
| Bus Speed | 400 kHz |
| Communication Direction | CPU → GPU |

# Packet Format

Every command sent to the GPU starts with a command byte.

```
[COMMAND] [DATA...]
```

The GPU receives commands and executes them using its internal framebuffer.

# Command List

## Clear Framebuffer

Command:

```
0x01
```

Description:

Clears the internal GPU framebuffer.

Data:

```
None
```

Example:

```
01
```

## Update Display

Command:

```
0x02
```

Description:

Updates the physical GLCD from the GPU framebuffer.

Data:

```
None
```

Example:

```
02
```

## Draw Pixel

Command:

```
0x03
```

Data:

```
[X] [Y] [COLOR]
```

Parameters:

| Parameter | Size | Description |
|---|---|---|
| X | 1 byte | X coordinate (0-127) |
| Y | 1 byte | Y coordinate (0-63) |
| COLOR | 1 byte | `1` = ON, `0` = OFF |

Example:

```
03 0A 0A 01
```

Draws a pixel at:

```
X = 10
Y = 10
```

## Draw Line

Command:

```
0x04
```

Data:

```
[X0] [Y0] [X1] [Y1] [COLOR]
```

Example:

```
04 00 00 7F 3F 01
```

Draws a line from:

```
(0,0) → (127,63)
```

## Draw Rectangle

Command:

```
0x05
```

Data:

```
[X] [Y] [WIDTH] [HEIGHT] [COLOR]
```

## Fill Rectangle

Command:

```
0x06
```

Data:

```
[X] [Y] [WIDTH] [HEIGHT] [COLOR]
```

---

## Draw Text

Command:

```
0x07
```

Data:

```
[X] [Y] [FONT] [COLOR] [TEXT]
```

Fonts:

| ID | Font |
|---|---|
| `0x00` | FONT_5X7 |
| `0x01` | FONT_8X8 |

Example:

```
07 01 01 01 HELLO
```

## Bitmap Start

Command:

```
0x08
```

Starts bitmap transfer.

Data:

```
[X] [Y] [WIDTH] [HEIGHT]
```

## Bitmap Data

Command:

```
0x09
```

Transfers bitmap bytes.

Data:

```
[BYTE0] [BYTE1] ... [BYTEN]
```

Bitmap format:

- 1 bit per pixel
- Stored vertically
- Compatible with `PROGMEM` bitmap arrays

## Bitmap End

Command:

```
0x0A
```

Ends bitmap transfer.

Data:

```
None
```

# Rendering Pipeline

The RT-X12864 uses a GPU-style rendering architecture:

```
CPU
 |
 | I2C Commands
 v
RT-X12864 GPU
 |
 | Framebuffer
 v
CustomGLCD Driver
 |
 v
128x64 GLCD Display
```

# GPU Responsibilities

The GPU handles:

- Framebuffer management
- Pixel drawing
- Line rendering
- Shape rendering
- Text rendering
- Font handling
- Bitmap rendering
- Display updates

The CPU only sends high-level drawing commands.

# Example Workflow

Drawing text:

CPU sends:

```
CMD_TEXT
X
Y
FONT
COLOR
TEXT DATA
```

GPU performs:

```
Text rendering
        |
        v
Framebuffer update
        |
        v
Display refresh
```

# Extending The Protocol

New commands can be added by:

1. Adding a new command ID.
2. Implementing command handling in GPU firmware.
3. Adding a matching function in the CPU driver.

Example:

```
CMD_CUSTOM = 0x20
```

# Protocol Version

```
v1.0
```
