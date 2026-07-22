#include "ComposeGLCD.h"

#include <string.h>
#include "GPU12864.h"

constexpr uint8_t FONT_5X7_WIDTH =  5;
constexpr uint8_t FONT_8X8_WIDTH =  8;
constexpr uint8_t FONT_5X7_HEIGHT = 7;
constexpr uint8_t FONT_8X8_HEIGHT = 8;
constexpr uint8_t CHAR_SPACE =      1;
constexpr uint8_t BUTTON_MARGIN =   2;

const uint8_t warn_bitmap[] PROGMEM =
{
0x00, 0x00, 0x00, 0x80, 0x60, 0x18, 0x04, 0xF2, 0xF2, 0x04, 0x18, 0x60,
0x80, 0x00, 0x00, 0x00, 0x00, 0x30, 0x4E, 0x41, 0x40, 0x40, 0x40, 0x5B,
0x5B, 0x40, 0x40, 0x40, 0x41, 0x4E, 0x38, 0x00
}; // Size: 16x16

// Commands

void initScreen()
{
  gpuBegin();
  gpuClear();
  gpuUpdate();
}

void clearScreen()
{
  gpuClear();
  gpuUpdate();
}

void draw() { gpuUpdate(); }


// System

void uiRaiseError(const char* err1, const char* err2, const char* err3 = "")
{
  gpuClear();

  gpuDrawBitmap(3, 3, warn_bitmap, 16, 16);
  gpuDrawText(3, 20, "ComposeGLCD Error!", FONT_5X7, 1);
  gpuDrawText(3, 30, err1, FONT_5X7, 1);
  gpuDrawText(3, 38, err2, FONT_5X7, 1);
  gpuDrawText(3, 46, err3, FONT_5X7, 1);

  gpuUpdate();

  while (true) {}
}

uint8_t centerX(uint8_t objectWidth)
{
  return (SCREEN_WIDTH - objectWidth) / 2;
}

uint8_t centerY(uint8_t objectHeight)
{
  return (SCREEN_HEIGHT - objectHeight) / 2;
}

uint8_t centerTextX(uint8_t len, bool font8x8 = false)
{
  if (len == 0) return SCREEN_WIDTH / 2;

  uint8_t width = 0;

  if (!font8x8)
  {
    width = FONT_5X7_WIDTH * len + CHAR_SPACE * (len - 1);
  }
  else
  {
    width = FONT_8X8_WIDTH * len + CHAR_SPACE * (len - 1);
  }

  return (SCREEN_WIDTH - width) / 2;
}

// UI Elements

void uiTitle(uint8_t y, const char* text)
{
  char buffer[50];

  uint8_t len = strlen(text);

  if (FONT_8X8_WIDTH * len + CHAR_SPACE * (len - 1) > SCREEN_WIDTH)
  {
    sprintf(buffer, "String Length: %d", len);
    uiRaiseError("Title length out", "of screen range.", buffer);
    return;
  }

  gpuDrawText(centerTextX(strlen(text), true), y, text, FONT_8X8, 1);
}

void uiLabel(uint8_t x, uint8_t y, const char* text, bool color = true)
{
  gpuDrawText(x, y, text, FONT_5X7, color);
}

void uiDialogBox(uint8_t x, uint8_t y, uint8_t w, uint8_t h)
{
  char buffer[50];

  if (x + w > SCREEN_WIDTH || y + h > SCREEN_HEIGHT)
  {
    sprintf(buffer, "'%dx%d'", w, h);
    uiRaiseError("DialogBox size:", buffer, "out of scope.");
    return;
  }

  gpuFillRect(x + 3, y + 3, w, h, 1); // Shadow
  
  gpuDrawRect(x, y, w, h);
  gpuFillRect(x + 1, y + 1, w - 2, h - 2, 0);
}

void uiButton(uint8_t x, uint8_t y, uint8_t w, uint8_t h, const char* text, bool active = false)
{
  char buffer[50];

  uint8_t stringLen = strlen(text);
  uint8_t realStrLen = 0;
  if (stringLen > 0)
  {
    realStrLen = FONT_5X7_WIDTH * stringLen + CHAR_SPACE * (stringLen - 1);
  }

  uint8_t textX = x + ((w - realStrLen) / 2);
  uint8_t textY = y + (h - FONT_5X7_HEIGHT) / 2;

  if (w - 2 < realStrLen + BUTTON_MARGIN * 2 || h - 2 < FONT_5X7_HEIGHT + BUTTON_MARGIN * 2)
  {
    sprintf(buffer, "Button size '%dx%d'", w, h);
    uiRaiseError(buffer, "out of scope.");
    return;
  }

  gpuDrawRect(x, y, w, h);
  gpuFillRect(x + 1, y + 1, w - 2, h - 2, active);

  gpuDrawText(textX, textY, text, FONT_5X7, !active);
}

void uiProgressBar(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t perc)
{
  if (perc > 100)
  {
    perc = 100;
  }

  uint8_t innerWidth = w - 4;
  uint8_t filledWidth = (innerWidth * perc) / 100;

  gpuDrawRect(x, y, w, h);

  if (filledWidth > 0)
  {
    gpuFillRect(x + 2, y + 2, filledWidth, h - 4, 1);
  }
}

void uiMenu(const char* items[], uint8_t itemCount, uint8_t selectedIndex)
{
  gpuClear();

  const uint8_t visibleItems = 6;
  uint8_t startIndex = 0;

  if (itemCount > visibleItems && selectedIndex >= 2)
  {
    startIndex = selectedIndex - 1;

    if (startIndex > itemCount - visibleItems)
    {
      startIndex = itemCount - visibleItems;
    }
  }

  for (uint8_t i = 0; i < visibleItems; i++)
  {
    uint8_t itemIndex = startIndex + i;

    if (itemIndex >= itemCount)
    {
      break;
    }

    if (itemIndex == selectedIndex)
    {
      gpuFillRect(0, 2 + i * 10, SCREEN_WIDTH, 10, 1);
      gpuDrawText(3, 3 + i * 10, items[itemIndex], FONT_5X7, 0);
    }
    else
    {
      gpuFillRect(0, 2 + i * 10, SCREEN_WIDTH, 10, 0);
      gpuDrawText(3, 3 + i * 10, items[itemIndex], FONT_5X7, 1);
    }
  }
}