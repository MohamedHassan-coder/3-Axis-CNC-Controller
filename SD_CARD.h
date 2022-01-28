#include "Arduino.h"
#include <SPI.h>
#include <SD.h>
#define pin 4

//Notes::::
//to load a file you must open it first
//don't forget to close the file when you are finished
//the class can open one file each time
//you must close the current one to open another
// to load a file you must open it first
//cannot load files from sd card if **config.mach** file doesn't exsit <<<<----------------------- /*IMPORTANT*\

class SD_CARD {
  public:
    SD_CARD();
    bool sdAvailable();//
    void getFilesData();//
    void loadCurrentFile();
    void openFile(String);//
    void closeFile();//
    String files_names = "";
    String files_sizes = "";
    void pr();
    int getNumber();
    String getFileName(int);
    bool isConfigFileExist();
    void createConfigFile();
    void loadToFile();
    void loadFromFile();
    String line =  "1,0,1,A";

  private:
    File root , myFile , dir;
    String filename;
    bool sd_there , file_opend;
    int number_of_files = 0;
    int serial_delay = 100;
    String check = "FILE1.TXT";
    String temp;
    String configName = "config.txt";
    //Data Stored in config file
    String fileResumed = "0";
    String lastFile = "NONE";
    String lastLineExcuted = "-1";

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
      temp = files_names;
      entry.close();
      number_of_files++;
    }
  }
}

void SD_CARD:: openFile(String file_name) {
  if (sd_there) {
    if (!file_opend) {
      Serial.println("open file");
      myFile = SD.open(file_name);
      if (myFile) {
        file_opend = true;
      } else {
        file_opend = false;
      }
    }
  }
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
        Serial1.write(myFile.read());
      }
    }
  }
}

void SD_CARD :: pr() {
  for (int i = 0 ; i < 6 ; i++) {
    Serial.println(files_names[i]);
  }
}

int SD_CARD ::getNumber() {
  int x = 0;
  for (int i = 0 ; i < files_names.length(); i++) {
    if (files_names[i] == ',') {
      x++;
    }
  }
  return x;
}

String SD_CARD:: getFileName(int file_number) {
  String main = files_names;
  String files = files_names;
  String s1;
  for (int i = 0; i < file_number ; i++) {
    s1 = strtok (files.c_str(), ",");
    main.replace(s1 + "," , "\0");
    files = main;
  }
  return s1;
}

bool SD_CARD::isConfigFileExist() {
  if (SD.exists(configName)) {
    return true;
    //all things are good
  } else {
    //some MF removed it and needed to be created again
    myFile = SD.open(configName, FILE_WRITE);
    Serial.println("some MF removed it and needed to be created again");
    myFile.close();
    return true;
  }
}

void SD_CARD:: loadToFile() {
  closeFile();
  if (isConfigFileExist()) {
    myFile = SD.open(configName , FILE_WRITE);
    Serial.println("Loading TO....");
    if (myFile) {
      myFile.println(line);
      Serial.println("writing");
    } else {
      Serial.println("error opening File");
    }
    closeFile();
  }
}

void SD_CARD:: loadFromFile() {
  closeFile();
  if (isConfigFileExist()) {
    myFile = SD.open(configName , FILE_READ);
    Serial.println("Loading from....");
    while (myFile.available()) {
      //Serial.println("Reading");
      line += myFile.read();
    }
    closeFile();
  }
}
