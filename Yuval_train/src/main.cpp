#include <Arduino.h>
#include <Wire.h>  // for I2c
#include "PCF8574.h"
#include <generalFunc.h>
//#include <i2c.h>
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
#define button_start_pin   35
#define button_stop_pin   17 // was 36
#define button_cng_dir_pin 34
#define speed_potsmtr_pin   12 //  26  //39 // was  33

//#define I2C_interrupt_pin 13

const int freq = 5000;
const int resolution = 8;
const int ledChannel0 = 0; // was 0


Train_ctrl my_train;
//I2C_ctrl my_i2c_bus;
int train_speed;

TaskHandle_t Task1; // create a task to run on core 0 - the analog read

//uint8_t button_val;
volatile bool start_pressed = false;
volatile bool stop_pressed = false;
volatile bool cng_pressed = false;
int num_start_pressed = 0;
int num_end_pressed = 0;

 void IRAM_ATTR Button_start_isr() {
  detachInterrupt(button_start_pin);
  start_pressed = true;
} // end of ISR

void IRAM_ATTR Button_stop_isr() {
  detachInterrupt(button_stop_pin);
  stop_pressed = true;
} // end of ISR

void IRAM_ATTR Button_cng_isr() {
  detachInterrupt(button_cng_dir_pin);
  cng_pressed = true;
} // end of ISR


void Task1code( void * parameter) {
  int val;
  for(;;) {
    //val = analogRead(speed_potsmtr_pin);
    val = my_train.manual_speed_knob.read_speed();
    my_train.speed_knob_val = val ; // keep reading speed from the knob
    
    Serial.println(" ");
    Serial.print("pin:  ");
    Serial.print(speed_potsmtr_pin);
    Serial.print("   Core:  ");
    Serial.println(xPortGetCoreID());
    /*
    Serial.print("    ****   analog read:  ");
    Serial.print(val);
    Serial.print("      ..   ");
    val = analogRead(speed_potsmtr_pin);
    Serial.print(val);
    Serial.print("    speed:    ");
    train_speed = analogRead(speed_potsmtr_pin);
    Serial.println(train_speed);
    Serial.print("    /  ");
    Serial.println(my_train.speed_knob_val);
    */
    wait_millis(100);
  } // of for() loop
} // of Task1code






void setup() {
  Serial.begin(9600);
  Wire.begin(); // init I2C bus as a master 
  Serial.println("..starting SETUP....");
  Serial.println(xPortGetCoreID());
      
  my_train.Red_led.led_pin = red_led_pin;
  my_train.Yellow_led.led_pin = yellow_led_pin;
  my_train.Green_led.led_pin = green_led_pin;
  my_train.Red_led.init_led();
  my_train.Yellow_led.init_led();
  my_train.Green_led.init_led();

  my_train.manual_speed_knob.potsmtr_pin = speed_potsmtr_pin;

  my_train.start_button.button_pin = button_start_pin;
  my_train.stop_button.button_pin = button_stop_pin;
  my_train.cng_button.button_pin = button_cng_dir_pin;
  my_train.start_button.init();
  my_train.stop_button.init();
  my_train.cng_button.init();

  


  //my_train.test_leds();
  
  // Leds ON for a short time
  my_train.Red_led.set_led_on(); 
  my_train.Green_led.set_led_on();
  my_train.Yellow_led.set_led_on();

  //Serial.print(millis());
  wait_millis(1000);
  //Serial.print("  ");
  //Serial.println(millis());
  //delay(4000);

  //my_train.buzz._buz_pin = buzzer_pin;
  //my_train.buzz.init_buzzer();

  my_train.motor.init(m1_en_pin,m1_in1_pin,m1_in2_pin,freq,resolution,ledChannel0);
  
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

// the task to be run on core 0 - the analog read
xTaskCreatePinnedToCore(
      Task1code, /* Function to implement the task */
      "Task1", /* Name of the task */
      10000,  /* Stack size in words */
      NULL,  /* Task input parameter */
      0,  /* Priority of the task */
      &Task1,  /* Task handle. */
      0); /* Core where the task should run */





   
  my_train.led_ctrl(RED); // train is at stop at start
  wait_millis(1000); // for debug stage ONLY

  attachInterrupt(digitalPinToInterrupt(button_start_pin), Button_start_isr, RISING);
  attachInterrupt(digitalPinToInterrupt(button_stop_pin), Button_stop_isr, RISING);
  attachInterrupt(digitalPinToInterrupt(button_cng_dir_pin), Button_cng_isr, RISING);

  Serial.println("..End of SETUP");
} // of SETUP()  ******************************************


void handle_buttons(); // the function is declared at the bottom after the loop

