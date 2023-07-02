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


void wait_millis(int _period_ms) {
  unsigned long time_now = millis();
  while(millis() < time_now+_period_ms);
} // of wait_millis


class US_sensor {
    public:
    int trigPin;
    int echoPin;
    int dist;
    
    void init_US_sensor() {
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
  } // of read_US_sensor() 
}; // of class US_sensor

class sensor_client {
  public:
  US_sensor dist_sensor;
    Led Red_led;
    Led Green_led;
    Led Yellow_led;

}; // of sensor_client