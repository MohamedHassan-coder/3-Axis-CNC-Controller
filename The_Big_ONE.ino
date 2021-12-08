#include "Screen.h"

Screen new_s;

void setup(void) {
  new_s.x = 10.02;
  new_s.y = 23.12;
  new_s.z = 7.19;
  new_s.sdCard_status = true;
  new_s.spindle_status = true;

}

void loop(void) {
new_s.go();
}
