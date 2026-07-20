#ifndef GPU12864_H
#define GPU12864_H

#include <Arduino.h>
#include <Wire.h>
#include <avr/pgmspace.h>

#define GPU_ADDR 0x08

#define CMD_CLEAR         0x01
#define CMD_UPDATE        0x02
#define CMD_PIXEL         0x03
#define CMD_LINE          0x04
#define CMD_RECT          0x05
#define CMD_FILLRECT      0x06
#define CMD_TEXT          0x07
#define CMD_BITMAP_START  0x08
#define CMD_BITMAP_DATA   0x09
#define CMD_BITMAP_END    0x0A
#define CMD_CIRCLE        0x0B
#define CMD_FILLCIRCLE    0x0C

#define FONT_5X7 0x00
#define FONT_8X8 0x01

inline void gpuBegin()
{
  delay(1200); // Give some time for GPU's bootloader!
  Wire.begin();
  Wire.setClock(400000);
}

inline void gpuClear()
{
  Wire.beginTransmission(GPU_ADDR);
  Wire.write(CMD_CLEAR);
  Wire.endTransmission();
}

inline void gpuUpdate()
{
  Wire.beginTransmission(GPU_ADDR);
  Wire.write(CMD_UPDATE);
  Wire.endTransmission();
}

inline void gpuDrawPixel(uint8_t x, uint8_t y, bool color = true)
{
  Wire.beginTransmission(GPU_ADDR);
  Wire.write(CMD_PIXEL);
  Wire.write(x);
  Wire.write(y);
  Wire.write(color);
  Wire.endTransmission();
}

inline void gpuDrawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, bool color = true)
{
  Wire.beginTransmission(GPU_ADDR);
  Wire.write(CMD_LINE);
  Wire.write(x0);
  Wire.write(y0);
  Wire.write(x1);
  Wire.write(y1);
  Wire.write(color);
  Wire.endTransmission();
}

inline void gpuDrawRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, bool color = true)
{
  Wire.beginTransmission(GPU_ADDR);
  Wire.write(CMD_RECT);
  Wire.write(x);
  Wire.write(y);
  Wire.write(w);
  Wire.write(h);
  Wire.write(color);
  Wire.endTransmission();
}

inline void gpuFillRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, bool color = true)
{
  Wire.beginTransmission(GPU_ADDR);
  Wire.write(CMD_FILLRECT);
  Wire.write(x);
  Wire.write(y);
  Wire.write(w);
  Wire.write(h);
  Wire.write(color);
  Wire.endTransmission();
}

inline void gpuDrawCircle(uint8_t x, uint8_t y, uint8_t r, bool color = true)
{
  Wire.beginTransmission(GPU_ADDR);
  Wire.write(CMD_CIRCLE);
  Wire.write(x);
  Wire.write(y);
  Wire.write(r);
  Wire.write(color);
  Wire.endTransmission();
}

inline void gpuFillCircle(uint8_t x, uint8_t y, uint8_t r, bool color = true)
{
  Wire.beginTransmission(GPU_ADDR);
  Wire.write(CMD_FILLCIRCLE);
  Wire.write(x);
  Wire.write(y);
  Wire.write(r);
  Wire.write(color);
  Wire.endTransmission();
}

inline void gpuDrawText(uint8_t x, uint8_t y, const char* text, uint8_t fontId, bool color = true)
{
  Wire.beginTransmission(GPU_ADDR);
  Wire.write(CMD_TEXT);
  Wire.write(x);
  Wire.write(y);
  Wire.write(fontId);
  Wire.write(color);

  while (*text)
  {
    Wire.write(*text++);
  }

  Wire.endTransmission();
}

inline void gpuDrawBitmap(uint8_t x, uint8_t y,
                          const uint8_t *bitmap,
                          uint8_t width, uint8_t height)
{
  uint16_t size = width * ((height + 7) / 8);

  Wire.beginTransmission(GPU_ADDR);
  Wire.write(CMD_BITMAP_START);
  Wire.write(x);
  Wire.write(y);
  Wire.write(width);
  Wire.write(height);
  Wire.endTransmission();

  for (uint16_t i = 0; i < size; i += 8)
  {
    Wire.beginTransmission(GPU_ADDR);
    Wire.write(CMD_BITMAP_DATA);

    uint8_t chunk = (size - i >= 8) ? 8 : (size - i);

    for (uint8_t j = 0; j < chunk; j++)
    {
      Wire.write(pgm_read_byte(&bitmap[i + j]));
    }

    Wire.endTransmission();
  }

  Wire.beginTransmission(GPU_ADDR);
  Wire.write(CMD_BITMAP_END);
  Wire.endTransmission();
}

#endif