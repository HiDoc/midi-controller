#include "system.h"

uint8_t modeSelected = 0;
uint8_t channelSelected = 0;

uint8_t programsSelected[8] = {-1,-1,-1,-1,-1,-1,-1,-1};
bool waitingForKeypadValue = false;
String keypadValue = "";

// Function to set the color for channel mode
void selectChannelColor() {
  colorSpecificOption(BUTTON_CHANNEL);
  colorLedsRange(8, 19, COLOR_BLACK);
  colorLed(BUTTON_CHANNEL, COLOR_CHANNEL);
}

// Function to set the color for program mode
void selectProgramColor() {
  colorSpecificOption(BUTTON_PROGRAM);
  colorLedsRange(0, 15, COLOR_COMMON);
  colorLed(channelSelected, COLOR_CHANNEL);
  if (programsSelected[channelSelected] != -1) {
    colorLed(programsSelected[channelSelected], COLOR_PROGRAM);
  }
}

// Function to set the color for control mode
void selectControlColor() {
  colorLedsRange(0, 15, COLOR_COMMON);
}

// Function to set the color for clock mode
void selectClock() {
  colorLedsRange(0, 15, COLOR_COMMON);
}

// Function to handle mode selection
void selectMode(uint8_t index) {
  Serial.print("Mode selected : ");
  switch (index) {
    case BUTTON_CHANNEL:
      selectChannelColor();
      highlightLabel(0);
      Serial.println("Channel");
      modeSelected = BUTTON_CHANNEL;
      break;
    case BUTTON_PROGRAM:
      selectProgramColor();
      highlightLabel(1);
      Serial.println("Program");
      modeSelected = BUTTON_PROGRAM;
      break;
    case BUTTON_CONTROL:
      selectControlColor();
      highlightLabel(2);
      Serial.println("Control");
      modeSelected = BUTTON_CONTROL;
      break;
    case BUTTON_CLOCK:
      selectClock();
      highlightLabel(3);
      Serial.println("Clock");
      modeSelected = BUTTON_CLOCK;
      break;
  }
  colorSpecificOption(index);
}


// Function to handle channel selection
void handleChannelSelection(uint8_t index) {
  if (index < 8) {
    channelSelected = index;
    drawChannels(index);
    colorLedsRange(0, 7, COLOR_COMMON);
    colorLed(index, COLOR_CHANNEL);
    Serial.print("Channel selected: ");
    Serial.println(channelSelected);
  }
}

// Function to handle program selection
void handleProgramSelection(uint8_t index) {
  Serial.print("Channel selected: ");
  Serial.println(channelSelected);
  sendMidiProgramChange(index, channelSelected + 1);
  if (programsSelected[channelSelected] != -1) {
    colorLed(programsSelected[channelSelected], COLOR_COMMON);
  }
  blinkColor(index, index == channelSelected ? COLOR_CHANNEL : COLOR_COMMON, COLOR_PROGRAM, 3, 200);
  programsSelected[channelSelected] = index;
}

// Function to handle control selection
void handleControlSelection(uint8_t index) {
  startReadingKeypad();
  sendMidiControlChange(index + 1, 127, channelSelected + 1);
  blinkColor(index, index == channelSelected ? COLOR_CHANNEL : COLOR_COMMON, COLOR_CONTROL, 3, 200);
}

// Function to perform actions based on the selected mode
void doAction(uint8_t index) {
  switch (modeSelected) {
    case BUTTON_CHANNEL:
      handleChannelSelection(index);
      break;
    case BUTTON_PROGRAM:
      handleProgramSelection(index);
      break;
    case BUTTON_CONTROL:
      handleControlSelection(index);
      break;
    case BUTTON_CLOCK:
      // Handle clock-related actions here if any
      break;
  }
  FastLED.show();
}

void systemLoop() {
  unsigned long currentMillis = millis();
  for (uint8_t i = 0; i < BUTTON_COUNT; i++) {
    if (checkButtonPress(i, currentMillis)) {
      Serial.print("Button pressed :");
      Serial.println(i);
      if (i == BUTTON_CHANNEL || i == BUTTON_PROGRAM || i == BUTTON_CONTROL || i == BUTTON_CLOCK) {
        if (waitingForKeypadValue) {
          stopReadingKeypad();
          waitingForKeypadValue = false;
        }
        selectMode(i);
      } else if (!waitingForKeypadValue) {
        doAction(i);
      }
      delay(BUTTON_DELAY);
      resetButtonState(i);
    }
    if (waitingForKeypadValue) {
      String value = handleKeypadInput();
      if (value.length() > 0) {
        // Handle the validated keypad value here
        Serial.print("Keypad value: ");
        Serial.println(value);
        waitingForKeypadValue = false;
        stopReadingKeypad();
      }
    }
  }
}

