#include <Arduino.h>
#include <Wire.h>  // for I2c
#include "PCF8574.h"
#include <generalFunc.h>
#include <i2c.h>
#include <Motors.h>
#include <headers.h>



// 2 June 2023: moving from PCB Yuval Train (#8) to Train_CTRL (#6)


#define red_led_pin 15
#define yellow_led_pin 2
#define green_led_pin 16 // in pcb1 was 12
//#define buzzer_pin 25
#define m1_en_pin 22 // was 22 in layout pcb2, 13 for testing
#define m1_in1_pin 23
#define m1_in2_pin 4
#define button_start_pin  35
#define button_stop_pin    34
#define button_cng_dir_pin    34


#define temperature_pin 36
//#define I2C_interrupt_pin 13

const int freq = 5000;
const int resolution = 8;
const int ledChannel0 = 0;


Train_ctrl my_train;
I2C_ctrl my_i2c_bus;

//uint8_t button_val;
volatile bool start_pressed = false;
volatile bool end_pressed = false;
int num_start_pressed = 0;
int num_end_pressed = 0;

 void IRAM_ATTR Button_start_isr() {
  detachInterrupt(button_start_pin);
  start_pressed = true;
} // end of ISR

void IRAM_ATTR Button_stop_isr() {
  detachInterrupt(button_stop_pin);
  end_pressed = true;
} // end of ISR


void setup() {
  Serial.begin(9600);
  Wire.begin(); // init I2C bus as a master 
  Serial.println("..starting SETUP....");
      
  my_train.Red_led.led_pin = red_led_pin;
  my_train.Yellow_led.led_pin = yellow_led_pin;
  my_train.Green_led.led_pin = green_led_pin;
  my_train.Red_led.init_led();
  my_train.Yellow_led.init_led();
  my_train.Green_led.init_led();

  //my_train.test_leds();
  
  // RED red led on 
  my_train.Red_led.set_led_on(); 
  my_train.Green_led.set_led_off();
  my_train.Yellow_led.set_led_off();

  

  //my_train.buzz._buz_pin = buzzer_pin;
  //my_train.buzz.init_buzzer();

  my_train.motor.init(m1_en_pin,m1_in1_pin,m1_in2_pin,freq,resolution,ledChannel0);
  /// TESTING ONLY temporary
  //Serial.println("Testing motors");
  //while (true) my_train.motor.motor_test();
  //Serial.println("..starting SETUP....3");
  
  // scan I2C - for debug phases
  //my_i2c_bus.I2C_scanner();

    
/*
if (Wire.begin(0x39)) {
   Serial.println("I2C 0x39 exists");
} 
else {
   Serial.println("I2C 0x39 is missing");
}
*/  
  
 
   
  pinMode(button_start_pin, INPUT_PULLUP);
  pinMode(button_stop_pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(button_start_pin), Button_start_isr, RISING);
  attachInterrupt(digitalPinToInterrupt(button_stop_pin), Button_stop_isr, RISING);

  Serial.println("..End of SETUP");
} // of SETUP()  ******************************************

int sum_0 = 0;
int sum_1 = 0;

void loop() {

  if (start_pressed) {
    //detachInterrupt(button_start_pin);

      num_start_pressed+=1;     

    start_pressed = false;
    wait_millis(100);
    attachInterrupt(digitalPinToInterrupt(button_start_pin), Button_start_isr, RISING);
  }
  
  if (end_pressed) {
    //detachInterrupt(button_end_pin);
      num_end_pressed+=1;     

    end_pressed = false;
    wait_millis(100);
    attachInterrupt(digitalPinToInterrupt(button_stop_pin), Button_stop_isr, RISING);
  }
  
  Serial.print("Start/end num_pressed: ");  
  Serial.print(num_start_pressed);
  Serial.print(" / ");  
  Serial.println(num_end_pressed);
      
} // of LOOP()   ******************************************