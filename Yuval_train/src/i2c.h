PCF8574 i2c_panel(0x39);


class I2C_panel_ctrl {
    #define led_red 4
    #define led_yellow 5
    #define led_green 6
    #define push_button1 2
  
  

public:
    
    void i2c_init() {
        i2c_panel.pinMode(led_red, OUTPUT);
        i2c_panel.pinMode(led_yellow, OUTPUT);
        i2c_panel.pinMode(led_green, OUTPUT);
        i2c_panel.pinMode(push_button1, INPUT);
        if (i2c_panel.begin()) 
            Serial.println("OK");
        else
            Serial.println("KO");

    } // of i2c_init

    void write_i2c(int _pin, int _val) {
      i2c_panel.digitalWrite(_pin, _val );
    } // of write_i2c

    int read_i2c(int _pin) {
        return(i2c_panel.digitalRead(_pin));
    } // of read_i2c




    /*
      if (!PCF_39.begin())
  {
    Serial.println("could not initialize...");
  }
  if (!PCF_39.isConnected())
  {
    Serial.println("=> not connected");
  }
  else
  {
    Serial.println("=> connected!!");
  }
}*/

void test_panel_leds() {
    write_i2c(led_red,LOW);
    write_i2c(led_yellow,HIGH);
    write_i2c(led_green,HIGH);
    wait_millis(1000);

    write_i2c(led_red,HIGH);
    write_i2c(led_yellow,LOW);
    write_i2c(led_green,HIGH);
    wait_millis(1000);

    write_i2c(led_red,HIGH);
    write_i2c(led_yellow,HIGH);
    write_i2c(led_green,LOW);
    wait_millis(1000);

    write_i2c(led_red,LOW);
    write_i2c(led_yellow,LOW);
    write_i2c(led_green,LOW);
    wait_millis(500);




} // of panel_leds




    void I2C_scanner() {
      byte error, address;
      int nDevices;

      nDevices = 0;
      Serial.println("Scanning...");   /*ESP32 starts scanning available I2C devices*/
      for(address = 1; address < 127; address++ ) {   /*for loop to check number of devices on 127 address*/
        Wire.beginTransmission(address);
        error = Wire.endTransmission();
        if (error == 0) {   /*if I2C device found*/
          Serial.print("I2C device found at address 0x");/*print this line if I2C device found*/
          if (address<16) {
            Serial.print("0");
          } // of if()
          Serial.println(address,HEX);  /*prints the HEX value of I2C address*/
          nDevices++;
        } // of if()
        else if (error==4) {
          Serial.print("Unknown error at address 0x");
          if (address<16) {
            Serial.print("0");
          } // of if()
          Serial.println(address,HEX);
        }    // of else if()
      } // of for loop
    if (nDevices == 0) {
      Serial.println("No I2C devices found\n"); /*If no I2C device attached print this message*/
    } // of if()
    else {
      Serial.println("done\n");
    } // of else()
    delay(5000);   /*Delay given for checking I2C bus every 5 sec*/
    } // of I2C_scanner
 
  }; // of I2C_ctrl

 
  
