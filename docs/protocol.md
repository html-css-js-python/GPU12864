# GPU12864 I2C Communication Protocol

This document describes the communication protocol between the CPU and the VidiaG Force RT-X12864 Ti graphics processor.

The CPU communicates with the GPU using the I2C interface.

## Default Configuration

| Parameter | Value |
|---|---|
| Interface | I2C |
| Address | `0x08` |
| Speed | 400 kHz |
| Direction | CPU → GPU |

---

# Command Format

Each packet starts with a command byte.

```
[COMMAND] [DATA...]
```

---

# Commands

## Clear Screen

Command:

```
0x01
```

Description:

Clears the GPU framebuffer.

Data:

```
None
```

Example:

```
01
```

---

## Update Display

Command:

```
0x02
```

Description:

Transfers the framebuffer to the physical display.

Data:

```
None
```

Example:

```
02
```

---

## Draw Pixel

Command:

```
0x03
```

Description:

Draws one pixel.

Data:

```
[X] [Y] [COLOR]
```

Example:

```
03 10 20 01
```

Parameters:

| Parameter | Size | Description |
|---|---|---|
| X | 1 byte | Pixel X position |
| Y | 1 byte | Pixel Y position |
| COLOR | 1 byte | `1` = white, `0` = black |

---

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

Parameters:

| Parameter | Description |
|---|---|
| X0 | Start X |
| Y0 | Start Y |
| X1 | End X |
| Y1 | End Y |
| COLOR | Pixel state |

---

## Draw Rectangle

Command:

```
0x05
```

Data:

```
[X] [Y] [WIDTH] [HEIGHT] [COLOR]
```

---

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
| `0x00` | 5x7 |
| `0x01` | 8x8 |

Example:

```
07 01 01 00 01 HELLO
```

---

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

---

## Bitmap Data

Command:

```
0x09
```

Transfers bitmap data.

Data:

```
[BYTE 0] [BYTE 1] ... [BYTE N]
```

Bitmap format:

- 1 bit per pixel
- Vertical byte orientation
- Stored in PROGMEM

---

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

---

# Example Communication

Draw pixel at position X=10, Y=10:

CPU sends:

```
03 0A 0A 01
```

GPU executes:

```
glcdDrawPixel(10, 10, true);
```

---

# Rendering Pipeline

The GPU uses a framebuffer.

Typical workflow:

```
CPU
 |
 | I2C commands
 v
GPU12864
 |
 | framebuffer update
 v
CustomGLCD Driver
 |
 v
128x64 GLCD
```

---

# Notes

- The CPU does not directly control the display.
- The GPU handles:
  - framebuffer management
  - text rendering
  - shapes
  - bitmap rendering
  - display updates

- New commands can be added in future versions.

Protocol version:

```
v1.0
```
