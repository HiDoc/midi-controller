#pragma once

#include "buttons.h"
#include "midi.h"

const int BUTTON_PINS[BUTTON_COUNT] = {30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49}; // Broches des boutons

bool buttonPressed[BUTTON_COUNT] = { false }; // Tableau pour stocker l'état de chaque bouton pressé
bool lastButtonStates[BUTTON_COUNT] = { HIGH }; // Tableau pour stocker l'état précédent de chaque bouton
unsigned long lastButtonPressTimes[BUTTON_COUNT] = {0}; // Tableau pour stocker le temps du dernier appui sur chaque bouton

void setupButtons() {
    // Set button pins as input with pull-up resistors and initialize LEDs to off
  for (int i = 0; i < BUTTON_COUNT; i++) {
    pinMode(BUTTON_PINS[i], INPUT_PULLUP);
  }
}

bool checkButtonPress(int buttonIndex, unsigned long currentMillis) {
  bool currentButtonState = digitalRead(BUTTON_PINS[buttonIndex]);

  // Logique de débouclage
  if (lastButtonStates[buttonIndex] != currentButtonState) {
    delay(30); // Délai de débouclage en millisecondes (à ajuster si nécessaire)
    currentButtonState = digitalRead(BUTTON_PINS[buttonIndex]);
  }

  lastButtonStates[buttonIndex] = currentButtonState;

  // Vérifier si le bouton est pressé
  if (!buttonPressed[buttonIndex] && currentButtonState == LOW) {
    // Vérifier si le délai minimum est écoulé depuis le dernier appui sur ce bouton
    if (currentMillis - lastButtonPressTimes[buttonIndex] >= BUTTON_DELAY) {
      buttonPressed[buttonIndex] = true;
      lastButtonPressTimes[buttonIndex] = currentMillis; // Mettre à jour le temps du dernier appui sur ce bouton

      // Faites quelque chose lorsque le bouton est pressé, par exemple :
      // digitalWrite(LED_PIN, HIGH); // Allumer une LED
    }
  } else if (buttonPressed[buttonIndex] && currentButtonState == HIGH) {
    buttonPressed[buttonIndex] = false;

    // Faites quelque chose lorsque le bouton est relâché, par exemple :
    // digitalWrite(LED_PIN, LOW); // Éteindre une LED
  }
  return buttonPressed[buttonIndex];
}

void resetButtonState(int index) {
  buttonPressed[index] = false;
}
