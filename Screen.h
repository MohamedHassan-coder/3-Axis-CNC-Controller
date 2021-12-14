#include "Arduino.h"
#include "U8glib.h"
U8GLIB_ST7920_128X64_1X u8g(10, 9, 8);  // SPI Com: SCK = en = 18, MOSI = rw = 16, CS = di = 17

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

#define Arrow_width 10
#define Arrow_height 5
const uint8_t Arrow_bits[]U8G_PROGMEM = {
  0x60, 0x00, 0xfe, 0x00, 0xfe, 0x01, 0xfe, 0x00, 0x60, 0x00
};

class Screen {
  public:
    Screen();
    void homePage();
    void mainMenu();
    void jogMenu();
    void mcConfig1();
    void mcConfig2();
    void features();
    void moveAxis();
    void setOrigin();
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;
    bool sdCard_status  , spindle_status;
    void setCoordinates(int ,  int , int );
    void setSdCard_status(bool);
    void setSpindle_status();
    void current_file_data(String  , float , float );
    void go();
    void setSelection(int);
    void initial();


  private:
    void _draw_spindle();
    void _draw_Sd_card();
    void _draw_axis();
    void _make_coordinates();
    void _other();
    void _drawArrow();
    void _drawSelectionBox(int);
    String __file_name = "NONE";
    float __time_left = 00.00 , __work_precentage = 00.00;
    int __text_begin = 12 , __line_begin = 5;
    int __selection = 1;

};

Screen:: Screen() {
  u8g.setColorIndex(1);
}

void Screen:: initial() {
  u8g.setColorIndex(1);
  mainMenu();
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
  u8g.drawVLine(33, 55, 8);
  u8g.drawStr(40, 53, w.c_str());
  u8g.drawStr(70, 53, "%");
  u8g.drawVLine(77, 55, 8);
  u8g.drawFrame(80, 56, 45, 6);
  u8g.drawBox(80, 56, box_width, 6);
}

void Screen:: setSelection(int select) {
  __selection = select;
}

void Screen:: homePage() {
  u8g.firstPage();
  do {
    _draw_spindle();
    _draw_Sd_card();
    _draw_axis();
    _make_coordinates();
    _other();
  } while ( u8g.nextPage() );
}


void Screen:: _drawSelectionBox(int selecttion) {
  switch (selecttion) {
    case 1:
      u8g.drawHLine(2 , 18 , 124);
      u8g.drawHLine(2 , 31 , 124);
      break;
    case 2:
      u8g.drawHLine(2 , 32 , 124);
      u8g.drawHLine(2 , 45 , 124);
      break;
    case 3:
      u8g.drawHLine(2 , 45 , 124);
      u8g.drawHLine(2 , 60 , 124);
      break;
  }
}
void Screen:: mainMenu() {
  Serial.println("Main Menu");
  String s = "Main Menu";
  int w = u8g.getStrWidth(s.c_str());
  int middle = 64 - w / 2;
  u8g.firstPage();
  do {
    _drawSelectionBox(__selection);
    u8g.setFontPosCenter();
    u8g.setFont(u8g_font_6x10);
    u8g.drawFrame(0, 0, 128, 64);
    u8g.drawStr(middle, 9, s.c_str());
    u8g.drawHLine(middle - 3 , 14 , w + 4);
    //
    u8g.drawHLine(__line_begin , 25 , 5);
    u8g.drawStr(__text_begin , 25 , "Jogging.");
    u8g.drawXBMP( 115, 23, Arrow_width, Arrow_height, Arrow_bits);
    //
    u8g.drawHLine(__line_begin , 40, 5);
    u8g.drawStr(__text_begin , 40 , "Configration.");
    u8g.drawXBMP( 115, 38, Arrow_width, Arrow_height, Arrow_bits);
    //
    u8g.drawHLine(__line_begin , 55 , 5);
    u8g.drawStr(__text_begin , 55 , "Cool Things.");
    u8g.drawXBMP( 115, 53, Arrow_width, Arrow_height, Arrow_bits);
  } while ( u8g.nextPage() );
}

