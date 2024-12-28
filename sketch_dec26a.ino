#include <Preferences.h>
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

Preferences preferences;

int xp = 0;
int level = 1;
int xpNextLevel = 100;
unsigned long lastActivityTime = 0;
unsigned long lastXPTime = 0;       
const unsigned long afkTimeout = 120000; 

void setup() {
  auto cfg = M5.config();
  StickCP2.begin(cfg);
  StickCP2.Display.setRotation(1);
  StickCP2.Display.fillScreen(backgroundColor);

  preferences.begin("user_data", true);
  xp = preferences.getInt("xp", 0);
  level = preferences.getInt("level", 1);
  preferences.end();

  displayMenu();
  lastActivityTime = millis(); 
}

void loop() {
  M5.update();

  if (isAFK()) {
    displayAFKMessage();
    return;
  }

  if (millis() - lastXPTime > 1000) {
    gainXP(1);
    lastXPTime = millis();
  }

  if (onMenu) {
    if (M5.BtnB.wasPressed()) {
      currSelection = (currSelection + 1) % totalOptions;
      displayMenu();
      lastActivityTime = millis(); 
    }

    if (M5.BtnA.wasPressed()) {
      if (menuOptions[currSelection] == "Config") {
        inConfigMenu = true;
        onMenu = false;
        displayConfigMenu();
      } else if (menuOptions[currSelection] == "Info") {
        displayInfo();
      } else {
        displayPage(menuOptions[currSelection]);
      }
      lastActivityTime = millis(); 
    }
  } else if (inConfigMenu) {
    if (M5.BtnB.wasPressed()) {
      configSelection = (configSelection + 1) % totalConfigOptions;
      displayConfigMenu();
      lastActivityTime = millis(); 
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
        StickCP2.Display.fillScreen(backgroundColor);
        displayConfigMenu();
      }
      lastActivityTime = millis(); 
    }
  } else {
    if (M5.BtnA.wasPressed()) {
      onMenu = true;
      displayMenu();
      lastActivityTime = millis(); 
    }
  }
}

void displayHeader() {
  StickCP2.Display.fillRect(0, 0, 240, 20, TFT_DARKGREY);
  StickCP2.Display.drawRect(0, 0, 240, 20, TFT_ORANGE);

  StickCP2.Display.setTextSize(1);
  StickCP2.Display.setTextColor(TFT_WHITE, TFT_DARKGREY);
  StickCP2.Display.setCursor(5, 5);
  StickCP2.Display.print("M5Flip");

  int batteryVoltage = StickCP2.Power.getBatteryVoltage();
  StickCP2.Display.setCursor(200, 5);
  StickCP2.Display.printf("%dmV", batteryVoltage);
}

void displayMenu() {
  StickCP2.Display.fillScreen(backgroundColor);
  displayHeader();
  onMenu = true;

  for (int i = 0; i < totalOptions; i++) {
    int boxX = 20;
    int boxY = 30 + i * 40;
    int boxWidth = 200;
    int boxHeight = 30;

    if (i == currSelection) {
      StickCP2.Display.fillRect(boxX, boxY, boxWidth, boxHeight, TFT_WHITE);
      StickCP2.Display.drawRect(boxX, boxY, boxWidth, boxHeight, TFT_WHITE);
      StickCP2.Display.setTextColor(TFT_BLACK);
    } else {
      StickCP2.Display.drawRect(boxX, boxY, boxWidth, boxHeight, borderColor);
      StickCP2.Display.setTextColor(TFT_WHITE);
    }

    StickCP2.Display.setTextSize(2);
    StickCP2.Display.setCursor(boxX + 10, boxY + 5);
    StickCP2.Display.print(menuOptions[i]);
  }
}

void displayConfigMenu() {
  StickCP2.Display.fillScreen(backgroundColor);
  displayHeader();
  inConfigMenu = true;

  for (int i = 0; i < totalConfigOptions; i++) {
    int boxX = 20;
    int boxY = 30 + i * 40;
    int boxWidth = 200;
    int boxHeight = 30;

    if (i == configSelection) {
      StickCP2.Display.fillRect(boxX, boxY, boxWidth, boxHeight, TFT_WHITE);
      StickCP2.Display.drawRect(boxX, boxY, boxWidth, boxHeight, TFT_WHITE);
      StickCP2.Display.setTextColor(TFT_BLACK);
    } else {
      StickCP2.Display.drawRect(boxX, boxY, boxWidth, boxHeight, borderColor);
      StickCP2.Display.setTextColor(TFT_WHITE);
    }

    StickCP2.Display.setTextSize(2);
    StickCP2.Display.setCursor(boxX + 10, boxY + 5);
    StickCP2.Display.print(configOptions[i]);
  }
}

void displayInfo() {
  StickCP2.Display.fillScreen(backgroundColor);
  displayHeader();

  StickCP2.Display.setTextSize(2);
  StickCP2.Display.setTextColor(TFT_WHITE);
  StickCP2.Display.setCursor(10, 40);
  StickCP2.Display.printf("Level: %d", level);

  StickCP2.Display.setCursor(10, 70);
  StickCP2.Display.printf("XP: %d/%d", xp, xpNextLevel);

  int progressBarWidth = 200;
  int filledWidth = (xp * progressBarWidth) / xpNextLevel;
  StickCP2.Display.fillRect(20, 100, filledWidth, 20, TFT_GREEN);
  StickCP2.Display.drawRect(20, 100, progressBarWidth, 20, TFT_WHITE);

  StickCP2.Display.setTextSize(1);
  StickCP2.Display.setCursor(10, 140);
  StickCP2.Display.print("Press BtnA to return");
}

void displayPage(String pageName) {
  StickCP2.Display.fillScreen(backgroundColor);
  displayHeader();
  onMenu = false;

  StickCP2.Display.setTextSize(3);
  StickCP2.Display.setTextColor(TFT_WHITE);
  StickCP2.Display.setCursor(40, 50);
  StickCP2.Display.print("Page: ");
  StickCP2.Display.print(pageName);

  StickCP2.Display.setTextSize(2);
  StickCP2.Display.setCursor(20, 120);
  StickCP2.Display.setTextColor(borderColor);
  StickCP2.Display.print("Press BtnA to go back");
}

void gainXP(int amount) {
  xp += amount;

  if (xp >= xpNextLevel) {
    xp -= xpNextLevel;
    level++;
    xpNextLevel += 50;

    preferences.begin("user_data", false);
    preferences.putInt("xp", xp);
    preferences.putInt("level", level);
    preferences.end();
  }
}

bool isAFK() {
  return millis() - lastActivityTime > afkTimeout;
}

void displayAFKMessage() {
  StickCP2.Display.fillScreen(backgroundColor);
  displayHeader();
  StickCP2.Display.setTextSize(2);
  StickCP2.Display.setTextColor(TFT_RED);
  StickCP2.Display.setCursor(30, 60);
  StickCP2.Display.print("AFK Mode");
  StickCP2.Display.setTextSize(1);
  StickCP2.Display.setCursor(10, 120);
  StickCP2.Display.print("Press any button to resume.");
  if (M5.BtnA.wasPressed() || M5.BtnB.wasPressed()) {
    lastActivityTime = millis();
  }
}
