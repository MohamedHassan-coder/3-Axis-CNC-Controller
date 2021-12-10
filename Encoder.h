# include "Arduino.h"

class Encoder {
  public:
    Encoder();
    int currentSelection();


  private:
    int __counter = 0;
    int __state;
    int __LastState;
    void _currentPosition();
    int __clk = 3 , __data = 4;
};

Encoder :: Encoder() {
}

void Encoder :: _currentPosition() {
  __state = digitalRead(__clk);
  if (__state != __LastState) {
    if (digitalRead(__data) != __state) {
      __counter ++;
    } else {
      __counter --;
    }
  }
  __LastState = __state;
  Serial.println(__counter);
}

int Encoder :: currentSelection() {
  _currentPosition();
  int first = 5;
  int second = 10;
  int third = 15;
  if ( 0 < __counter && __counter < first) {
    return 1;
  } else if (first < __counter && __counter < second) {
    return 2;
  }
  else if (second < __counter && __counter < third) {
    return 3;
  } else {
    return 1;
  }
}