void Screen:: jogMenu() {
  String s = "Jogging Menu";
  int w = u8g.getStrWidth(s.c_str());
  int middle = 64 - w / 2;
  u8g.firstPage();
  do {
    _drawSelectionBox(__selection);
    u8g.setFontPosCenter();
    u8g.setFont(u8g_font_6x10);
    u8g.drawFrame(0, 0, 128, 64);
    u8g.drawStr(middle, 9, s.c_str());
    u8g.drawHLine(middle - 3 , 14 , w + 4);
    //
    u8g.drawHLine(__line_begin , 25 , 5);
    u8g.drawStr(__text_begin , 25 , "Move Axis.");
    u8g.drawXBMP( 115, 23, Arrow_width, Arrow_height, Arrow_bits);
    //
    u8g.drawHLine(__line_begin , 40, 5);
    u8g.drawStr(__text_begin , 40 , "Homing.");
    //
    u8g.drawHLine(__line_begin , 55 , 5);
    u8g.drawStr(__text_begin , 55 , "Set New Origin.");
    u8g.drawXBMP( 115, 53, Arrow_width, Arrow_height, Arrow_bits);
    _drawSelectionBox(__selection);
  } while ( u8g.nextPage() );
}

void Screen :: mcConfig1() {
  String s = "M/C Config Menu";
  int w = u8g.getStrWidth(s.c_str());
  int middle = 64 - w / 2;
  u8g.firstPage();
  do {
    _drawSelectionBox(__selection);
    u8g.setFontPosCenter();
    u8g.setFont(u8g_font_6x10);
    u8g.drawFrame(0, 0, 128, 64);
    u8g.drawStr(middle, 9, s.c_str());
    u8g.drawHLine(middle - 3 , 14 , w + 4);
    //
    u8g.drawHLine(__line_begin , 25 , 5);
    u8g.drawStr(__text_begin , 25 , "Callibration.");
    u8g.drawXBMP( 115, 23, Arrow_width, Arrow_height, Arrow_bits);
    //
    u8g.drawHLine(__line_begin , 40, 5);
    u8g.drawStr(__text_begin , 40 , "Feed Rate.");
    u8g.drawXBMP( 115, 38, Arrow_width, Arrow_height, Arrow_bits);
    //
    u8g.drawHLine(__line_begin , 55 , 5);
    u8g.drawStr(__text_begin , 55 , "Spindle Settings.");
    u8g.drawXBMP( 115, 53, Arrow_width, Arrow_height, Arrow_bits);
    _drawSelectionBox(__selection);

  } while ( u8g.nextPage() );
}


void Screen :: mcConfig2() {
  String s = "M/C Config Menu";
  int w = u8g.getStrWidth(s.c_str());
  int middle = 64 - w / 2;
  u8g.firstPage();
  do {
    _drawSelectionBox(__selection);
    u8g.setFontPosCenter();
    u8g.setFont(u8g_font_6x10);
    u8g.drawFrame(0, 0, 128, 64);
    u8g.drawStr(middle, 9, s.c_str());
    u8g.drawHLine(middle - 3 , 14 , w + 4);
    //
    u8g.drawHLine(__line_begin , 25 , 5);
    u8g.drawStr(__text_begin , 25 , "Grbl Settings.");
    u8g.drawXBMP( 115, 23, Arrow_width, Arrow_height, Arrow_bits);
    //
    u8g.drawHLine(__line_begin , 40, 5);
    u8g.drawStr(__text_begin , 40 , "Screen Settings.");
    u8g.drawXBMP( 115, 38, Arrow_width, Arrow_height, Arrow_bits);
    //
    u8g.drawHLine(__line_begin , 55 , 5);
    u8g.setFont(u8g_font_6x10);
    u8g.drawStr(__text_begin , 55 , "About...");
    u8g.drawXBMP( 115, 53, Arrow_width, Arrow_height, Arrow_bits);
    _drawSelectionBox(__selection);

  } while ( u8g.nextPage() );
}

