#include "keypad.h"

char keys[KEYPAD_ROWS][KEYPAD_COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins[KEYPAD_ROWS] = {ROW_PIN_1, ROW_PIN_2, ROW_PIN_3, ROW_PIN_4}; // Connect to the row pins (R0-R3) of the keypad
byte colPins[KEYPAD_COLS] = {COL_PIN_1, COL_PIN_2, COL_PIN_3}; // Connect to the column pins (C0-C2) of the keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, KEYPAD_ROWS, KEYPAD_COLS);

String inputString = ""; // String to hold the user input
bool readingEnabled = false; // Flag to control reading state

String handleKeypadInput() {
  if (!readingEnabled) return "";

  char key = keypad.getKey(); // Read the key pressed

  if (key) { // Check if a key is actually pressed
    if (key >= '0' && key <= '9') { // If the key is a digit
      inputString += key; // Append the digit to the input string
    } else if (key == '*') { // If the key is '*', validate the input
      if (inputString.length() > 0) {
        String validatedInput = inputString;
        inputString = ""; // Clear the input string after processing
        return validatedInput;
      }
    } else if (key == '#') { // If the key is '#', cancel the input
      inputString = ""; // Clear the input string
    }
  }
  return "";
}

void startReadingKeypad() {
  readingEnabled = true;
  inputString = ""; // Clear the input string
}

void stopReadingKeypad() {
  readingEnabled = false;
  inputString = ""; // Clear the input string
}
