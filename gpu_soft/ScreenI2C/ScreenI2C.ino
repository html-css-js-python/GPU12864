#include <Wire.h>
#include "CustomGLCD.h"

#define GPU_ADDR 0x08

#define CMD_CLEAR        0x01
#define CMD_UPDATE       0x02
#define CMD_PIXEL        0x03
#define CMD_LINE         0x04
#define CMD_RECT         0x05
#define CMD_FILLRECT     0x06
#define CMD_TEXT         0x07
#define CMD_BITMAP_START 0x08
#define CMD_BITMAP_DATA  0x09
#define CMD_BITMAP_END   0x0A
#define CMD_CIRCLE       0x0B
#define CMD_FILLCIRCLE   0x0C

#define FONT_5X7         0x00
#define FONT_8X8         0x01

uint16_t bitmapIndex = 0;
uint8_t bitmapX = 0;
uint8_t bitmapY = 0;
uint8_t bitmapW = 0;
uint8_t bitmapH = 0;

void receiveEvent(int howMany)
{
  if (howMany < 1) return;

  uint8_t cmd = Wire.read();

  switch (cmd)
  {
    case CMD_CLEAR:
      glcdClear();
      break;

    case CMD_UPDATE:
      glcdUpdate();
      break;

    case CMD_PIXEL:
    {
      if (Wire.available() >= 3)
      {
        uint8_t x = Wire.read();
        uint8_t y = Wire.read();
        bool color = Wire.read();

        glcdDrawPixel(x, y, color);
      }
      break;
    }

    case CMD_LINE:
    {
      if (Wire.available() >= 5)
      {
        uint8_t x0 = Wire.read();
        uint8_t y0 = Wire.read();
        uint8_t x1 = Wire.read();
        uint8_t y1 = Wire.read();
        bool color = Wire.read();

        glcdDrawLine(x0, y0, x1, y1, color);
      }
      break;
    }

    case CMD_RECT:
    {
      if (Wire.available() >= 5)
      {
        uint8_t x = Wire.read();
        uint8_t y = Wire.read();
        uint8_t w = Wire.read();
        uint8_t h = Wire.read();
        bool color = Wire.read();

        glcdDrawRect(x, y, w, h, color);
      }
      break;
    }

    case CMD_FILLRECT:
    {
      if (Wire.available() >= 5)
      {
        uint8_t x = Wire.read();
        uint8_t y = Wire.read();
        uint8_t w = Wire.read();
        uint8_t h = Wire.read();
        bool color = Wire.read();

        glcdFillRect(x, y, w, h, color);
      }
      break;
    }

    case CMD_TEXT:
    {
      if (Wire.available() >= 4)
      {
        uint8_t x = Wire.read();
        uint8_t y = Wire.read();
        uint8_t fontId = Wire.read();
        bool color = Wire.read();

        char text[27];
        uint8_t i = 0;

        while (Wire.available() && i < 26)
        {
          text[i++] = Wire.read();
        }

        text[i] = '\0';

        const GLCD_Font* font = &Font5x7;

        if (fontId == FONT_8X8)
          font = &Font8x8;

        glcdDrawText(x, y, text, *font, color);
      }
      break;
    }

    case CMD_BITMAP_START:
    {
      bitmapX = Wire.read();
      bitmapY = Wire.read();
      bitmapW = Wire.read();
      bitmapH = Wire.read();
      bitmapIndex = 0;
      break;
    }

    case CMD_BITMAP_DATA:
    {
      while (Wire.available())
      {
        uint8_t b = Wire.read();

        uint16_t xx = bitmapIndex % bitmapW;
        uint16_t yy = (bitmapIndex / bitmapW) * 8;

        for (uint8_t bit = 0; bit < 8; bit++)
        {
          if (yy + bit < bitmapH)
          {
            bool pixel = b & (1 << bit);
            glcdDrawPixel(bitmapX + xx, bitmapY + yy + bit, pixel);
          }
        }

        bitmapIndex++;
      }
      break;
    }

    case CMD_BITMAP_END:
    {
      break;
    }

    case CMD_CIRCLE:
    {
      if (Wire.available() >= 4)
      {
        uint8_t x = Wire.read();
        uint8_t y = Wire.read();
        uint8_t r = Wire.read();
        bool color = Wire.read();

        glcdDrawCircle(x, y, r, color);
      }
      break;
    }

    case CMD_FILLCIRCLE:
    {
      if (Wire.available() >= 4)
      {
        uint8_t x = Wire.read();
        uint8_t y = Wire.read();
        uint8_t r = Wire.read();
        bool color = Wire.read();

        glcdFillCircle(x, y, r, color);
      }
      break;
    }
  }
}

void setup()
{
  glcdInit();
  glcdClear();

  Wire.begin(GPU_ADDR);
  Wire.onReceive(receiveEvent);
}

void loop()
{
}