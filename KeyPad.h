#include "Arduino.h"
#include <Keypad.h>

class KeyPad {
  public:
    KeyPad();
    String getData_feedRate();
    String getData_speed();
    String getData(String);
    void getData();
    bool keyPressed();
    String data = "";
    String feedRate_P;
    String speed_p;
    String default_key = "";


  private:
    char normal_Keys[4][4] = {
      {'1', '2', '3', ' '},
      {'4', '5', '6', ' '},
      {'7', '8', '9', ' '},
      {'.', '0', ' ', ' '}
    };

    char default_keys[4][4] = {
      {'X', 'Y', 'Z', 'T'},
      {'x', 'y', 'z', 'H'},
      {'A', 'B', ' ', 'R'},
      {'a', 'b', 'K', 'U'}
    };
    byte rowPins[4] = {28, 30, 32, 34};
    byte colPins[4] = {29, 31, 33, 35};
    int buzzer_pin = 7;
    Keypad normalKeypad = Keypad( makeKeymap(normal_Keys), rowPins, colPins, 4, 4);
    Keypad defaultKeypad = Keypad( makeKeymap(default_keys), rowPins, colPins, 4, 4);

};

KeyPad::KeyPad() {
  pinMode(buzzer_pin, OUTPUT);
}

String KeyPad::getData_feedRate() {
  String k = (String) normalKeypad.getKey();
  if (k != NO_KEY && k != "#" && k != "A" && k != "B" && k != "C" && k != "D") {
    data += k;
  }
  if (data != "") {
    return data;
  } else {
    return feedRate_P;
  }
}

//these methods for Normal keybad only
//////////////////////////
String KeyPad::getData_speed() {
  String s = (String) normalKeypad.getKey();
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
  String s = (String) normalKeypad.getKey();
  if (s != NO_KEY && s != "#" && s != "A" && s != "B" && s != "C" && s != "D" && s != " ") {
    data += s;
  }
  if (data != "") {
    return data;
  } else {
    return data_default;
  }
}
//////////////////////////
//////////////////////////
//////////////////////////
//these methods for default keybad only
void KeyPad::getData() {
  String s = (String) defaultKeypad.getKey();
  if (s != "" && s != NO_KEY && s != " ") {
    default_key = s;
    //Serial.println("Char is " + s);
  } else {
    default_key = "";
  }
}
