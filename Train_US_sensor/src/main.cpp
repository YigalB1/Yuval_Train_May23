#include <Arduino.h>
#include <headers.h>

// dor sensor PCB 
#define red_led_pin 12 //D6 // was 12
#define yellow_led_pin 13 //D7
#define green_led_pin 15 // D8 
#define trig_pin 5 //D1
#define echo_pin 4 // D2
#define servo_pin 14

sensor_client sensor_client_1;

void setup() {
  Serial.begin(9600);
  Serial.print("");
  Serial.println("starting SETUP ....");
  //pinMode(red_led_pin, OUTPUT);
  
  sensor_client_1.dist_sensor.trigPin = trig_pin;
  sensor_client_1.dist_sensor.echoPin = echo_pin;
  sensor_client_1.dist_sensor.init_US_sensor();

  sensor_client_1.Red_led.led_pin = red_led_pin;
  sensor_client_1.Red_led.init_led();
  sensor_client_1.Yellow_led.led_pin = yellow_led_pin;
  sensor_client_1.Yellow_led.init_led();
  sensor_client_1.Green_led.led_pin = green_led_pin;
  sensor_client_1.Green_led.init_led();

  sensor_client_1.init_servo(servo_pin);

  sensor_client_1.test_leds();

  Serial.println("Finished Setup");
} // of SETUP


void loop() {
 //sensor_client_1.test_us_sensor();
 sensor_client_1.test_servo();
 wait_millis(500);
  
} // of LOOP

