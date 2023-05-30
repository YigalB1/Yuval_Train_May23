#include <Arduino.h>
#include <Wire.h>  // for I2c
#include <Motors.h>
#include "PCF8574.h"

#include <headers.h>
#include <i2c.h>




#define red_led_pin 15
#define yellow_led_pin 2
#define green_led_pin 12
#define buzzer_pin 25
#define m1_en 32
#define m1_in1 33
#define m1_in2 26
#define m2_en 27
#define m2_in1 14
#define m2_in2 13
#define temperature_pin = 36
const int freq = 5000;
const int resolution = 8;
const int ledChannel0 = 0;


Train_ctrl my_train;
I2C_panel_ctrl my_panel;




void setup() {
  Serial.begin(9600);
  Wire.begin(); // I2C
  Serial.print("..starting SETUP");
  
  
  
  my_train.Red_led.led_pin = red_led_pin;
  my_train.Yellow_led.led_pin = yellow_led_pin;
  my_train.Green_led.led_pin = green_led_pin;
  my_train.Red_led.init_led();
  my_train.Yellow_led.init_led();
  my_train.Green_led.init_led();
  
  my_train.buzz._buz_pin = buzzer_pin;
  my_train.buzz.init_buzzer();
  my_train.motor.init(m1_en,m1_in1,m1_in2,freq,resolution,ledChannel0);
  
  Serial.print("..End of SETUP");

  my_panel.i2c_init();
  my_panel.test_panel_leds();
  my_panel.I2C_scanner();

   
} // of SETUP() 

void loop() {


 
  
  uint8_t val2 = i2c_panel.digitalRead(P2);
  Serial.print(val2);
  wait_millis(20);
  return;

  
  int sw_tmp = my_panel.read_i2c(push_button1);
  Serial.print(sw_tmp);
  wait_millis(20);

  
  return;
  
  //my_train.test_leds();
  //I2C_scanner();
  //send the data
  
  
  my_train.motor.motor_test();
  return;


  //my_train.Red_led.set_led_on();
  digitalWrite(red_led_pin,HIGH);
  digitalWrite(m1_in1,LOW);
  digitalWrite(m1_in2,LOW);
  wait_millis(2000);
  //my_train.Red_led.set_led_off();
  //my_train.Green_led.set_led_on();
  digitalWrite(red_led_pin,LOW);
  digitalWrite(green_led_pin,HIGH);
  digitalWrite(m1_in1,HIGH);
  digitalWrite(m1_in2,HIGH);
  wait_millis(2000);
  //my_train.Green_led.set_led_off();
  digitalWrite(green_led_pin,LOW);
  return;



  
} // of LOOP()