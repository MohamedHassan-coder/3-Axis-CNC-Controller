#include "Screen.h"
#include "Button.h"
#include "Encoder.h"
#include "SD_CARD.h"


//Pins
int const __ok = 5;
int const __back = 2;
int const __buzzer = 6;
bool __ok_status = LOW;
bool __back_status = LOW;
int encoder1 = 3;

Screen new_s;
Push_Button ok_btn (__ok, __buzzer);
Push_Button back_btn (__back, __buzzer);
Encoder encoder;

int choice;
int currentMenu = 0; //0-> home screen 1->main menu 2->jog men 3->config1menu 4->featuresmenu
int currentSubMenu = 0;

void setup(void) {
  new_s.x = 10.02;
  new_s.y = 23.12;
  new_s.z = 7.19;
  new_s.sdCard_status = false;
  new_s.spindle_status = true;
  Serial.begin(9600);

  attachInterrupt(digitalPinToInterrupt(encoder1 ), currentselect, HIGH);
  attachInterrupt(digitalPinToInterrupt(__back), back , FALLING );

}

void loop(void) {
  new_s.homePage();
  nav();
  while (currentMenu == 1) {
    new_s.mainMenu();
    new_s.setSelection(choice);
    if (!ok_btn.get_current_status()) {
      switch (choice) {
        case 1:
          encoder.resetChoice();
          choice = 0;
          currentMenu = 2;
          while (currentMenu == 2) {
            new_s.jogMenu();
            new_s.setSelection(choice);
            if (!ok_btn.get_current_status()) {
              jogging_submenu_go();
              new_s.setSelection(choice);
            }
          }
          break;
        case 2:
          encoder.resetCounter();
          encoder.resetChoice();
          choice = 0;
          currentMenu = 3;
          while (currentMenu == 3) {
            new_s.mcConfig1();
            new_s.setSelection(choice);
            while (encoder.getCounter() > 6) {
              encoder.multiMenu(true);
              new_s.mcConfig2();
              new_s.setSelection(choice);
            }
          }
          encoder.multiMenu(false);
          break;
        case 3:
          encoder.resetCounter();
          encoder.resetChoice();
          choice = 0;
          currentMenu = 4;
          while (currentMenu == 4) {
            new_s.features();
            new_s.setSelection(choice);
          }
          break;
      }
    }
  }
}

void nav() {
  __ok_status = ok_btn.get_current_status();
  if (!__ok_status) {
    currentMenu++;
  }
}

void goBack() {
  switch (currentMenu) {
    case 1:
      new_s.homePage();
      currentMenu = 0;
      break;
    case 2:
      new_s.mainMenu();
      currentMenu = 1;
      break;
    case 3:
      new_s.mainMenu();
      currentMenu = 1;
      break;
    case 4:
      new_s.mainMenu();
      currentMenu = 1;
      break;
  }
  choice = 0;
  encoder.resetCounter();
}

void back() {
  __back_status = back_btn.get_current_status();
  if (!__back_status) {
    if (currentSubMenu ==  1 || currentSubMenu ==  2) {
      new_s.jogMenu();
      currentSubMenu = 0;
    } else {
      goBack();
    }
  }
}

void jogging_submenu_go() {
  switch (choice) {
    case 1:
      currentSubMenu = 1;
      while (currentSubMenu == 1) {
        new_s.moveAxis();
        //read data from axis bottons x,y,z
      }
      break;
    case 2:
      //send $H to grbl to begin homing process and set x ,y ,z = 0
      new_s.homePage();
      delay(5000);
      currentMenu = 0;
      break;
    case 3:
      currentSubMenu = 2;
      while (currentSubMenu == 2) {
        new_s.setOrigin();
        //read data from axis bottons x,y,z
        //wait for origin botton to confirm
      }
      break;
  }
}

void currentselect() {
  encoder.currentSelection();
  choice = encoder.getChoice();
}
