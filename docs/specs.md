# VidiaG Force RT-X12864 — Technical Specifications

This document contains the official technical specifications of the VidiaG Force RT-X12864 GPU.

## General Information

| Parameter             | Value                                 |
| --------------------- | ------------------------------------- |
| Project Name          | VidiaG Force RT-X12864                |
| Project Type          | Open-source microcontroller-based GPU |
| GPU Controller        | Arduino Uno R4 WiFi                   |
| Intended Display      | 128x64 monochrome GLCD                |
| Display Compatibility | AG12864AHF / KS0108-compatible        |

## Graphics Capabilities

| Feature                  | Support     |
| ------------------------ | ----------- |
| Framebuffer Management   | Yes         |
| Pixel Drawing            | Yes         |
| Line Drawing             | Yes         |
| Rectangle Drawing        | Yes         |
| Filled Rectangle Drawing | Yes         |
| Circle Drawing           | Yes         |
| Filled Circle Drawing    | Yes         |
| Text Rendering           | Yes         |
| Bitmap Rendering         | Yes         |
| Font Rendering           | 5x7 and 8x8 |

## Memory

| Parameter          | Value                        |
| ------------------ | ---------------------------- |
| Framebuffer Size   | 1 KB                         |
| Display Resolution | 128 × 64 pixels              |
| Color Depth        | 1 bit per pixel (monochrome) |
| Bitmap Storage     | PROGMEM-compatible           |

## Communication

| Parameter               | Value         |
| ----------------------- | ------------- |
| Interface               | I2C           |
| Default Address         | 0x08          |
| Bus Speed               | 400 kHz       |
| Communication Direction | CPU → GPU     |
| Protocol                | Command-based |

## Electrical Characteristics

| Parameter                   | Value                                        |
| --------------------------- | -------------------------------------------- |
| Supply Voltage              | 5V                                           |
| Typical Current Consumption | Approximately 255 mA during active rendering |
| Logic Level                 | 5V compatible                                |

## Physical PCB Features

| Feature           | Description                             |
| ----------------- | --------------------------------------- |
| Mounting Holes    | 8                                       |
| GLCD Connector    | Dedicated display connector             |
| Arduino Interface | Uno R4 WiFi Shield Header               |
| I2C Connector     | GND, VCC, SCL, SDA                      |
| PCB Branding      | Vertical "VidiaG Force RT-X12864" label |
| Repository URL    | Printed on PCB near GLCD pins           |

## Rendering Pipeline

```
CPU (Master)
    |
    | I2C Commands
    v
RT-X12864 GPU
    |
    | Framebuffer Rendering
    v
CustomGLCD Driver
    |
    v
128x64 GLCD Display
```

## Software Components

| Component     | Description                     |
| ------------- | ------------------------------- |
| GPU12864.h    | CPU-side GPU driver and API     |
| ScreenI2C.ino | GPU firmware                    |
| CustomGLCD.h  | Low-level GLCD rendering driver |
| glcdimg.py    | Bitmap conversion utility       |

## Notes

* The CPU does not directly control the GLCD display.
* The RT-X12864 GPU manages its own framebuffer and rendering operations.
* The communication protocol is extensible and can support additional commands in future versions.
* The project is released as open-source hardware and software.
