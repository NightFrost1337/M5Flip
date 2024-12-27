#include "M5StickCPlus2.h"

String menuOptions[] = {"Home", "Config", "Info"};
int currSelection = 0;
int totalOptions = sizeof(menuOptions) / sizeof(menuOptions[0]);

void setup() {
  M5.begin();
  M5.Lcd.setRotation(1);
  M5.Lcd.fillScreen(TFT_BLACK);

  displayMenu();
}

void loop() {
  M5.update();

  if (M5.BtnA.wasPressed()) {
    currSelection = (currSelection - 1 + totalOptions) % totalOptions;
    displayMenu();
  }

  if (M5.BtnB.wasPressed()) {
    currSelection = (currSelection + 1) % totalOptions;
    displayMenu();
  }
}

void displayMenu() {
  M5.Lcd.fillScreen(TFT_BLACK);

  for (int i = 0; i < totalOptions; i++) {
    int boxX = 20;
    int boxY = 20 + i * 40;
    int boxWidth = 200;
    int boxHeight = 30;

    if (i == currSelection) {
      M5.Lcd.fillRect(boxX, boxY, boxWidth, boxHeight, TFT_WHITE); 
      M5.Lcd.drawRect(boxX, boxY, boxWidth, boxHeight, TFT_WHITE); 
      M5.Lcd.setTextColor(TFT_BLACK);
    } else {
      M5.Lcd.drawRect(boxX, boxY, boxWidth, boxHeight, TFT_ORANGE); 
      M5.Lcd.setTextColor(TFT_WHITE);
    }

    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(boxX + 10, boxY + 5);
    M5.Lcd.print(menuOptions[i]);
  }
}