#ifndef COMPOSEGLCD_H
#define COMPOSEGLCD_H

#include <Arduino.h>

#define SCREEN_WIDTH   128
#define SCREEN_HEIGHT  64


void initScreen();
void clearScreen();
void draw();

void uiRaiseError(const char* err1, const char* err2, const char* err3 = "");
uint8_t centerX(uint8_t objectWidth);
uint8_t centerY(uint8_t objectHeight);
uint8_t centerTextX(uint8_t len, bool font8x8 = false);

void uiTitle(uint8_t y, const char* text);
void uiLabel(uint8_t x, uint8_t y, const char* text, bool color = true);
void uiDialogBox(uint8_t x, uint8_t y, uint8_t w, uint8_t h);
void uiButton(uint8_t x, uint8_t y, uint8_t w, uint8_t h, const char* text, bool active = false);
void uiProgressBar(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t perc);
void uiMenu(const char* items[], uint8_t itemCount, uint8_t selectedIndex);

#endif