void loop() {
  //return;
  
  
  Serial.println("   ");
  Serial.print("  core:  ");
  Serial.print(xPortGetCoreID());
  
  //my_train.speed_knob_val = my_train.manual_speed_knob.read_speed(); // keep reading speed from the knob
  //my_train.update_speed();
  Serial.print("   my train speed val:  ");
  Serial.print(my_train.speed_knob_val);
  Serial.print("  my train pin num:  ");
  Serial.print(my_train.manual_speed_knob.potsmtr_pin);
  Serial.print("     ");
  //return;
  

  if (start_pressed || stop_pressed || cng_pressed) {
    // Push buttpn event occured
    Serial.print(" Push Button event occured ");
    Serial.print(start_pressed);
    Serial.print("   ");
    Serial.print(stop_pressed);
    Serial.print("   ");
    Serial.print(cng_pressed);
    Serial.print("   ");
    handle_buttons();
    
  }

  // make sure train runs on speed according to the knob



  /*
  Serial.print(start_pressed);
  Serial.print("   ");
  Serial.print(stop_pressed);
  Serial.print("   ");
  Serial.print(cng_pressed);
  Serial.print("  /  ");
  Serial.print(my_train.start_button.pressed_num);
  Serial.print("   ");
  Serial.print(my_train.stop_button.pressed_num);
  Serial.print("   ");
  Serial.print(my_train.cng_button.pressed_num);
  Serial.print("       status:  ");
  Serial.print(my_train.motor.status);
  Serial.print("   dir: ");
  Serial.print(my_train.motor.dir);
  Serial.print("   ");
  */

wait_millis(50);      
} // of LOOP()   ******************************************





void handle_buttons() {


    if (start_pressed) {
      Serial.print("   in START_pressed   ");

      start_pressed = false;
      // if we are already in movement, do nothing
      if (my_train.motor.status==GO) {
        Serial.print("   ");
        //Serial.print("in START, GO");
        wait_millis(100);
        attachInterrupt(digitalPinToInterrupt(button_start_pin), Button_start_isr, RISING);
        return;
      } // of inner if()

      Serial.print("in START, was no-go");
      // At this stage, we got a valid go command
      my_train.start_button.pressed_num +=1;
      my_train.motor.status = GO;
    
      // go, depends on the direction
      if (my_train.motor.dir==GO_FWD) {
        my_train.motor.go_fwd(my_train.speed_knob_val);
        my_train.led_ctrl(GREEN);
      } // of if()
      else {
        my_train.motor.go_back(my_train.speed_knob_val);
        my_train.led_ctrl(YELLOW);
      } // of else()
    wait_millis(100);
    attachInterrupt(digitalPinToInterrupt(button_start_pin), Button_start_isr, RISING);
  } // of if() start_pressed
  
  
  if (stop_pressed) {
    // no need to check if we are already in stop mode,,,, just stopping again..
    // TBD: moderated stop
    Serial.print("    in STOP_PRESSED    ");
    stop_pressed = false;
    my_train.stop_button.pressed_num +=1;
        
    my_train.motor.stop();
    my_train.motor.status = STOP;
    my_train.led_ctrl(RED);
    wait_millis(100);
    attachInterrupt(digitalPinToInterrupt(button_stop_pin), Button_stop_isr, RISING);   
  } // of if() stopped pressed

  if (cng_pressed) {
    cng_pressed = false;
    my_train.cng_button.pressed_num +=1;
    
    if (my_train.motor.status == STOP) {
      // We are in stop mode
      //just change future direction
      if (my_train.motor.dir==GO_FWD) {
       my_train.motor.dir = GO_BCK;
      }
      else {
        my_train.motor.dir = GO_FWD;
      }
    } // of if()
    else {
      // we are already on the go
      // Need to stop and change direction
      //Serial.print("  in ELSE ");
      my_train.motor.stop();
      my_train.led_ctrl(RED);
      wait_millis(1000);
      if (my_train.motor.dir==GO_FWD) {
        my_train.motor.dir = GO_BCK;
        my_train.motor.go_back(my_train.speed_knob_val);
        my_train.led_ctrl(YELLOW);
      } // of IF()
      else {
        my_train.motor.dir = GO_FWD;
        my_train.motor.go_fwd(my_train.speed_knob_val);
        my_train.led_ctrl(GREEN);
      } // of ELSE()
      wait_millis(100);
    } // of else()

    wait_millis(300); // larger delay to debounce - delay between changes
    attachInterrupt(digitalPinToInterrupt(button_cng_dir_pin), Button_cng_isr, RISING);   
  } // of if() cng_pressed

} // of handle_buttons