void Screen:: features() {
  String s = "Features Menu";
  int w = u8g.getStrWidth(s.c_str());
  int middle = 64 - w / 2;
  u8g.firstPage();
  do {
    _drawSelectionBox(__selection);
    u8g.setFontPosCenter();
    u8g.setFont(u8g_font_6x10);
    u8g.drawFrame(0, 0, 128, 64);
    u8g.drawStr(middle, 9, s.c_str());
    u8g.drawHLine(middle - 3 , 14 , w + 4);
    //
    u8g.drawHLine(__line_begin , 25 , 5);
    u8g.drawStr(__text_begin , 25 , "SD-Card Files.");
    if (sdCard_status) {
      u8g.drawXBMP( 115, 23, Arrow_width, Arrow_height, Arrow_bits);
    }
    //
    u8g.drawHLine(__line_begin , 40, 5);
    u8g.drawStr(__text_begin , 40 , "Bluetooh.");
    u8g.drawXBMP( 115, 38, Arrow_width, Arrow_height, Arrow_bits);
    //
    u8g.drawHLine(__line_begin , 55 , 5);
    u8g.setFont(u8g_font_6x10);
    u8g.drawStr(__text_begin , 55 , "IOT(: .");
    u8g.drawXBMP( 115, 53, Arrow_width, Arrow_height, Arrow_bits);
    _drawSelectionBox(__selection);

  } while ( u8g.nextPage() );
}

void Screen:: moveAxis() {
  String s = "Move Axis";
  String xs = "X --> ";
  String ys = "Y --> ";
  String zs = "Z --> ";
  String X_pos = String(x);
  String Y_pos = String(y);
  String Z_pos = String(z);
  int w = u8g.getStrWidth(s.c_str());
  int middle = 64 - w / 2;
  int x_width = u8g.getStrWidth(xs.c_str());
  int y_width = u8g.getStrWidth(ys.c_str());
  int z_width = u8g.getStrWidth(zs.c_str());
  u8g.firstPage();
  do {
    u8g.setFontPosCenter();
    u8g.setFont(u8g_font_6x10);
    u8g.drawFrame(0, 0, 128, 64);
    u8g.drawStr(middle, 9, s.c_str());
    u8g.drawHLine(middle - 3 , 14 , w + 4);
    //
    u8g.drawHLine(__line_begin , 25 , 5);
    u8g.drawStr(__text_begin , 25 , xs.c_str());
    u8g.drawStr(x_width + 10, 25, X_pos.c_str());

    //
    u8g.drawHLine(__line_begin , 40, 5);
    u8g.drawStr(__text_begin , 40 , ys.c_str());
    u8g.drawStr(y_width + 10, 40, Y_pos.c_str());

    //
    u8g.drawHLine(__line_begin , 55 , 5);
    u8g.drawStr(__text_begin , 55 , zs.c_str());
    u8g.drawStr(z_width + 10, 55, Z_pos.c_str());
  } while ( u8g.nextPage() );
}

void Screen:: setOrigin() {
  String s = "Set New Origin";
  String xs = "X --> ";
  String ys = "Y --> ";
  String zs = "Z --> ";
  String X_pos = String(x);
  String Y_pos = String(y);
  String Z_pos = String(z);
  int w = u8g.getStrWidth(s.c_str());
  int middle = 64 - w / 2;
  int x_width = u8g.getStrWidth(xs.c_str());
  int y_width = u8g.getStrWidth(ys.c_str());
  int z_width = u8g.getStrWidth(zs.c_str());
  u8g.firstPage();
  do {
    u8g.setFontPosCenter();
    u8g.setFont(u8g_font_6x10);
    u8g.drawFrame(0, 0, 128, 64);
    u8g.drawStr(middle, 9, s.c_str());
    u8g.drawHLine(middle - 3 , 14 , w + 4);
    //
    u8g.drawHLine(__line_begin , 25 , 5);
    u8g.drawStr(__text_begin , 25 , xs.c_str());
    u8g.drawStr(x_width + 10, 25, X_pos.c_str());

    //
    u8g.drawHLine(__line_begin , 40, 5);
    u8g.drawStr(__text_begin , 40 , ys.c_str());
    u8g.drawStr(y_width + 10, 40, Y_pos.c_str());

    //
    u8g.drawHLine(__line_begin , 55 , 5);
    u8g.drawStr(__text_begin , 55 , zs.c_str());
    u8g.drawStr(z_width + 10, 55, Z_pos.c_str());
  } while ( u8g.nextPage() );
}

void Screen :: setSdCard_status(bool stat){
  sdCard_status = stat;
}

//void Screen ::go() {
//  u8g.firstPage();
//  do {
//    setOrigin();
//  } while ( u8g.nextPage() );
//}
