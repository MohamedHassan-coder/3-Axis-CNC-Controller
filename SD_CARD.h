#include "Arduino.h"
#include <SPI.h>
#include <SD.h>
#define pin 4

//Notes::::
//to load a file you must open it first
//don't forget to close the file when you are finished
//the class can open one file each time
//you must close the current one to open another
//max number of files to be displayed --> 9 files
// to load a file ypu must open it first

class SD_CARD {
  public:
    SD_CARD();
    bool sdAvailable();//
    void getFilesData();//
    void loadCurrentFile();
    void openFile(int);//
    void closeFile();//
    String files_names = "";
    String files_sizes = "";
    void pr();

  private:
    File root , myFile , dir;
    String filename;
    bool sd_there , file_opend;
    int number_of_files = 0;
    int serial_delay = 100;
    String check = "FILE1.TXT";
};

SD_CARD:: SD_CARD() {
}

bool SD_CARD:: sdAvailable() {
  if (SD.begin(pin)) {
    sd_there = true;
    return true;
  } else {
    sd_there = false;
    return false;
  }
}

void SD_CARD:: getFilesData() {
  if (sd_there) {
    root = SD.open("/");
    while (true) {
      File entry =  root.openNextFile();
      if (! entry) {
        // no more files
        break;
      }
      if (!entry.isDirectory()) {
        files_names += String(entry.name());
        files_names += ",";
        files_sizes += String(entry.size());
        files_sizes += ",";
      }
      entry.close();
      number_of_files++;
    }
  }
}

void SD_CARD:: openFile(int file_number) {
  //  if (sd_there) {
  //    if (!file_opend) {
  //      String s = files_names[file_number];
  //      myFile = SD.open(s);
  //      if (myFile) {
  //        file_opend = true;
  //      } else {
  //        file_opend = false;
  //      }
  //    }
  //  }
}

void SD_CARD:: closeFile() {
  if (sd_there) {
    myFile.close();
    file_opend = false;
  }
}

void SD_CARD :: loadCurrentFile() {
  if (sd_there) {
    if (file_opend) {
      while (myFile.available()) {
        Serial.write(myFile.read());
      }
    }
  }
}

void SD_CARD :: pr() {
  for (int i = 0 ; i < 6 ; i++) {
    Serial.println(files_names[i]);
  }
}
