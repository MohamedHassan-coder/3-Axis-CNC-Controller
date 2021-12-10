#include "Screen.h"
#include "Button.h"
//#include "Encoder.h"

Screen new_s;


//Pins
int const __ok = 2;
int const __back = 5;
int const __buzzer = 6;
int const encoder1 = 3;
int const encoder2 = 4;
bool __ok_status = LOW;
bool __back_status = LOW;

Push_Button ok_btn (__ok, __buzzer);
Push_Button back_btn (__back, __buzzer);
//Encoder encoder;


int choice;

int counter = 0;
int newState;
int LastState;
void currentPosition();

void setup(void) {
  new_s.x = 10.02;
  new_s.y = 23.12;
  new_s.z = 7.19;
  new_s.sdCard_status = false;
  new_s.spindle_status = true;
  Serial.begin(9600);
  pinMode (encoder1, INPUT);
  pinMode (encoder2, INPUT);
  attachInterrupt(digitalPinToInterrupt(encoder1), currentSelection, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoder2), currentSelection, CHANGE);
}

void loop(void) {
  new_s.homePage();
  __ok_status = ok_btn.get_current_status();
  Serial.println(__ok_status);
  while ( !__ok_status) {
    new_s.mainMenu();
    new_s.setSelection(choice);
  }
  currentSelection();
  //  new_s.go();
  //  new_s.setSelection(choice);
}


void currentPosition() {

}

void currentSelection() {

  newState = digitalRead(encoder1);
  if (newState != LastState) {
    if (digitalRead(encoder2) != newState) {
      counter ++;
    } else {
      counter --;
    }
  }
  LastState = newState;


  int first = 3;
  int second = 5;
  int third = 7;
  if ( 0 <= counter && counter < first) {
    choice =  1;
  } else if (first < counter && counter < second) {
    choice =  2;
  }
  else if (second < counter && counter < third) {
    choice =  3;
  } else if (counter > 10) {
    choice =  1;
    counter = 1;
  }
  else if (counter < -3) {
    choice =  1;
    counter = 1;
  }
}
