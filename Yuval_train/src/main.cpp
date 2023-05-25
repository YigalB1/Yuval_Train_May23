#include <Arduino.h>
#include <headers.h>

Train_ctrl my_train;

void setup() {
  my_train.Red_led.led_pin = red_led_pin;
  my_train.Yellow_led.led_pin = yellow_led_pin;
  my_train.Green_led.led_pin = green_led_pin;
  my_train.Red_led.init_led();
  my_train.Yellow_led.init_led();
  my_train.Green_led.init_led();
  
} // of SETUP() 

void loop() {
  my_train.test_leds();
} // of LOOP()