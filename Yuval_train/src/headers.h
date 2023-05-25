

#define red_led_pin 15
#define yellow_led_pin 2
#define green_led_pin 12

void wait_millis(int _period_ms) {
  unsigned long time_now = millis();
  //Serial.print(" # "); 
  //Serial.print(time_now); 
  //Serial.print(" # "); 
  //Serial.print(_period_ms); 
  //Serial.print("#"); 

  while(millis() < time_now+_period_ms);
  //Serial.print(millis()); 
  //Serial.println("#"); 
} // of wait_millis




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


class Train_ctrl {
  public:
    Led Green_led;
    Led Red_led;
    Led Yellow_led;


// -------------------------------------------------


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