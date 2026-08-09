# VidiaG Force RT-X12864 — Technical Specifications

This document contains the official technical specifications of the VidiaG Force RT-X12864 GPU.

## General Information

| Parameter             | Value                                 |
| --------------------- | ------------------------------------- |
| Project Name          | VidiaG Force RT-X12864                |
| Project Type          | Open-source microcontroller-based GPU |
| GPU Controller        | Arduino Uno R4 WiFi                   |
| Intended Display      | 128x64 monochrome GLCD                |
| Display Compatibility | KS0108-compatible                     |

## Compatibility

| Model                       | Tested | Datasheet link                                                                             | Link to purchase                             |
| --------------------------- | ------ | ------------------------------------------------------------------------------------------ | -------------------------------------------- |
| Ampire AG12864AHF           | Yes    | Unavailable                                                                                | https://aliexpress.com/item/32656645397.html |
| Crystalfontz CFAG12864A-YYH | No     | https://www.alldatasheet.com/datasheet-pdf/pdf/1162323/CRYSTAIFONTZ/CFAG12864A-YYH-VN.html | Unavailable                                  |
| Crystalfontz CFAG12864A-TMI | No     | https://www.alldatasheet.com/datasheet-pdf/pdf/1162322/CRYSTAIFONTZ/CFAG12864A-TMI-VN.html | Unavailable                                  |

## Graphics Capabilities

| Feature                  | Support           | Function                    |
| ------------------------ | ----------------- | --------------------------- |
| Framebuffer Management   | Yes               | `gpuClear()`, `gpuUpdate()` |
| Pixel Drawing            | Yes               | `gpuDrawPixel()`            |
| Line Drawing             | Yes               | `gpuDrawLine()`             |
| Rectangle Drawing        | Yes               | `gpuDrawRect()`             |
| Filled Rectangle Drawing | Yes               | `gpuFillRect()`             |
| Circle Drawing           | Yes               | `gpuDrawCircle()`           |
| Filled Circle Drawing    | Yes               | `gpuFillCircle()`           |
| Text Rendering           | Fonts 5x7 and 8x8 | `gpuDrawText()`             |
| Bitmap Rendering         | Yes               | `gpuDrawBitmap()`           |


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

| Feature               | Description                             |
| --------------------- | --------------------------------------- |
| Mounting Holes        | 8                                       |
| GLCD Connector        | Dedicated display connector             |
| Arduino Interface     | Uno R4 WiFi Shield Header               |
| I2C Connector         | GND, VCC, SCL, SDA                      |
| PCB Branding          | Vertical "VidiaG Force RT-X12864" label |
| GitHub Profile URL    | Printed on PCB near GLCD pins           |

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

| Component     | Description                       |
| ------------- | --------------------------------- |
| GPU12864.h    | CPU-side GPU driver and API       |
| ScreenI2C.ino | GPU firmware                      |
| CustomGLCD.h  | Low-level GLCD rendering driver   |
| glcdimg.py    | Bitmap conversion utility         |
| ComposeGLCD.h | Additional drier (no need to use) |


## Important Informations

> [!NOTE]
> * The CPU does not directly control the GLCD display.
> * The RT-X12864 GPU manages its own framebuffer and rendering operations.
> * The communication protocol is extensible and can support additional commands in future versions.
> * The project is released as open-source hardware and software.
