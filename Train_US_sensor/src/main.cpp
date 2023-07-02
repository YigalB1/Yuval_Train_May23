#include <Arduino.h>
#include <headers.h>

// dor sensor PCB 
#define red_led_pin 6
#define yellow_led_pin 7
#define green_led_pin 8 
#define trig_pin 1 
#define echo_pin 2

sensor_client sensor_client_1;

void setup() {
  Serial.begin(9600);
  Serial.print("");
  Serial.print("starting SETUP ....");
  
  sensor_client_1.dist_sensor.trigPin = trig_pin;
  sensor_client_1.dist_sensor.echoPin = echo_pin;
  sensor_client_1.dist_sensor.init_US_sensor();

  sensor_client_1.Red_led.led_pin = red_led_pin;
  sensor_client_1.Red_led.init_led();
  sensor_client_1.Yellow_led.led_pin = yellow_led_pin;
  sensor_client_1.Yellow_led.init_led();
  sensor_client_1.Green_led.led_pin = green_led_pin;
  sensor_client_1.Green_led.init_led();


  // test leds
  for (int i=0;i<5;i++) {
    sensor_client_1.Red_led.set_led_on();
    //sensor_client_1.Yellow_led.set_led_on();
    //sensor_client_1.Green_led.set_led_on();
    wait_millis(500);
    sensor_client_1.Red_led.set_led_off();
    //sensor_client_1.Yellow_led.set_led_off();
    //sensor_client_1.Green_led.set_led_off();
    wait_millis(500);

  }

  Serial.println("Finished Setup");
}

void loop() {
  sensor_client_1.dist_sensor.read_US_sensor();
  int l_dist = sensor_client_1.dist_sensor.dist;
  Serial.print( "l_dist: ");
  Serial.println(l_dist);
  wait_millis(100);

  // put your main code here, to run repeatedly:
}

