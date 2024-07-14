#include "leds.h"

// Define the array of leds
CRGB leds[NUM_LEDS];

// Define the palette and blending mode
CRGBPalette16 currentPalette;
TBlendType currentBlending = LINEARBLEND;

const int ledsToButton[20] = { 3, 2, 1, 0, 7, 6, 5, 4, 11, 10, 9, 8, 15, 14, 13, 12, 19, 18, 17, 16 }; 

// Define the color options
ColorOption colorOptions[] = {
  { BUTTON_CHANNEL, COLOR_CHANNEL},
  { BUTTON_PROGRAM, COLOR_PROGRAM},
  { BUTTON_CONTROL, COLOR_CONTROL},
  { BUTTON_CLOCK, COLOR_CLOCK}
};

void fillLEDsFromPaletteColors(uint8_t colorIndex) {
  uint8_t brightness = 255;
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette(currentPalette, colorIndex, brightness, currentBlending);
    colorIndex += 3;
  }
}

void colorLedsRange(int start, int end, CRGB color) {
  start = constrain(start, 0, NUM_LEDS - 1);
  end = constrain(end, 0, NUM_LEDS - 1);
  for (int i = start; i <= end; i++) {
    leds[ledsToButton[i]] = color;
  }
}

void colorLed(int index, CRGB color) {
  leds[ledsToButton[index]] = color;
}

void blinkColor(int index, CRGB startColor, CRGB endColor, int times, int delay) {
  for (int i = 0; i < times; i++) {
    colorLed(index, (i % 2 == 0) ? startColor : endColor);
    FastLED.show();
    FastLED.delay(delay);
  }
  colorLed(index, endColor);
  FastLED.show();
}

void colorSpecificOption(int option) {
  for (const auto& colorOption : colorOptions) {
    if (option == colorOption.option) {
      colorLed(colorOption.option, colorOption.color);
    } else {
      colorLed(colorOption.option, blend(colorOption.color, CRGB::Black, 220));
    }
  }
  FastLED.show();
}

void colorOptionSelection() {
  for (const auto& colorOption : colorOptions) {
    colorLed(colorOption.option, colorOption.color);
  }
  FastLED.show();
}

void colorDefault() {
  fill_solid(leds, NUM_LEDS, CRGB::Wheat);
  colorOptionSelection();
  FastLED.show();
}

void setupLeds() {
  Serial.println("Starting leds configuration");
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);

  currentPalette = RainbowColors_p;

  for (uint8_t startIndex = 0; startIndex < 255; startIndex++) {
    fillLEDsFromPaletteColors(startIndex);
    FastLED.show();
    FastLED.delay(10);
  }

  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
  FastLED.delay(100);
  fill_solid(leds, NUM_LEDS, CRGB::Wheat);
  FastLED.show();
  FastLED.delay(100);
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
  FastLED.delay(100);
  colorDefault();
  Serial.println("Leds configuration done...");
}

void loopLeds() {
  // Placeholder for future LED handling in the loop
}
