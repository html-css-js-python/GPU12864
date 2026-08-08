# VidiaG Force RT-X12864

VidiaG Force RT-X12864 is an open-source microcontroller-based GPU designed for 128x64 GLCD displays. It acts as a dedicated graphics processing unit, handling framebuffer management, rendering, and communication with the display independently from the main CPU.

Unlike a typical GLCD library, the CPU does not directly control the display. Instead, it sends high-level drawing commands to the RT-X12864 GPU, which performs all rendering operations and updates the GLCD using its own framebuffer.

## Features

* Dedicated GPU architecture for 128x64 GLCD displays
* Independent framebuffer management
* I2C communication between CPU and GPU
* Text rendering with 5x7 and 8x8 fonts
* Pixel, line, rectangle, and filled rectangle drawing
* Circle and filled circle rendering
* Bitmap rendering from PROGMEM
* Open-source hardware and software
* Expandable command-based communication protocol

## Architecture

```
CPU (Master)
    |
    | I2C Commands (400 kHz)
    v
VidiaG Force RT-X12864 GPU
    |
    | Framebuffer Rendering
    v
CustomGLCD Driver
    |
    v
128x64 GLCD Display
```

The CPU only sends high-level commands such as drawing pixels, lines, text, and bitmaps. The GPU handles all low-level rendering and display communication.

## Hardware

| Component         | Description                                                |
| ----------------- | ---------------------------------------------------------- |
| GPU               | Arduino Uno R4 WiFi                                        |
| CPU               | Any compatible I2C master (tested with Arduino Nano Every) |
| Display           | AG12864AHF / KS0108-compatible 128x64 GLCD                 |
| Interface         | I2C (400 kHz)                                              |
| VRAM              | 1 KB framebuffer                                           |
| Power Consumption | Approximately 255 mA during active rendering               |

## Installation

1. Upload `gpu_soft/ScreenI2C/ScreenI2C.ino` to the Arduino Uno R4 WiFi.
2. Connect the GLCD display to the GPU according to the schematic.
3. Connect the CPU board to the GPU via I2C using `GND`, `VCC`, `SCL`, and `SDA`.
4. Include `GPU12864.h` in your CPU project.
5. Call `gpuBegin()` before using any GPU functions.

## Basic Usage

```cpp
#include "GPU12864.h"

void setup()
{
    gpuBegin();
    gpuClear();

    gpuDrawText(1, 1, "Hello, World!", FONT_5X7);
    gpuDrawLine(0, 0, 127, 63);

    gpuUpdate();
}

void loop()
{
}
```

## Available Commands

| Command                                                                                     | Function                                                     |
| ------------------------------------------------------------------------------------------- | ------------------------------------------------------------ |
| `gpuBegin()`                                                                                | Begins communication between CPU and GPU (takes about 1.2 s) |
| `gpuClear()`                                                                                | Clear the framebuffer                                        |
| `gpuUpdate()`                                                                               | Send the framebuffer to the GLCD                             |
| `gpuDrawPixel(uint8_t x, uint8_t y, bool color = true)`                                     | Draw a single pixel                                          |
| `gpuDrawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, bool color = true)`            | Draw a line                                                  |
| `gpuDrawRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, bool color = true)`                | Draw a rectangle                                             |
| `gpuFillRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, bool color = true)`                | Draw a filled rectangle                                      |
| `gpuDrawCircle(uint8_t x, uint8_t y, uint8_t r, bool color = true)`                         | Draw a circle                                                |
| `gpuFillCircle(uint8_t x, uint8_t y, uint8_t r, bool color = true)`                         | Draw a filled circle                                         |
| `gpuDrawText(uint8_t x, uint8_t y, const char* text, uint8_t fontId, bool color = true)`    | Render text                                                  |
| `gpuDrawBitmap(uint8_t x, uint8_t y, const uint8_t *bitmap, uint8_t width, uint8_t height)` | Render a bitmap                                              |

The API is function-based rather than object-oriented.

> Functions, yes, functions. **Because yes**.
>
> It was simpler to implement this way. :P

## Demos

The repository includes several demonstration programs:

* Hello World
* Font rendering demo
* Shapes and primitives demo
* Sine wave graph
* Live scrolling graph
* Bouncing ball animation
* Rotating 3D cube
* Benchmark demo
* Full demonstration sequence

## PCB

The repository includes the complete KiCad project and manufacturing files for the RT-X12864 adapter PCB, including:

* `.kicad_pro` project file
* `.kicad_sch` schematic
* `.kicad_pcb` PCB layout
* Gerber files (`.gbr`)
* Drill files (`.drl`)
* `gerber.zip` ready for PCB fabrication

## Documentation

* [Technical Specification](docs/specs.md)
* [Bitmap Conversion and Rendering](docs/bitmap.md)
* [I2C Communication Protocol](docs/protocol.md)
* [Additional Drivers](docs/additional_drivers.md)
* [Fun Specifications](/fun_specs.md)

## License

This project is released as open-source hardware and software. You are free to study, modify, and distribute it under the terms of the chosen license.
