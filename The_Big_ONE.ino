#include "Screen.h"
#include "Button.h"

Screen new_s;
//Controller new_c;


//Pins
int const __ok = 2;
int const __back = 3;
int const __buzzer = 4;
bool __ok_status = LOW;
bool __back_status = LOW;

Push_Button ok_btn (__ok, __buzzer);
Push_Button back_btn (__back, __buzzer);


void setup(void) {
  new_s.x = 10.02;
  new_s.y = 23.12;
  new_s.z = 7.19;
  new_s.sdCard_status = false;
  new_s.spindle_status = true;
  Serial.begin(9600);

}

void loop(void) {
  new_s.homePage();
  __ok_status = ok_btn.get_current_status();
  while( !__ok_status){
    new_s.mainMenu();
  }

}
