#include "Screen.h"
#include "Button.h"
#include "Encoder.h"
#include "SD_CARD.h"

//Pins
#define __ok 5
#define __back  2
#define __buzzer  7

#define Xp 22
#define Xn 23
#define Yp 24
#define Yn 25
#define Zp 26
#define Zn 27

Screen new_s;
Encoder encoder;
SD_CARD sd;
Push_Button ok_btn (__ok, __buzzer);
Push_Button back_btn (__back, __buzzer);
Push_Button zp_btn (Zp, __buzzer);
Push_Button zn_btn (Zn, __buzzer);
Push_Button xp_btn (Xp, __buzzer);
Push_Button xn_btn (Xn, __buzzer);
Push_Button yp_btn (Yp, __buzzer);
Push_Button yn_btn (Yn, __buzzer);

bool __ok_status = LOW;
bool __back_status = LOW;
bool __xp_status = LOW;
bool __xn_status = LOW;
bool __yp_status = LOW;
bool __yn_status = LOW;
bool __zp_status = LOW;
bool __zn_status = LOW;

int choice;
int currentMenu = 0; //0-> home screen 1->main menu 2->jog men 3->config1menu 4->featuresmenu
int currentSubMenu = 0;
float axis_Increment_value = 1;
float x = 0.00 , y = 0.00 , z = 0.00;

int menu_select = 0; //0-> normal select 1->multi menu select , 2->sd card-menu select
String files_names;
String files_sizes;
int files_num;
int column , row;

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
void setup(void) {
  Serial.begin(9600);
  new_s.spindle_status = true;
  new_s.setCoordniates(x , y , z);
  new_s.sdCard_status = sd.sdAvailable();
  new_s.homePage();
  sd.getFilesData();
  files_names = sd.files_names;
  files_sizes = sd.files_sizes;
  files_num = sd.getNumber();
  attachInterrupt(digitalPinToInterrupt(3), select , HIGH);
  attachInterrupt(digitalPinToInterrupt(__back), back , FALLING );
  Serial.println("Setup finished");
}

void loop() {
  new_s.homePage();
  nav();
  while (currentMenu == 1) {
    new_s.mainMenu();
    new_s.setSelection(choice);
    if (!ok_btn.get_current_status()) {
      mainMenuSelect();
    }
  }
}
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

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
    } if (currentSubMenu ==  3 || currentSubMenu ==  4) {
      new_s.features();
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
        getAxis();
      }
      break;
    case 2:
      Serial.println("$H");
      x = 0;
      y = 0;
      z = 0;
      new_s.setCoordniates(x , y , z);
      new_s.homePage();
      delay(5000);
      currentMenu = 0;
      break;
    case 3:
      currentSubMenu = 2;
      while (currentSubMenu == 2) {
        new_s.setOrigin();
        getAxis();
        __ok_status = ok_btn.get_current_status();
        if (!__ok_status) {
          //Send the new origin comand to grbl
          x = 0;
          y = 0;
          z = 0;
          new_s.setCoordniates(x , y , z);
          new_s.homePage();
          currentMenu = 0;
          break;
        }
      }
      break;
  }
}

void features_submenu() {
  switch (choice) {
    case 1:
      currentSubMenu = 3;
      while (currentSubMenu == 3) {
        sd_card_Menu();
        menu_select = 2;
      }
      menu_select = 0;
      break;
    case 2:
      //bluetooth
      break;
  }
}

void sd_card_Menu() {
  new_s.sdFiles(files_names, files_num);
  new_s.sd_setSelection(row , column);
  if (!ok_btn.get_current_status()) {
    int file_number = encoder.sd_choice;
    String file_name = sd.getFileName(file_number);
    Serial.println(file_number);
    Serial.println(file_name);
    sd.openFile(file_name);
    sd.loadCurrentFile();
    sd.closeFile();
  }
}

void currentselect() {
  encoder.currentSelection();
  choice = encoder.getChoice();
}

void mainMenuSelect() {
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
      currentMenu = 3;
      choice = 0;
      while (currentMenu == 3) {
        menu_select = 1;
        new_s.mcConfig1();
        new_s.setSelection(choice);
        while (encoder.getCounter() > 8) {
          new_s.mcConfig2();
          new_s.setSelection(choice);
        }
      }
      menu_select = 0;
      break;
    case 3:
      encoder.resetCounter();
      encoder.resetChoice();
      choice = 0;
      currentMenu = 4;
      while (currentMenu == 4) {
        new_s.features();
        new_s.setSelection(choice);
        if (!ok_btn.get_current_status()) {
          features_submenu();
          new_s.setSelection(choice);
        }
      }
      break;
  }
}

void select() {
  if (menu_select == 1) {
    encoder.multiSelection();
    choice = encoder.getChoice();
  } else if (menu_select == 0) {
    currentselect();
  } else if (menu_select == 2) {
    encoder.sd_select();
    row = encoder.sd_row;
    column = encoder.sd_column;
  }
}

void getAxis() {
  __xp_status = xp_btn.get_current_status();
  __xn_status = xn_btn.get_current_status();
  __yp_status = yp_btn.get_current_status();
  __yn_status = yn_btn.get_current_status();
  __zp_status = zp_btn.get_current_status();
  __zn_status = zn_btn.get_current_status();
  if (!__xp_status) {
    x += axis_Increment_value;
  } else if (!__xn_status) {
    x -= axis_Increment_value;
  }
  if (!__yp_status) {
    y += axis_Increment_value;
  } else if (!__yn_status) {
    y -= axis_Increment_value;
  }
  if (!__zp_status) {
    z += axis_Increment_value;
  } else if (!__zn_status) {
    z -= axis_Increment_value;
  }
  new_s.setCoordniates(x , y , z);
}
