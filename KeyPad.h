#include "Arduino.h"
#include <Keypad.h>

class KeyPad {
  public:
    KeyPad();
    String getData_feedRate();
    String getData_speed();
    String getData(String);
    bool keyPressed();
    String data = "";
    String feedRate_P;
    String speed_p;


  private:
    char hexaKeys[4][4] = {
      {'1', '2', '3', 'A'},
      {'4', '5', '6', 'B'},
      {'7', '8', '9', 'C'},
      {'.', '0', '#', 'D'}
    };
    byte rowPins[4] = {28, 30, 32, 34};
    byte colPins[4] = {29, 31, 33, 35};
    int buzzer_pin = 7;
    Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, 4, 4);

};

KeyPad::KeyPad() {
  pinMode(buzzer_pin, OUTPUT);
}

String KeyPad::getData_feedRate() {
  String k = (String) customKeypad.getKey();
  if (k != NO_KEY && k != "#" && k != "A" && k != "B" && k != "C" && k != "D") {
    data += k;
  }
  if (data != "") {
    return data;
  } else {
    return feedRate_P;
  }
}

String KeyPad::getData_speed() {
  String s = (String) customKeypad.getKey();
  if (s != NO_KEY && s != "#" && s != "A" && s != "B" && s != "C" && s != "D") {
    data += s;
  }
  if (data != "") {
    return data;
  } else {
    return speed_p;
  }
}
String KeyPad::getData(String data_default) {
  String s = (String) customKeypad.getKey();
  if (s != NO_KEY && s != "#" && s != "A" && s != "B" && s != "C" && s != "D") {
    data += s;
  }
  if (data != "") {
    return data;
  } else {
    return data_default;
  }
}
