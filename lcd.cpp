#include "lcd.h" // Include your library header file here

Adafruit_PCD8544 display(LCD_CLK, LCD_DIN, LCD_DC, LCD_CE, LCD_RST);

const char* labels[4] = { "CH", "PC", "CC", "CLK" };
uint8_t BL_VALUE = HIGH;

void switchBacklight() {
  BL_VALUE = BL_VALUE == HIGH ? LOW : HIGH;
  digitalWrite(LCD_BL, BL_VALUE);
}

void setupLCD() {
    Serial.println("Setting up LCD");
    pinMode(LCD_BL, OUTPUT);
    digitalWrite(LCD_BL, BL_VALUE);
    display.begin();
    display.setContrast(60);
    display.clearDisplay();
    drawLabels();
    drawChannels(0);
    Serial.println("Finishing setting up LCD...");
}

void displayText(const char* text, int x, int y, int textSize) {
    display.setTextSize(textSize);
    display.setCursor(x, y);
    display.print(text);
    display.display();
}

void resetDisplay() {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.display();
}

void addNewLine(const char* text) {
    int16_t x, y;
    uint16_t w, h;
    display.getTextBounds(text, 0, 0, &x, &y, &w, &h);
    int cursorY = display.getCursorY();
    display.setCursor(0, cursorY + h);
    display.print(text);
    display.display();
}

void drawLabels() {
    display.setTextSize(1);
    display.setTextColor(BLACK);
    display.setCursor(0, 1);
    display.print(labels[0]);
    display.setCursor(22, 1); // Adjust x position based on label length and spacing
    display.print(labels[1]);
    display.setCursor(44, 1); // Adjust x position based on label length and spacing
    display.print(labels[2]);
    display.setCursor(66, 1); // Adjust x position based on label length and spacing
    display.print(labels[3]);
    display.drawLine(0, 10, 84, 10, BLACK);
    display.display();
}

void drawChannels(uint8_t channelSelectedIndex) {
  
  // Calculate the starting X position for the circles
  int startX = (display.width() - (4 * (2 * CIRCLE_RADIUS + CIRCLE_GAP))) / 2;
  
  // Draw the circles
  for (int i = 0; i < 8; i++) {
    int row = i / 4;
    int col = i % 4;
    
    int x = 4 + startX + col * (2 * CIRCLE_RADIUS + CIRCLE_GAP);
    int y = CIRCLE_Y + row * (2 * CIRCLE_RADIUS + CIRCLE_GAP) - 4;
    
    if (channelSelectedIndex == i) {
      display.fillCircle(x + CIRCLE_RADIUS, y + CIRCLE_RADIUS, CIRCLE_RADIUS, BLACK);
    } else {
      display.drawCircle(x + CIRCLE_RADIUS, y + CIRCLE_RADIUS, CIRCLE_RADIUS, BLACK);
    }
  }
}

void highlightLabel(uint8_t labelIndex) {
    resetDisplay();
    drawLabels();

    int16_t x, y;
    uint16_t w, h;
    display.setTextSize(1);
    display.getTextBounds(labels[labelIndex], 0, 0, &x, &y, &w, &h);

    int labelX;
    switch (labelIndex) {
        case 0:
            labelX = 0;
            break;
        case 1:
            labelX = 21; // Adjust x position based on label length and spacing
            break;
        case 2:
            labelX = 42; // Adjust x position based on label length and spacing
            break;
        case 3:
            labelX = 63; // Adjust x position based on label length and spacing
            break;
        default:
            return; // Invalid label index
    }

    // Draw black rectangle and white text
    display.fillRect(labelX, 0, w + 2, h + 1, BLACK);
    display.setTextColor(WHITE, BLACK);
    display.setCursor(labelX + 1, 1);
    display.print(labels[labelIndex]);
    display.setTextColor(BLACK);
    display.display();
}

void showWelcomeMessage() {
    const char* welcomeText[] = {
        "Loading",
        "Loading.",
        "Loading..",
        "Loading...",
        "Almost there",
        "Welcome!",
        "Enjoy your session :)"
    };

    resetDisplay();
    display.setTextSize(1);

    for (int i = 0; i < 7; i++) {
        display.clearDisplay();
        display.setCursor(0, 0);
        display.print(welcomeText[i]);
        Serial.println(welcomeText[i]);
        display.display();
        delay(300); // Adjust delay for animation speed
    }

    delay(1000); // Hold final message for a moment
    resetDisplay();
}

void drawWaveEffect() {
    resetDisplay();
    display.setTextSize(1);
    display.setTextColor(BLACK);

    const int waveHeight = 6;
    const int waveLength = 12;
    const int waveSpeed = 100; // milliseconds

    for (int x = 0; x < display.width(); x++) {
        display.clearDisplay();
        for (int i = 0; i < display.width(); i++) {
            int y = waveHeight * sin((i + x) * 2 * PI / waveLength);
            display.drawPixel(i, display.height() / 2 + y, BLACK);
        }
        display.display();
        delay(waveSpeed);
    }

    // Hold the final wave for a moment
    delay(1000);
    resetDisplay();
}

