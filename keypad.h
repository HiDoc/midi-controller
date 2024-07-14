#pragma once

#include <Keypad.h>

// KEYPAD SETUP
#define KEYPAD_ROWS 4 // Define the number of rows on the keypad
#define KEYPAD_COLS 3 // Define the number of columns on the keypad

// Define the pins for the rows and columns
#define ROW_PIN_1 23
#define ROW_PIN_2 24
#define ROW_PIN_3 25
#define ROW_PIN_4 26

#define COL_PIN_1 27
#define COL_PIN_2 28
#define COL_PIN_3 29

// Matrix defining character to return for each key
extern char keys[KEYPAD_ROWS][KEYPAD_COLS];

extern byte rowPins[KEYPAD_ROWS]; // Connect to the row pins (R0-R3) of the keypad
extern byte colPins[KEYPAD_COLS]; // Connect to the column pins (C0-C2) of the keypad
extern Keypad keypad;

extern String inputString; // String to hold the user input
extern bool readingEnabled; // Flag to control reading state

// Function prototypes
String handleKeypadInput();
void processInput(String input);
void startReadingKeypad();
void stopReadingKeypad();
