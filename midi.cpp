#include "midi.h"

SoftwareSerial mySerial(127, 52);

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);
MIDI_CREATE_INSTANCE(SoftwareSerial, mySerial, MIDI1);

#define MIDI_BAUD 31250

void setupMidi() {
  Serial1.begin(MIDI_BAUD);
  mySerial.begin(MIDI_BAUD);
}

void sendMidiControlChange(int control, int value, int channel) {
  // Envoie un message Control Change
  MIDI1.sendControlChange(control, value, channel);
  MIDI.sendControlChange(control, value, channel);
  Serial.print("Control Change envoyé: ");
  Serial.print(control);
  Serial.print(" Valeur: ");
  Serial.print(value);
  Serial.print(" Canal: ");
  Serial.println(channel);
}

void sendMidiProgramChange(int program, int channel) {
  // Envoie un message Program Change
  MIDI1.sendProgramChange(program, channel);
  MIDI.sendProgramChange(program, channel);
  Serial.print("Program Change envoyé: ");
  Serial.print(program);
  Serial.print(" Canal: ");
  Serial.println(channel);
}

void loopMidi() {
  for (int program = 0; program < 128; program++) {
    sendMidiProgramChange(program, 1); // Envoyer Program Change sur le canal 1
    delay(1000); // Attendre 1 seconde entre chaque message pour observer le changement
  }
}