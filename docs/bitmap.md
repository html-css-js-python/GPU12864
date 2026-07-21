# Bitmap Conversion and Rendering

This document explains how to use `glcdimg.py` to convert BMP images into a format compatible with the VidiaG Force RT-X12864 GPU.

## Requirements

The bitmap converter requires Python and the Pillow library. It is recommended to use a virtual environment.

## Setup

Run the following commands in the `cpu_soft` directory:

```bash
python -m venv venv
venv\Scripts\activate
pip install -r requirements.txt
```

The `requirements.txt` file contains:

```text
Pillow
```

## Converting a BMP Image

To convert a bitmap, run:

```bash
python glcdimg.py <path_to_bmp_file>
```

Example:

```bash
python glcdimg.py images/cats.bmp
```

The converter will generate a C/C++ `PROGMEM` array that can be copied directly into an Arduino sketch.

## Recommended Image Settings

For best results, prepare images with the following settings before conversion:

| Parameter   | Recommended Value   |
| ----------- | ------------------- |
| Resolution  | 128 × 64 pixels     |
| Color Mode  | Monochrome (1-bit)  |
| File Format | BMP                 |
| Orientation | Vertical byte order |

## Example Output

The converter generates a PROGMEM-compatible bitmap array:

```cpp
const uint8_t bitmap[] PROGMEM =
{
    0x00, 0x3C, 0x42, 0x81,
    0x81, 0x42, 0x3C, 0x00
};
```

## Rendering a Bitmap

Use `gpuDrawBitmap()` to display the converted image:

```cpp
#include "GPU12864.h"

const uint8_t bitmap[] PROGMEM =
{
    // Converted bitmap data
};

void setup()
{
    gpuBegin();
    gpuClear();

    gpuDrawBitmap(0, 0, bitmap, 128, 64);

    gpuUpdate();
}

void loop()
{
}
```

## Function Parameters

| Parameter | Description                         |
| --------- | ----------------------------------- |
| `x`       | X position on the display           |
| `y`       | Y position on the display           |
| `bitmap`  | Pointer to the PROGMEM bitmap array |
| `width`   | Bitmap width in pixels              |
| `height`  | Bitmap height in pixels             |

## Notes

* Only BMP images should be passed directly to `glcdimg.py`.
* Images should be resized to 128×64 pixels before conversion if necessary.
* The GPU stores the rendered bitmap in its internal framebuffer until `gpuUpdate()` is called.
