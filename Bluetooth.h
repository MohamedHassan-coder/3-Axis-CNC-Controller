#include "Arduino.h"
#include <SoftwareSerial.h>
#define EN 36

SoftwareSerial BT(15, 18);   // RX | TX

class Bluetooth {

  public:
    Bluetooth();
    void bt_begin();
    void bt_receive();
    void bt_send();
    void bt_open();
    void bt_close();

  private:

};

Bluetooth :: Bluetooth() {
  pinMode(36 , OUTPUT);
}

void Bluetooth :: bt_begin() {
  bt_begin();
  //BT.begin(9600);
  Serial.begin(115200);
}

void Bluetooth :: bt_receive() {
  //  //BT.listen();
  //  int incomingByte = 0;
  //  //  String recieved_data;
  //  //  if (BT.available()) {
  //  //    incomingByte = BT.read();
  //  //    //    recieved_data = BT.read();
  //  //    Serial.println(incomingByte, DEC);
  //  //  }
  //  if (BT.available() > 0) {
  //    // read the incoming byte:
  //    incomingByte = BT.read();
  //    // say what you got:
  //    BT.print("I received: ");
  //    BT.println(incomingByte, DEC);
  //  }

}

void Bluetooth :: bt_send() {
  String data_sent = "0";
  BT.println(data_sent);
}

void Bluetooth :: bt_open() {
  digitalWrite(EN , HIGH);
}

void Bluetooth::bt_close() {
  digitalWrite(EN , LOW);
}



/*
   void send_data() {
  String data_sent = "0" + String(humidity)  + String(test_temp) + String(fan_state) + String(lamp_state);
  Serial.println(data_sent);
  }
*/
