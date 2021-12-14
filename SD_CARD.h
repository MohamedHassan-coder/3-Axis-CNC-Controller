#include "Arduino.h"
#include <SPI.h>
#include <SD.h>

//Notes::::
//to load a file you must open it first
//don't forget to close the file when you are finished
//the class can open one file each time
//you must close the current one to open another

class SD_CARD {
  public:
    SD_CARD();
    bool sdAvailable();//
    int getFilesNumber();//
    void loadFile();
    void openFile(String);//
    void closeFile();//
    int getFileSize();//




  private:
    File root , myFile , dir;
    String filename;
    bool sd_there , file_opend;
    int number_of_files = 0;
    int serial_delay = 100;
    String check = "FILE1.TXT";
    int pin = 4;

};

SD_CARD:: SD_CARD() {
}

bool SD_CARD:: sdAvailable() {
  if (SD.begin(pin)) {
    return true;
  } else {
    return false;
  }
    SD.end();
}

int SD_CARD:: getFilesNumber() {
  while (true) {
    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    entry.close();
    number_of_files++;
  }
  return number_of_files;
}

void SD_CARD:: openFile(String fileName) {
  if (!file_opend) {
    root = SD.open("/");
    myFile = SD.open(fileName);
    if (myFile) {
      file_opend = true;
    } else {
      file_opend = false;
    }
  }
}

void SD_CARD:: closeFile() {
  myFile.close();
  file_opend = false;
}

int SD_CARD :: getFileSize() {
  if (file_opend) {
    File entry =  dir.openNextFile();
    if (!entry.isDirectory()) {
      return (entry.size());
    } else {
      //error happened
      return -1;
    }
  }
}

void SD_CARD :: loadFile() {
  if (file_opend) {
    while (myFile.available()) {
      Serial.write(myFile.read());
      delay(serial_delay);
    }
  }
}
