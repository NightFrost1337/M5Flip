#include "M5StickCPlus2.h"

String menuOptions[] = {"Home", "Config", "Info"};
int currSelection = 0;
int totalOptions = sizeof(menuOptions) / sizeof(menuOptions[0]);
bool onMenu = true;

void setup() {
  M5.begin();
  M5.Lcd.setRotation(1);
  M5.Lcd.fillScreen(TFT_BLACK);
  displayMenu();
}

void loop() {
  M5.update();

  if (onMenu) {
    if (M5.BtnB.wasPressed()) {
      currSelection = (currSelection + 1) % totalOptions;
      displayMenu();
    }

    if (M5.BtnA.wasPressed()) {
      displayPage(menuOptions[currSelection]);
    }
  } else {
    if (M5.BtnA.wasPressed()) {
      onMenu = true;
      displayMenu();
    }
  }
}

void displayMenu() {
  M5.Lcd.fillScreen(TFT_BLACK);
  onMenu = true;

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

void displayPage(String pageName) {
  M5.Lcd.fillScreen(TFT_BLACK);
  onMenu = false;

  M5.Lcd.setTextSize(3);
  M5.Lcd.setTextColor(TFT_WHITE);
  M5.Lcd.setCursor(40, 50);
  M5.Lcd.print("Page: ");
  M5.Lcd.print(pageName);

  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(20, 120);
  M5.Lcd.setTextColor(TFT_ORANGE);
  M5.Lcd.print("Press BtnA to go back");
}
