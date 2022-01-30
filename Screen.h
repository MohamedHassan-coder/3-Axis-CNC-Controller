#include "Arduino.h"
#include "U8glib.h"
U8GLIB_ST7920_128X64_1X u8g(10, 9, 8);

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

#define BT_OFF_width 20
#define BT_OFF_height 20
const uint8_t BT_OFF_bits[]U8G_PROGMEM  = {
  0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x0a, 0x00, 0x08, 0x12, 0x00,
  0x10, 0x22, 0x00, 0x20, 0x42, 0x00, 0x40, 0x22, 0x00, 0x80, 0x12, 0x00,
  0x00, 0x0b, 0x00, 0x00, 0x06, 0x00, 0x00, 0x06, 0x00, 0x00, 0x0b, 0x00,
  0x80, 0x12, 0x00, 0x40, 0x22, 0x00, 0x20, 0x42, 0x00, 0x10, 0x22, 0x00,
  0x08, 0x12, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00
};

#define BT_ON_width 20
#define BT_ON_height 20
const uint8_t BT_ON_bits[]U8G_PROGMEM  = {
  0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x0e, 0x00, 0x08, 0x1e, 0x00,
  0x10, 0x3e, 0x00, 0x20, 0x7e, 0x00, 0x40, 0x3e, 0x00, 0x80, 0x1e, 0x00,
  0x00, 0x0f, 0x00, 0x00, 0x06, 0x00, 0x00, 0x06, 0x00, 0x00, 0x0f, 0x00,
  0x80, 0x1e, 0x00, 0x40, 0x3e, 0x00, 0x20, 0x7e, 0x00, 0x10, 0x3e, 0x00,
  0x08, 0x1e, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00
};

#define Lock_width 20
#define Lock_height 20
const uint8_t Lock_bits[]U8G_PROGMEM = {
  0x00, 0x00, 0x00, 0xfc, 0xff, 0x03, 0x04, 0x00, 0x02, 0x04, 0x00, 0x02,
  0x04, 0x00, 0x02, 0x04, 0x00, 0x02, 0x04, 0x00, 0x02, 0x04, 0x00, 0x02,
  0xfe, 0xff, 0x07, 0xfe, 0xff, 0x07, 0x3e, 0xc0, 0x07, 0xbe, 0xdf, 0x07,
  0xbe, 0xdf, 0x07, 0x3e, 0xc0, 0x07, 0x7e, 0xef, 0x07, 0x7e, 0xef, 0x07,
  0x7e, 0xe0, 0x07, 0xfe, 0xff, 0x07, 0xfe, 0xff, 0x07, 0x00, 0x00, 0x00
};

#define UnLock_width 20
#define UnLock_height 20
const uint8_t UnLock_bits[]U8G_PROGMEM = {
  0x00, 0x00, 0x00, 0xfc, 0xff, 0x03, 0x04, 0x00, 0x02, 0x04, 0x00, 0x00,
  0x04, 0x00, 0x00, 0x04, 0x00, 0x00, 0x04, 0x00, 0x00, 0x04, 0x00, 0x00,
  0xfe, 0xff, 0x07, 0xfe, 0xff, 0x07, 0x3e, 0xc0, 0x07, 0xbe, 0xdf, 0x07,
  0xbe, 0xdf, 0x07, 0x3e, 0xc0, 0x07, 0x7e, 0xef, 0x07, 0x7e, 0xef, 0x07,
  0x7e, 0xe0, 0x07, 0xfe, 0xff, 0x07, 0xfe, 0xff, 0x07, 0x00, 0x00, 0x00
};


class Screen {
  public:
    Screen();
    //Menues:
    void makeMenu(String , String, bool, String, bool, String, bool);
    void homePage();
    void features();
    void moveAxis();
    void setOrigin();
    void sdFiles(String , int);
    void feedRate();
    void spindleSettings();
    void about();
    void grblSettings();
    void grblSettings_new(String);
    void initalizing(String);
    void throwError(String);
    //

