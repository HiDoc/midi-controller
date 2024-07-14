#pragma once

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// Define LCD pins
#define LCD_BL    7 // Backlight control pin

#define LCD_CLK 8
#define LCD_DIN 9
#define LCD_DC  10
#define LCD_CE  11
#define LCD_RST 12

#define CIRCLE_RADIUS 5
#define CIRCLE_GAP    8 // Gap between circles
#define CIRCLE_Y      20 // Y position of the circles (centered vertically)

// Initialize the display
extern Adafruit_PCD8544 display;

// Function prototypes
void setupLCD();

void resetDisplay();
void addNewLine(const char* text);

void drawLabels();
void drawTitle(uint8_t index);
void drawChannels(uint8_t channelSelectedIndex);
void highlightLabel(uint8_t index);

void drawWaveEffect();
void showWelcomeMessage();
void displayText(const char* text, int x, int y, int textSize = 1);