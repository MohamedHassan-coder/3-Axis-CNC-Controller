# include "Arduino.h"
class Push_Button {
  public:
    Push_Button(int button_pin , int buzzer_pin);
    bool get_current_status();
    bool get_last_status();

  private:
    int _button_pin , _buzzer_pin;
    bool _current_status = LOW;
    bool _last_status = LOW;
    void __button_pressed();

};

Push_Button::Push_Button(int button_pin , int buzzer_pin) {
  _button_pin = button_pin;
  _buzzer_pin = buzzer_pin;
  pinMode(buzzer_pin, OUTPUT);
  pinMode(_button_pin , INPUT_PULLUP);
}

void Push_Button:: __button_pressed() {
  _current_status = digitalRead(_button_pin);
  if (_last_status != _current_status)
  {
    delay(10);
    _current_status = digitalRead(_button_pin);
    digitalWrite(_buzzer_pin, HIGH);
    delay(5);
    digitalWrite(_buzzer_pin, LOW);
  }
}

bool Push_Button:: get_current_status() {
  __button_pressed();
  _last_status = _current_status;

  return _current_status;
    millis();
    delay(50);
  return LOW;
}

bool Push_Button:: get_last_status() {
  __button_pressed();
  _last_status = _current_status;

  return _last_status;
}
