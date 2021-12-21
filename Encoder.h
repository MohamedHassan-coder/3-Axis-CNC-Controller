#include "Arduino.h"

class Encoder {
  public:
    Encoder();
    void currentSelection();
    void resetChoice();
    void resetCounter();
    void multiMenu(bool);
    int getCounter();
    int getChoice();
    void multiSelection();

  private:
    void currentPosition();
    //bool multiFlag = false;
    int choice = 0;
    int counter = 0;
    int newState;
    int LastState;
    int const encoder1 = 3;
    int const encoder2 = 6;
};

Encoder:: Encoder() {
  pinMode (encoder1, INPUT);
  pinMode (encoder2, INPUT);
}


void Encoder:: resetChoice() {
  choice = 0;
}

void Encoder:: resetCounter() {
  counter = 0;
}

//void Encoder:: multiMenu(bool f) {
//  multiFlag = f;
//}

void Encoder:: currentPosition() {
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

void Encoder:: currentSelection() {
  //  Serial.print("Position: ");
  //  Serial.println(counter);
  currentPosition();
  int first = 2;
  int second = 5;
  int third = 8;
  int forth = 11;
  int sixth = 14;
  int seventh = 17;
  if ( 0 <= counter && counter < first) {
    choice =  1;
  } else if (first < counter && counter < second) {
    choice =  2;
  }
  else if (second < counter && counter < third) {
    choice =  3;
  }
  if (counter > forth ) {
    counter = 12;
    choice =  3;
  }
  if (counter < 0) {
    choice = 1;
    counter = 0;
  }
}

int Encoder:: getCounter() {
  return counter;
}

int Encoder:: getChoice() {
  return choice;
}

void Encoder:: multiSelection() {
  currentPosition();
  int first = 2;
  int second = 5;
  int third = 8;
  int forth = 11;
  int sixth = 14;
  int seventh = 17;
  if ( 0 <= counter && counter < first) {
    choice =  1;
  } else if (first < counter && counter < second) {
    choice =  2;
  }
  else if (second < counter && counter < third) {
    choice =  3;
  }
  if ( third < counter && counter < forth) {
    choice =  4;
  } else if (forth < counter && counter < sixth) {
    choice =  5;
  }
  else if (sixth < counter && counter < seventh) {
    choice =  6;
  } else if (counter > seventh ) {
    counter = seventh + 1;
    choice =  6;
  }
  if (counter < 0) {
    choice = 1;
    counter = 0;
  }
}
