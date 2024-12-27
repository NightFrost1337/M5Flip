#include "M5StickCPlus2.h"

String menuOptions[] = {"Home", "Config", "Info"};
String configOptions[] = {"Border Color", "Background Color", "Back"};
int currSelection = 0;
int totalOptions = sizeof(menuOptions) / sizeof(menuOptions[0]);
int configSelection = 0;
int totalConfigOptions = sizeof(configOptions) / sizeof(configOptions[0]);
bool onMenu = true;
bool inConfigMenu = false;

uint16_t borderColor = TFT_ORANGE;
uint16_t backgroundColor = TFT_BLACK;

void setup() {
  M5.begin();
  M5.Lcd.setRotation(1);
  M5.Lcd.fillScreen(backgroundColor);
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
      if (menuOptions[currSelection] == "Config") {
        inConfigMenu = true;
        onMenu = false;
        displayConfigMenu();
      } else {
        displayPage(menuOptions[currSelection]);
      }
    }
  } else if (inConfigMenu) {
    if (M5.BtnB.wasPressed()) {
      configSelection = (configSelection + 1) % totalConfigOptions;
      displayConfigMenu();
    }

    if (M5.BtnA.wasPressed()) {
      if (configOptions[configSelection] == "Back") {
        inConfigMenu = false;
        onMenu = true;
        displayMenu(); 
      } else if (configOptions[configSelection] == "Border Color") {
        borderColor = (borderColor == TFT_ORANGE) ? TFT_WHITE : TFT_ORANGE;
        displayConfigMenu();
      } else if (configOptions[configSelection] == "Background Color") {
        backgroundColor = (backgroundColor == TFT_BLACK) ? TFT_BLUE : TFT_BLACK;
        M5.Lcd.fillScreen(backgroundColor);
        displayConfigMenu();
      }
    }
  } else {
    if (M5.BtnA.wasPressed()) {
      onMenu = true;
      displayMenu();
    }
  }
}

void displayMenu() {
  M5.Lcd.fillScreen(backgroundColor);
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
      M5.Lcd.drawRect(boxX, boxY, boxWidth, boxHeight, borderColor);
      M5.Lcd.setTextColor(TFT_WHITE);
    }

    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(boxX + 10, boxY + 5);
    M5.Lcd.print(menuOptions[i]);
  }
}

void displayConfigMenu() {
  M5.Lcd.fillScreen(backgroundColor);
  inConfigMenu = true;

  for (int i = 0; i < totalConfigOptions; i++) {
    int boxX = 20;
    int boxY = 20 + i * 40;
    int boxWidth = 200;
    int boxHeight = 30;

    if (i == configSelection) {
      M5.Lcd.fillRect(boxX, boxY, boxWidth, boxHeight, TFT_WHITE);
      M5.Lcd.drawRect(boxX, boxY, boxWidth, boxHeight, TFT_WHITE);
      M5.Lcd.setTextColor(TFT_BLACK);
    } else {
      M5.Lcd.drawRect(boxX, boxY, boxWidth, boxHeight, borderColor);
      M5.Lcd.setTextColor(TFT_WHITE);
    }

    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(boxX + 10, boxY + 5);
    M5.Lcd.print(configOptions[i]);
  }
}

void displayPage(String pageName) {
  M5.Lcd.fillScreen(backgroundColor);
  onMenu = false;

  M5.Lcd.setTextSize(3);
  M5.Lcd.setTextColor(TFT_WHITE);
  M5.Lcd.setCursor(40, 50);
  M5.Lcd.print("Page: ");
  M5.Lcd.print(pageName);

  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(20, 120);
  M5.Lcd.setTextColor(borderColor);
  M5.Lcd.print("Press BtnA to go back");
}
