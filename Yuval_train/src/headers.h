class Led {
    public:
    int led_pin;
    
    void init_led() { 
      pinMode(led_pin, OUTPUT);
      //Serial.print("init_led: ");
      //Serial.println(led_pin);
    }
    void set_led_on() {
        digitalWrite(led_pin,HIGH);
        //Serial.print("Led ON : ");
        //Serial.println(led_pin);
    }
    void set_led_off() {
        digitalWrite(led_pin,LOW);
        //Serial.print("Led OFF : ");
        //Serial.println(led_pin);
    }
}; // of class led

class buzzer {
    public:
    int _buz_pin;

    void init_buzzer() { 
      pinMode(_buz_pin, OUTPUT);
      //Serial.print("init_led: ");
      //Serial.println(led_pin);
    }

    void set_buzzer_on() {
        digitalWrite(_buz_pin,HIGH);
    }
    void set_buzzer_off() {
        digitalWrite(_buz_pin,LOW);
    }
};

class push_button {
  int button_pin;
  int pressed_num = 0 ; // mostly for debug

  void init() {
    pinMode(button_pin, INPUT_PULLUP);
  } // of init()

}; // of push_button class


class Train_ctrl {
  public:
    Led Green_led;
    Led Red_led;
    Led Yellow_led;
    buzzer buzz;
    motor_control motor;

    push_button start_button;
    push_button stop_button;
    push_button cng_button;


    // for the ESP32 PWM
    const int freq = 5000;
    const int ledChannel0 = 0;
    const int ledChannel2 = 2;
    const int resolution = 8;

    bool dir_left = true;

    

    void test_leds() {
      int blink_delay = 500;
      for (int i=0;i<5;i++) {
        Red_led.set_led_off();
        Yellow_led.set_led_on();
        Green_led.set_led_off();
        
        wait_millis(blink_delay);
        Red_led.set_led_on();
        Yellow_led.set_led_off();
        Green_led.set_led_on();
        
        wait_millis(blink_delay);
      } // of for loop
    } // of test_leds()

}; // of Train_ctrl Class