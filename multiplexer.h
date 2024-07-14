#pragma once

#include <Arduino.h>

// Define the control pins for the multiplexer
#define S0 8
#define S1 9
#define S2 10
#define S3 11
#define SIG A0

void setupMultiplexer();
int readMultiplexerChannel(int channel);
