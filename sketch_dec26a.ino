#include "M5StickCPlus2.h"

#define MENU_SIZE 3

const char* menuItems[MENU_SIZE] = {"Option 1", "Option 2", "Option 3"};
int currSelection = 0;

void setup() {
  M5.begin();
  M5.Lcd.setRotation(1);  
  M5.Lcd.clear();
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(2);
}

void loop() {
  M5.update();

  if (M5.BtnA.wasPressed()) {
    selectOption();
  }
  if (M5.BtnB.wasPressed()) {
    scrollDown();
  }

  displayMenu();
  delay(100);
}

void displayMenu() {
  M5.Lcd.clear();
  M5.Lcd.setCursor(10, 10);
  M5.Lcd.setTextSize(3);
  M5.Lcd.print("Menu");
  
  for (int i = 0; i < MENU_SIZE; i++) {
    if (i == currSelection) {
      M5.Lcd.setTextColor(YELLOW);
      M5.Lcd.setTextSize(3);
    } else {
      M5.Lcd.setTextColor(WHITE);
      M5.Lcd.setTextSize(2);
    }

    M5.Lcd.setCursor(10, 40 + i * 30);
    M5.Lcd.print(menuItems[i]);
  }
}

void scrollDown() {
  currSelection++;
  if (currSelection >= MENU_SIZE) {
    currSelection = 0;
  }
}

void selectOption() {
  M5.Lcd.clear();
  M5.Lcd.setCursor(10, 10);
  M5.Lcd.setTextSize(3);
  
  if (currSelection == 0) {
    M5.Lcd.print("Option 1 selected");
  } else if (currSelection == 1) {
    M5.Lcd.print("Option 2 selected");
  } else if (currSelection == 2) {
    M5.Lcd.print("Option 3 selected");
  }
  
  delay(1000);
}