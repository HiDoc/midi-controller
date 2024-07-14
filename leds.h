#pragma once

#include <FastLED.h>
#include <Arduino.h>
#include "colors.h"
#include "buttons.h"

// Data pin for leds
#define LED_PIN    29

// Global values for leds
#define BRIGHTNESS  96
#define NUM_LEDS    20

#define LED_TYPE    PL9823
#define COLOR_ORDER RGB

// Array of leds
extern CRGB leds[NUM_LEDS];

extern CRGBPalette16 currentPalette;
extern TBlendType currentBlending;

struct ColorOption {
  int option;
  CRGB color;
};

extern ColorOption colorOptions[];

void fillLEDsFromPaletteColors(uint8_t colorIndex);
void colorLedsRange(int start, int end, CRGB color);
void colorLed(int index, CRGB color);
void blinkColor(int index, CRGB startColor, CRGB endColor, int times, int delay);
void colorSpecificOption(int option);
void colorOptionSelection();
void colorDefault();
void setupLeds();
void loopLeds();