    bool sdCard_status , spindle_status , bt_status;
    void current_file_data(String  , float , float );
    void go();
    void setSelection(int);
    void sd_setSelection(int , int);
    void setCoordniates(float , float , float);
    String feed_rate = "100.78";
    String spindle_speed = "1000";
    int spindle_direction = 1; //0-> CW ,1->CCW
    String grbl_settings = "---";
    String grbl_value = "---";


  private:
    void _draw_spindle();
    void _draw_Sd_card();
    void _draw_axis();
    void _draw_bluetooth();
    void _make_coordinates();
    void _other();
    void _drawArrow();
    void _drawSelectionBox(int);
    String __file_name = "NONE";
    float __time_left = 00.00 , __work_precentage = 00.00;
    int __text_begin = 12 , __line_begin = 5;
    int __selection = 1;
    float x , y , z;
    String _getFileName(int);
    String files_names;
    int row , column;
    void _sd_setSelection(int , int);
    String text1 = "", text2 = "" , text3 = "", text4 = "";
    int count = 1;
};

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
  u8g.drawXBMP( 74, 2, Axes_width, Axes_height, Axes_bits);
}

void Screen::_draw_bluetooth() {
  if (bt_status) {
    u8g.drawXBMP( 34, 2, BT_ON_width, BT_ON_height, BT_ON_bits);
  } else {
    u8g.drawXBMP( 34, 2, BT_OFF_width, BT_OFF_height, BT_OFF_bits);
  }
}

void Screen:: _make_coordinates() {
  String X_pos = String(x);
  String Y_pos = String(y);
  String Z_pos = String(z);

  u8g.setFont(u8g_font_6x12);
  u8g.drawFrame(0, 32, 128, 11 );
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
    _draw_bluetooth();
    _make_coordinates();
    _other();
  } while ( u8g.nextPage() );
}


void Screen:: _drawSelectionBox(int selecttion) {

  if (selecttion == 1 || selecttion == 4 ) {
    u8g.drawHLine(2 , 18 , 124);
    u8g.drawHLine(2 , 31 , 124);
  } else   if (selecttion == 2 || selecttion == 5 ) {
    u8g.drawHLine(2 , 32 , 124);
    u8g.drawHLine(2 , 45 , 124);
  } else if (selecttion == 3 || selecttion == 6 ) {
    u8g.drawHLine(2 , 45 , 124);
    u8g.drawHLine(2 , 60 , 124);
  }
}

