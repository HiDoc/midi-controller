#include "multiplexer.h"

void setupMultiplexer() {
    pinMode(S0, OUTPUT);
    pinMode(S1, OUTPUT);
    pinMode(S2, OUTPUT);
    pinMode(S3, OUTPUT);
    pinMode(SIG, INPUT);
}

int readMultiplexerChannel(int channel) {
    // Set the control pins
    digitalWrite(S0, bitRead(channel, 0));
    digitalWrite(S1, bitRead(channel, 1));
    digitalWrite(S2, bitRead(channel, 2));
    digitalWrite(S3, bitRead(channel, 3));
    delay(1); // Allow settling time

    // Read the value from the selected channel
    return analogRead(SIG);
}
