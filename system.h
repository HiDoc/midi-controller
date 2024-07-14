#pragma once

#include <Arduino.h>
#include "leds.h"
#include "midi.h"
#include "buttons.h"
#include "colors.h"
#include "buttons.h"
#include "keypad.h"
#include "lcd.h"

void selectChannel();
void selectProgram();
void selectControl();
void selectMidiClock();

void systemLoop();