void Screen:: makeMenu(String title , String row1 , bool row1_status, String row2 , bool row2_status, String row3 , bool row3_status) {
  int w = u8g.getStrWidth(title.c_str());
  int middle = 64 - w / 2;
  u8g.firstPage();
  do {
    _drawSelectionBox(__selection);
    u8g.setFontPosCenter();
    u8g.setFont(u8g_font_6x10);
    u8g.drawFrame(0, 0, 128, 64);
    u8g.drawStr(middle, 9, title.c_str());
    u8g.drawHLine(middle - 3 , 14 , w + 4);
    //
    u8g.drawHLine(__line_begin , 25 , 5);
    u8g.drawStr(__text_begin , 25 , row1.c_str());
    if (row1_status) {
      u8g.drawXBMP( 115, 23, Arrow_width, Arrow_height, Arrow_bits);
    }
    //
    u8g.drawHLine(__line_begin , 40, 5);
    u8g.drawStr(__text_begin , 40 , row2.c_str());
    if (row2_status) {
      u8g.drawXBMP( 115, 38, Arrow_width, Arrow_height, Arrow_bits);
    }
    //
    u8g.drawHLine(__line_begin , 55 , 5);
    u8g.drawStr(__text_begin , 55 , row3.c_str());
    if (row3_status) {
      u8g.drawXBMP( 115, 53, Arrow_width, Arrow_height, Arrow_bits);
    }
  } while ( u8g.nextPage() );
}
void Screen:: features() {
  String s = "Features & Other";
  int w = u8g.getStrWidth(s.c_str());
  int middle = 64 - w / 2;
  //
  String bt = "";
  if (bt_status) {
    bt = "ON";
  } else {
    bt = "OFF";
  }
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
    u8g.drawStr(__text_begin , 40 , "Bluetooh:");
    u8g.drawStr(95, 40, bt.c_str());
    //
    u8g.drawHLine(__line_begin , 55, 5);
    u8g.drawStr(__text_begin , 55 , "About...");
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

void Screen:: setCoordniates(float c1 , float c2 , float c3) {
  x = c1;
  y = c2;
  z = c3;
}

void Screen :: sd_setSelection(int _row , int _column) {
  row = _row;
  column = _column;
}

void Screen:: _sd_setSelection(int row , int col) {
  int width = 10;
  int y = 19;
  switch (col) {
    case 1:
      u8g.drawHLine(54 , y + (row - 1) * 8 , width);
      break;
    case 2:
      u8g.drawHLine(118 , y + (row - 1) * 8 , width);
      break;
  }
}

String Screen:: _getFileName(int file_number) {
  String main = files_names;
  String files = files_names;
  String s1;
  for (int i = 0; i < file_number ; i++) {
    s1 = strtok (files.c_str(), ",");
    files_names.replace(s1 + "," , "\0");
    main = files_names;
  }
  return s1;
}


void Screen::sdFiles(String files_name, int file_number) {

  String s = "SD-Card Files";
  int w = u8g.getStrWidth(s.c_str());
  int middle = 64 - w / 2;
  u8g.firstPage();
  do {
    _sd_setSelection(row, column);
    u8g.setFontPosCenter();
    u8g.setFont(u8g_font_6x10);
    u8g.drawStr(25, 11, s.c_str());
    u8g.drawFrame(0, 0, 128, 64);
    u8g.drawHLine(22 , 14 , 83);
    u8g.drawVLine(64, 16, 45);
    //
    u8g.setFontPosBottom();
    u8g.setFont(u8g_font_04b_03);
    files_names = files_name;
    int x = 0;
    int y = 0;
    for (int i = 0 ; i <= file_number ; i++) {
      if (i >= 0 && i < 7) {
        String s1 = _getFileName(i);
        u8g.drawStr(4 , 22 + (x - 1) * 8 , s1.c_str());
        x++;
      } else if (i >= 7 && i < 13) {
        String s1 = _getFileName(i);
        u8g.drawStr(68 , 22 + (y) * 8 , s1.c_str());
        y++;
      }
    }
  } while ( u8g.nextPage() );
}

void Screen:: feedRate() {
  String s = "Feed Rate";
  int w = u8g.getStrWidth(s.c_str());
  int middle = 64 - w / 2;
  //
  String s1 = "-Max Feed Rate-";
  int w1 = u8g.getStrWidth(s1.c_str());
  int middle1 = 64 - w1 / 2;
  //
  String s2 = "300 mm/sec";
  int w2 = u8g.getStrWidth(s2.c_str());
  int middle2 = 64 - w2 / 2;
  //
  String s3 = "-Current Feed Rate-";
  int w3 = u8g.getStrWidth(s3.c_str());
  int middle3 = 64 - w3 / 2;
  //
  int w4 = u8g.getStrWidth(feed_rate.c_str());
  int middle4 = 64 - w4 / 2;

  u8g.firstPage();
  do {
    u8g.setFontPosCenter();
    u8g.setFont(u8g_font_6x10);
    u8g.drawFrame(0, 0, 128, 64);
    u8g.drawStr(middle, 9, s.c_str());
    u8g.drawHLine(middle - 3 , 14 , w + 4);

    u8g.drawStr(middle1 , 22 , s1.c_str());
    u8g.drawStr(middle2 , 32 , s2.c_str());
    u8g.drawFrame(middle2 - 5 , 25 , w2 + 7 , 11);

    u8g.drawStr(middle3 , 43 , s3.c_str());
    u8g.drawStr(middle4 , 53 , feed_rate.c_str());
    u8g.drawHLine(middle4 - 3 , 57 , w4 + 6);

  } while ( u8g.nextPage() );
}

void Screen :: spindleSettings() {
  String s = "Spindle Settings";
  int w = u8g.getStrWidth(s.c_str());
  int middle = 64 - w / 2;
  //
  String s1 = "Status:";
  String spindle = "";
  if (spindle_status) {
    spindle = "ON";
  } else {
    spindle = "OFF";
  }
  //
  String s2 = "Speed:";
  //
  String s3 = "Direction:";
  String sdirection;
  if (spindle_direction) {
    sdirection = "CCW";
  } else {
    sdirection = "CW";
  }
  //
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
    u8g.drawStr(__text_begin , 25 , s1.c_str());
    u8g.drawStr(95, 25, spindle.c_str() );
    //
    u8g.drawHLine(__line_begin , 40, 5);
    u8g.drawStr(__text_begin , 40 , s2.c_str());
    u8g.drawStr(95, 40, spindle_speed.c_str());
    //
    u8g.drawHLine(__line_begin , 55 , 5);
    u8g.drawStr(__text_begin , 55 , s3.c_str());
    u8g.drawStr(95, 55, sdirection.c_str());
    _drawSelectionBox(__selection);
  } while ( u8g.nextPage() );
}


