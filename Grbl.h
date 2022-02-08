#include "Arduino.h"

class Grbl {
  public:
    Grbl();
    void set_grbl_value(int , String );
    void print_data();
    void move_axis(int, float , int);
    void homing();
    void unlock();
    void load_settings_values();
    bool settings_exist(String);
    String get_grbl_value(int);
    int get_settings_number(String);
    void Abort();
    void hold();
    void Resume();
    void real_time();



  private:
    String settings_names [31] =      //starts from pos 0 to 30
    { "0", "1", "2", "3", "4", "5", "6", "10",
      "11", "12", "13", "20", "21", "22", "23", "24",
      "25", "26", "27", "100", "101", "102", "110", "111",
      "112", "120", "121", "122", "130", "131", "132"
    };
    String settings_values [31];
    String inputString = "";
    void format(String);
    int l = 0;
    int i = 0;
};

Grbl::Grbl() {
  inputString.reserve(200);
}

void Grbl :: set_grbl_value(int value_num , String value) {
  settings_values[value_num] = value;
  Serial1.println("$" + settings_names[value_num] + " = " + value);
}
String Grbl :: get_grbl_value(int value_number) {
  return settings_values[value_number];
}

void Grbl :: print_data() {
  for (int i = 0 ; i < 31 ; i++) {
    Serial.print("$");
    Serial.print(settings_names[i]);
    Serial.print(" = ");
    Serial.println(settings_values[i]);
  }
}

int Grbl :: get_settings_number(String settings_name) {
  for (int i = 0; i < 31 ; i++) {
    if (settings_names[i] == settings_name) {
      return i;
      break;
    }
  }
}

bool Grbl :: settings_exist(String settings_name) {
  for (int i = 0; i < 31 ; i++) {
    if (settings_names[i] == settings_name) {
      return true;
      break;
    }
  }
  return false;
}

void Grbl:: move_axis(int axis, float accuracy , int feed) {
  String line1 = "G21G91G1";
  String line2 = "G90 G21";
  switch (axis) {
    case 1:
      Serial.println(line1 + "X" + String(accuracy) + "F" + String(feed));
      delay(2);
      Serial.println(line2);
      break;
    case 11:
      Serial.println(line1 + "X - " + String(accuracy) + "F" + String(feed));
      delay(2);
      Serial.println(line2);
      break;
    case 2:
      Serial.println(line1 + "Y" + String(accuracy) + "F" + String(feed));
      delay(2);
      Serial.println(line2);
      break;
    case 22:
      Serial.println(line1 + "Y - " + String(accuracy) + "F" + String(feed));
      delay(2);
      Serial.println(line2);
      break;
    case 3:
      Serial.println(line1 + "Z" + String(accuracy) + "F" + String(feed));
      delay(2);
      Serial.println(line2);
      break;
    case 33:
      Serial.println(line1 + "Z - " + String(accuracy) + "F" + String(feed));
      delay(2);
      Serial.println(line2);
      break;
  }
}

void Grbl :: homing() {
  Serial.println("$H");
  Serial1.println("$H");
}
void Grbl :: unlock() {
  Serial.println("$X");
  Serial1.println("$X");
}

void Grbl :: hold() {
  Serial.println("!");
  Serial1.println("!");
}
void Grbl :: Resume() {
  Serial.println("~");
  Serial1.println("~");
}
void Grbl :: Abort() {
  Serial.println("Abort");
  //Send low to the Abort pin
}

void Grbl:: real_time() {
  Serial.println("?");
  Serial1.println("?");
}

void Grbl :: format(String s) {
  if (s[0] == '$') {
    String temp = s;
    String iden = strtok(temp.c_str() , "=" );
    s.trim();
    s.replace(iden + "=", "\0");
    String value = strtok(s.c_str() , "(" );
    value.trim();
    settings_values[i] = value;
    i++;
  }
}

void Grbl :: load_settings_values() {
  Serial1.print("\r\n\r\n");
  delay(10);
  Serial1.println("$$");
  while (Serial1.available() > 0) {
    inputString = Serial1.readStringUntil('\n');
    format(inputString);
    l++;
    if (l == 36) {
      break;
    }
  }
}
