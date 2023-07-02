#include <Servo.h>

#define RED     1 
#define YELLOW  2
#define GREEN   3


class Led {
    public:
    int led_pin;
    
    void init_led() { 
      pinMode(led_pin, OUTPUT);
    }
    void set_led_on() {
        digitalWrite(led_pin,HIGH);
    }
    void set_led_off() {
        digitalWrite(led_pin,LOW);
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


void wait_millis(unsigned long _period_ms) {
  unsigned long time_now = millis();
  while(millis() < time_now+_period_ms);
} // of wait_millis


class US_sensor {
    public:
    int trigPin;
    int echoPin;
    int dist=777;
    
    void init_US_sensor() {
    //Serial.print("trig: ");
    //Serial.println(trigPin);
    //Serial.print("echo: ");
    //Serial.println(echoPin);
      pinMode(trigPin, OUTPUT);
      pinMode(echoPin, INPUT);
    } // of init_US_sensor()

    void read_US_sensor() {           
      // Clears the trigPin condition
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10); // was 10. should be 50??
      digitalWrite(trigPin, LOW);
      int duration = pulseIn(echoPin, HIGH,2350000UL); // for 40 cm max
      dist = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
      Serial.print("In reading, dist: ");
      Serial.println(dist);
  } // of read_US_sensor() 
}; // of class US_sensor

class sensor_client {
  public:
  US_sensor dist_sensor;
  Led Red_led;
  Led Green_led;
  Led Yellow_led;
  Servo radar_servo;

  void init_servo(int _pin) {
    radar_servo.attach(_pin);
  } // of init_servo

  void test_servo() {
    int step = 300;
    int inc = 20;
    for (int i=0;i<=180;i+=inc) {
    //Serial.print( "in servo UP, i = : ");
    //Serial.println(i);
      radar_servo.write(i);
      delay(step);
      //wait_millis(step);
    } // of for 

    for (int i=180;i>=0;i-=inc) {
    //Serial.print( "in servo DOWN, i = : ");
    //Serial.println(i);
      radar_servo.write(i);
      delay(step);
      //wait_millis(step);
    } // of for 

  } // of test_servo()


  void test_leds() {
    // test leds
    for (int i=0;i<5;i++) {
      Serial.println(i);
      Red_led.set_led_on();
      Yellow_led.set_led_on();
      Green_led.set_led_on();
      wait_millis(500);
      
      Red_led.set_led_off();
      Yellow_led.set_led_off();
      Green_led.set_led_off();
      wait_millis(500);
    } // of for loop - testing leds
  } // of test_leds()

  void test_us_sensor() {
    dist_sensor.read_US_sensor();
    int l_dist = dist_sensor.dist;
    Serial.print( "l_dist: ");
    Serial.println(l_dist);
    wait_millis(400);

  } // of test_us_sensor

}; // of sensor_client