void Screen :: about() {
  String s = "About";
  int w = u8g.getStrWidth(s.c_str());
  int middle = 64 - w / 2;
  String l1 = "-This controller is designed";
  String l2 = "for 3&5 axis cnc milling m/c.";
  String l3 = "made by: Mohamed Hassan.";
  String l4 = "-GitHub:MohamedHassan-coder";
  String l5 = "->3-Axis-CNC-Controller.git";
  u8g.firstPage();
  do {
    //    u8g.setFontLineSpacingFactor(2);
    u8g.setFontPosCenter();
    u8g.setFont(u8g_font_6x10);
    u8g.drawFrame(0, 0, 128, 64);
    u8g.drawStr(50, 11, "About");
    u8g.drawHLine(48 , 14 , w + 10);
    //
    u8g.setFont(u8g_font_04b_03);
    u8g.drawStr(0 , 22 , l1.c_str());
    u8g.drawStr(5 , 30 , l2.c_str());
    u8g.drawStr(5 , 38 , l3.c_str());
    u8g.drawStr(0 , 50, l4.c_str());
    u8g.drawStr(5 , 58 , l5.c_str());
  } while ( u8g.nextPage() );

}
void Screen :: grblSettings() {
  String s = "Grbl Settings";
  String symbol = "$";
  int w = u8g.getStrWidth(s.c_str());
  int middle = 64 - w / 2;
  u8g.firstPage();
  do {
    u8g.setFontPosCenter();
    u8g.setFont(u8g_font_6x10);
    u8g.drawFrame(0, 0, 128, 64);
    u8g.drawStr(middle, 9, s.c_str());
    u8g.drawHLine(middle - 3 , 14 , w + 4);
    //
    u8g.drawHLine(__line_begin , 25 , 5);
    u8g.drawStr(__text_begin , 25 , "Setttings Number: ");
    //
    u8g.drawHLine(__line_begin , 40 , 5);
    u8g.drawStr(__text_begin, 40 , symbol.c_str());
    u8g.drawStr(u8g.getStrWidth(symbol.c_str()) + 15 , 40 , grbl_settings.c_str());
    u8g.drawHLine(__text_begin , 45 , 12 + u8g.getStrWidth(grbl_settings.c_str()));
    u8g.drawXBMP( 59, 37, Arrow_width, Arrow_height, Arrow_bits);
    u8g.drawStr(85 , 40 , grbl_value.c_str());
    u8g.drawHLine(85 , 45 , u8g.getStrWidth(grbl_value.c_str()));

  } while ( u8g.nextPage() );
}

