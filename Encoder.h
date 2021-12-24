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
    void sd_select();
    int sd_row;
    int sd_column;
    int sd_choice;

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

void Encoder:: sd_select() {
  currentPosition();
  //first coulmn
  if (0 < counter && counter < 3) {
    sd_row = 1;
    sd_column = 1;
    sd_choice = 1;
  } else if (3 <= counter && counter < 5 ) {
    sd_row = 2;
    sd_column = 1;
    sd_choice = 2;
  } else if ( 5 <= counter && counter < 7 ) {
    sd_row = 3;
    sd_column = 1;
    sd_choice = 3;
  } else if (7 <= counter && counter < 9 ) {
    sd_row = 4;
    sd_column = 1;
    sd_choice = 4;
  } else if (9 <= counter && counter < 11 ) {
    sd_row = 5;
    sd_column = 1;
    sd_choice = 5;
  } else if (11 <= counter && counter < 13 ) {
    sd_row = 6;
    sd_column = 1;
    sd_choice = 6;
  }
  //second column
  else if (13 <= counter && counter < 15 ) {
    sd_row = 1;
    sd_column = 2;
    sd_choice = 7;
  } else if ( 15 <= counter && counter < 17 ) {
    sd_row = 2;
    sd_column = 2;
    sd_choice = 8;
  } else if (17 <= counter && counter < 19 ) {
    sd_row = 3;
    sd_column = 2;
    sd_choice = 9;
  } else if (19 <= counter && counter < 21) {
    sd_row = 4;
    sd_column = 2;
    sd_choice = 10;
  } else if (21 <= counter && counter < 23 ) {
    sd_row = 5;
    sd_column = 2;
    sd_choice = 11;
  } else if (23 <= counter && counter < 25 ) {
    sd_row = 6;
    sd_column = 2;
    sd_choice = 12;
  } else {
    sd_row = 1;
    sd_column = 1;
  }
}
