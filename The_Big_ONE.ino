#include "Screen.h"
#include "Button.h"


//Pins
int const __ok = 5;
int const __back = 2;
int const __buzzer = 6;
int const encoder1 = 3;
int const encoder2 = 4;
bool __ok_status = LOW;
bool __back_status = LOW;

Screen new_s;
Push_Button ok_btn (__ok, __buzzer);
Push_Button back_btn (__back, __buzzer);

int choice = 0;
int counter = 0;
int newState;
int LastState;
volatile int flag = 0;

int currentMenu = 0; //0-> home screen 1->main menu 2->jog men 3->config1menu 4->config2menu 5->featuresmenu

void currentSelection();

void setup(void) {
  new_s.x = 10.02;
  new_s.y = 23.12;
  new_s.z = 7.19;
  new_s.sdCard_status = false;
  new_s.spindle_status = true;
  Serial.begin(9600);
  pinMode (encoder1, INPUT);
  pinMode (encoder2, INPUT);
  attachInterrupt(digitalPinToInterrupt(encoder1 ), currentSelection, CHANGE);
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
          choice = 0;
          currentMenu = 2;
          while (currentMenu == 2) {
            new_s.jogMenu();
            new_s.setSelection(choice);
          }
          break;
        case 2:
          choice = 0;
          currentMenu = 3;
          while (currentMenu == 3) {
            new_s.mcConfig1();
            new_s.setSelection(choice);
          }
          break;

          //currentMenu = 2;
          //        case 2:
          //        case 3:
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
      new_s.jogMenu();
      currentMenu = 1;
      break;
  }
  choice = 0;
}

void back() {
  __back_status = back_btn.get_current_status();
  if (!__back_status) {
    goBack();
  }
}

void currentPosition() {
  newState = digitalRead(encoder1);
  if (newState != LastState) {
    if (digitalRead(encoder2) != newState) {
      counter ++;
    } else {
      counter --;
    }
  }
  LastState = newState;
}

void currentSelection() {
  currentPosition();
  int first = 2;
  int second = 4;
  int third = 6;
  if ( 0 <= counter && counter < first) {
    choice =  1;
  } else if (first < counter && counter < second) {
    choice =  2;
  }
  else if (second < counter && counter < third) {
    choice =  3;
  } else if (counter > 8) {
    choice =  1;
    counter = 1;
  }
  else if (counter < -3) {
    choice =  1;
    counter = 1;
  }
}
