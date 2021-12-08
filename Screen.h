#include "Arduino.h"
#include "U8glib.h"
U8GLIB_ST7920_128X64_1X u8g(13, 11, 10);  // SPI Com: SCK = en = 18, MOSI = rw = 16, CS = di = 17

#define SD_card_width 15
#define SD_card_height 20
const uint8_t SD_card_bits[] U8G_PROGMEM = {
  0xff, 0x03, 0xff, 0x07, 0xff, 0x0f, 0xff, 0x1f, 0xff, 0x3f, 0xff, 0x7f,
  0xff, 0x7f, 0xff, 0x7f, 0xff, 0x7f, 0xff, 0x7f, 0xff, 0x7f, 0xff, 0x7f,
  0xff, 0x7f, 0xff, 0x7f, 0xff, 0x7f, 0xff, 0x7f, 0xff, 0x7f, 0x01, 0x40,
  0x01, 0x40, 0xff, 0x7f
};

#define SD_card_none_width 15
#define SD_card_none_height 20
const uint8_t SD_card_none_bits[] U8G_PROGMEM = {
  0xff, 0x03, 0xff, 0x07, 0xff, 0x0f, 0xff, 0x1f, 0xff, 0x3f, 0x07, 0x78,
  0x0b, 0x74, 0x13, 0x72, 0x23, 0x71, 0xc3, 0x70, 0xc3, 0x70, 0x23, 0x71,
  0x13, 0x72, 0x0b, 0x74, 0x07, 0x78, 0xff, 0x7f, 0xff, 0x7f, 0x01, 0x40,
  0x01, 0x40, 0xff, 0x7f
};

#define Spindle_off_width 15
#define Spindle_off_height 20
const uint8_t  Spindle_off_bits[] U8G_PROGMEM = {
  0xf8, 0x0f, 0x78, 0x0c, 0x38, 0x0e, 0x18, 0x0f, 0x88, 0x0f, 0xc8, 0x0b,
  0xe8, 0x09, 0xf8, 0x08, 0x78, 0x0c, 0x38, 0x0e, 0x18, 0x0f, 0xf8, 0x0f,
  0xf8, 0x0f, 0xf0, 0x07, 0xe0, 0x03, 0xc0, 0x01, 0x80, 0x00, 0x80, 0x00,
  0x80, 0x00, 0x80, 0x00
};

#define Spindle_on_width 15
#define Spindle_on_height 20
const uint8_t  Spindle_on_bits[] U8G_PROGMEM = {
  0xf8, 0x0f, 0xc8, 0x0f, 0xe8, 0x0b, 0xf8, 0x09, 0xf8, 0x0c, 0x78, 0x0e,
  0x38, 0x0f, 0x98, 0x0f, 0xc8, 0x0f, 0xe8, 0x0b, 0xf8, 0x09, 0xf8, 0x0f,
  0xf8, 0x0f, 0xf0, 0x07, 0xe0, 0x03, 0xc8, 0x09, 0x90, 0x04, 0xa0, 0x02,
  0xc0, 0x01, 0xa0, 0x02
};

#define Axes_width 20
#define Axes_height 20
const uint8_t  Axes_bits[]U8G_PROGMEM = {
  0x00, 0x01, 0x00, 0x80, 0xf3, 0x01, 0xc0, 0x07, 0x01, 0x00, 0x81, 0x00,
  0x00, 0x41, 0x00, 0x00, 0x21, 0x00, 0x00, 0xf1, 0x01, 0x00, 0x01, 0x00,
  0x00, 0x01, 0x00, 0x09, 0x01, 0x02, 0x09, 0x01, 0x06, 0x0f, 0xff, 0x0f,
  0x88, 0x00, 0x06, 0x49, 0x00, 0x02, 0x2f, 0x88, 0x00, 0x10, 0x50, 0x00,
  0x0a, 0x20, 0x00, 0x06, 0x50, 0x00, 0x0e, 0x88, 0x00, 0x00, 0x00, 0x00
};


class Screen {

  public:
    Screen();
    void homePage();
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;
    bool sdCard_status  , spindle_status;
    void setCoordinates(int ,  int , int );
    void setSdCard_status();
    void setSpindle_status();
    void current_file_data(String  , float , float );
    void go();

  private:
    void _draw_spindle();
    void _draw_Sd_card();
    void _draw_axis();
    void _make_coordinates();
    void _other();
    String __file_name = "NONE";
    float __time_left = 00.00 , __work_precentage = 00.00;

};
//u8g.setFont(u8g_font_6x12);
Screen:: Screen() {
  u8g.setColorIndex(1);
}

void Screen:: _draw_spindle() {
  u8g.setFont(u8g_font_04b_03r);
  switch (spindle_status) {
    case true:
      u8g.drawXBMP( 2, 2, Spindle_on_width, Spindle_on_height, Spindle_on_bits);
      u8g.drawStr(2 , 30 , "Spindle: ON.");
      break;
    case false:
      u8g.drawXBMP( 2, 2, Spindle_off_width, Spindle_off_height, Spindle_off_bits);
      u8g.drawStr(2 , 30 , "Spindle: OFF.");
      break;
  }
}

void Screen::_draw_Sd_card() {
  u8g.setFont(u8g_font_04b_03r);
  switch (sdCard_status) {
    case true:
      u8g.drawXBMP( 108, 2, SD_card_width, SD_card_height, SD_card_bits);
      u8g.drawStr(87 , 30 , "SD: Exist.");
      break;
    case false:
      u8g.drawXBMP( 108, 2, SD_card_width, SD_card_height, SD_card_none_bits);
      u8g.drawStr(87 , 30 , "SD: NONE.");
      break;
  }
}

void Screen:: _draw_axis() {
  u8g.drawXBMP( 54, 2, Axes_width, Axes_height, Axes_bits);
}

void Screen:: _make_coordinates() {
  String X_pos = String(x);
  String Y_pos = String(y);
  String Z_pos = String(z);

  u8g.setFont(u8g_font_6x12);
  u8g.drawFrame(0, 32, 128, 11);
  //X
  u8g.drawStr(2, 41 , "X:");
  u8g.drawStr(12, 41 , X_pos.c_str());
  //Y
  u8g.drawStr(47, 41 , "Y:");
  u8g.drawStr(57, 41 , Y_pos.c_str());
  //Z
  u8g.drawStr(92, 41 , "Z: ");
  u8g.drawStr(103, 41 , Z_pos.c_str());
}

void Screen:: _other() {
  String t = String(__time_left);
  String w = String(__work_precentage);
  int box_width = __work_precentage * 0.45;
  u8g.setFont(u8g_font_6x12);
  u8g.setFontPosTop();
  u8g.drawStr(2, 44, "File");
  u8g.drawStr(28, 44, "Name:");
  u8g.drawStr(60, 44, __file_name.c_str());
  u8g.drawStr(2, 53, t.c_str());
  u8g.drawVLine(33,55,8);
  u8g.drawStr(40, 53, w.c_str());
  u8g.drawStr(70, 53, "%");
  u8g.drawVLine(77,55,8); 
  u8g.drawFrame(80, 56, 45, 6);
  u8g.drawBox(80, 56, box_width, 6);
  //u8g.drawHLine(2 , 55 , 10);
}

void Screen:: homePage() {
  _draw_spindle();
  _draw_Sd_card();
  _draw_axis();
  _make_coordinates();
  _other();
  //u8g.drawFrame(0, 0, 128, 64);

}

void Screen ::go() {
  u8g.firstPage();
  do {
    homePage();
  } while ( u8g.nextPage() );
}
