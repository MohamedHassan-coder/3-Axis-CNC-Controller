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

int currentMenu = 0; //0-> home screen 1->main menu 2->jog men 3->config1menu 4->featuresmenu
int currentSubMenu = 0;
bool multiMenu_Flag = false;
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
  attachInterrupt(digitalPinToInterrupt(encoder1 ), currentSelection, HIGH);
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
            Serial.println("Jog");
            if (!ok_btn.get_current_status()) {
              jogging_submenu_go();
              new_s.setSelection(choice);
            }
          }
          break;
        case 2:
          counter = 0;
          choice = 0;
          currentMenu = 3;
          while (currentMenu == 3) {
            new_s.mcConfig1();
            new_s.setSelection(choice);
            while (counter > 6) {
              multiMenu_Flag = true;
              new_s.mcConfig2();
              new_s.setSelection(choice);
            }

          }
          multiMenu_Flag = false;
          break;
        case 3:
          counter = 0;
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
  int forth = 8;
  if ( 0 <= counter && counter < first) {
    choice =  1;
  } else if (first < counter && counter < second) {
    choice =  2;
  }
  else if (second < counter && counter < third) {
    choice =  3;
  }
  if ((multiMenu_Flag && counter > third)) {
    int sixth = 11;
    int seventh = 13;
    if ( third < counter && counter < forth) {
      choice =  1;
    } else if (forth < counter && counter < sixth) {
      choice =  2;
    }
    else if (sixth < counter && counter < seventh) {
      choice =  3;
    } else if (counter > seventh ) {
      counter = 13;
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