void Screen :: grblSettings_new(String value_name) {
  String s = "Grbl Settings";
  String symbol = "$";
  int w = u8g.getStrWidth(s.c_str());
  int middle = 64 - w / 2;
  u8g.firstPage();
  do {
    u8g.setFontPosCenter();
    u8g.setFont(u8g_font_6x10);
    u8g.drawFrame(0, 0, 128, 64);
    u8g.drawStr(middle, 9, s.c_str());
    u8g.drawHLine(middle - 3 , 14 , w + 4);
    //
    u8g.drawHLine(__line_begin , 25 , 5);
    u8g.drawStr(__text_begin , 25 , "Setttings Number: ");
    //
    u8g.drawHLine(__line_begin , 40 , 5);
    u8g.drawStr(__text_begin, 40 , symbol.c_str());
    u8g.drawStr(u8g.getStrWidth(symbol.c_str()) + 15 , 40 , value_name.c_str());
    u8g.drawHLine(__text_begin , 45 , 12 + u8g.getStrWidth(value_name.c_str()));
    u8g.drawXBMP( 59, 37, Arrow_width, Arrow_height, Arrow_bits);
    u8g.drawStr(85 , 40 , grbl_value.c_str());
    u8g.drawHLine(85 , 45 , u8g.getStrWidth(grbl_value.c_str()));

  } while ( u8g.nextPage() );
}

void Screen :: throwError(String error) {
  String s = "Error";
  int w = u8g.getStrWidth(s.c_str());
  int middle = 64 - w / 2;
  u8g.firstPage();
  do {
    u8g.setFontPosCenter();
    u8g.setFont(u8g_font_6x10);
    u8g.drawFrame(0, 0, 128, 64);
    u8g.drawStr(middle, 9, s.c_str());
    u8g.drawHLine(middle - 3 , 14 , w + 4);
    //
    u8g.drawHLine(__line_begin , 33, 5);
    u8g.drawStr(__text_begin , 33 , error.c_str());

  } while ( u8g.nextPage() );
  delay(1500);
}

void Screen:: initalizing(String text) {
  u8g.setFontPosCenter();
  u8g.setFont(u8g_font_5x8);
  u8g.firstPage();
  if (count > 4) {
    count = 1;
    text1 = "";
    text2 = "";
    text3 = "";
    text4 = "";
  }
  do {
    u8g.drawFrame(0, 0, 128, 64);
    switch (count) {
      case 1:
        text1 = text;
        u8g.drawHLine(__line_begin, 9 , 5);
        u8g.drawStr(__text_begin, 9, text1.c_str());
        break;
      case 2:
        text2 = text;
        u8g.drawHLine(__line_begin, 9 , 5);
        u8g.drawStr(__text_begin, 9, text1.c_str());
        u8g.drawHLine(__line_begin, 25 , 5);
        u8g.drawStr(__text_begin, 25, text2.c_str());
        break;
      case 3:
        text3 = text;
        u8g.drawHLine(__line_begin, 9 , 5);
        u8g.drawStr(__text_begin, 9, text1.c_str());
        u8g.drawHLine(__line_begin, 25 , 5);
        u8g.drawStr(__text_begin, 25, text2.c_str());
        u8g.drawHLine(__line_begin, 40 , 5);
        u8g.drawStr(__text_begin, 40, text3.c_str());
        break;
      case 4:
        text4 = text;
        u8g.drawHLine(__line_begin, 9 , 5);
        u8g.drawStr(__text_begin, 9, text1.c_str());
        u8g.drawHLine(__line_begin, 25 , 5);
        u8g.drawStr(__text_begin, 25, text2.c_str());
        u8g.drawHLine(__line_begin, 40 , 5);
        u8g.drawStr(__text_begin, 40, text3.c_str());
        u8g.drawHLine(__line_begin, 55 , 5);
        u8g.drawStr(__text_begin, 55, text4.c_str());
        break;
    }

  } while ( u8g.nextPage() );
  count++;
  delay(500);
}
