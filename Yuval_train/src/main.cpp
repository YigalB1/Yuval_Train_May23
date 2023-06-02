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

#define temperature_pin 36
#define I2C_int 13

const int freq = 5000;
const int resolution = 8;
const int ledChannel0 = 0;


Train_ctrl my_train;
I2C_ctrl my_i2c_bus;

uint8_t p2_val;
volatile bool pressed = false;
int num_pressed = 0;

 void IRAM_ATTR pushB_isr() {
  detachInterrupt(I2C_int);
  pressed = true;
} // end of ISR


void setup() {
  Serial.begin(9600);
  Wire.begin(); // init I2C bus as a master 
  
  Serial.println("..starting SETUP....");
  

 
  
  /*
  my_train.Red_led.led_pin = red_led_pin;
  my_train.Yellow_led.led_pin = yellow_led_pin;
  my_train.Green_led.led_pin = green_led_pin;
  my_train.Red_led.init_led();
  my_train.Yellow_led.init_led();
  my_train.Green_led.init_led();
  
  my_train.buzz._buz_pin = buzzer_pin;
  my_train.buzz.init_buzzer();

  */
  //my_train.motor.init(m1_en,m1_in1,m1_in2,freq,resolution,ledChannel0);
  
 my_i2c_bus.I2C_scanner();
  bool ret_val = my_i2c_bus.i2c_init();
  Serial.print("ret_val: ");
  Serial.println(ret_val);
  if (!ret_val)
    {
      Serial.println("Failed to init my_panel ");
      while (true){};
    }// of if
  //my_panel.test_panel_leds();
  my_i2c_bus.I2C_scanner();
  // Check if an I2C device exists at address 0x42
if (Wire.begin(0x39)) {
   Serial.println("I2C 0x39 exists");
   my_train.Green_led.set_led_on();
   my_train.Red_led.set_led_off();   
} 
else {
   Serial.println("I2C 0x39 is missing");
   my_train.Green_led.set_led_off();
   my_train.Red_led.set_led_on(); 
}
  
  
 
  p2_val = i2c_panel.digitalRead(P2);
  Serial.print("p2 value: ");
  Serial.println(p2_val);
 
  pinMode(I2C_int, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(I2C_int), pushB_isr, RISING);

  Serial.println("..End of SETUP");
} // of SETUP()  ******************************************

int sum_0 = 0;
int sum_1 = 0;

void loop() {

  if (pressed) {
    detachInterrupt(I2C_int);

    p2_val = i2c_panel.digitalRead(P2);
    if (p2_val==0) {
      num_pressed+=1;     
    }
  }
  pressed = false;

  Serial.print("p2_val: ");  
  Serial.print(p2_val);

  Serial.print("     num_pressed: ");  
  Serial.println(num_pressed);
    
  attachInterrupt(digitalPinToInterrupt(I2C_int), pushB_isr, RISING);
  return;





  
} // of LOOP()   ******************************************