#pragma once

#include <Arduino.h>

#define BUTTON_CHANNEL  16
#define BUTTON_PROGRAM  17
#define BUTTON_CONTROL  18
#define BUTTON_CLOCK    19

#define BUTTON_COUNT    20
#define BUTTON_DELAY    200

void setupButtons();
void loopButtons();

bool checkButtonPress(int buttonIndex, unsigned long currentMillis);
void resetButtonState(int index);