#define I2C_Panel_addr 0x39 // the small pcb with the touch buttons and leds
#define I2C_Main_addr 0x38 // the main pcb withthe ESP32 and motor drivers



PCF8574 i2c_panel(0x39); // is 57 decimal
PCF8574 i2c_main(0x38); // is 56 decimal


class I2C_ctrl {
    #define led_red 4
    #define led_yellow 5
    #define led_green 6
    #define push_button1 2 

  public:
      
  bool i2c_init() {
    Serial.print("in i2c_init()   ");
    // check OCF8574 of Yuval_Panel 
    bool i2c_panel_ret;
    bool i2c_main_ret;

    i2c_panel_ret = check_i2c_alive(I2C_Panel_addr);
    if (!i2c_panel_ret) {
      // device is dead
      Serial.print("Adress: ");
      Serial.print(I2C_Panel_addr);
      Serial.println("    failed to init");
      return(false);
    } // of if()

    i2c_main_ret = check_i2c_alive(I2C_Main_addr);
    if (!i2c_main_ret) {
      // device is dead
      Serial.print("Adress: ");
      Serial.print(I2C_Main_addr);
      Serial.println("    failed to init");
      return(false);
    } // of if()
    
    // init the pins of the PCF8574
      i2c_panel.pinMode(led_red, OUTPUT);
      i2c_panel.pinMode(led_yellow, OUTPUT);
      i2c_panel.pinMode(led_green, OUTPUT);
      i2c_panel.pinMode(push_button1, INPUT);

      //i2c_main.pinMode(m1_in1,OUTPUT); with change from PCB1 to 2
      //i2c_main.pinMode(m1_in2,OUTPUT);
      //i2c_main.pinMode(m2_in1,OUTPUT);
      //i2c_main.pinMode(m2_in2,OUTPUT);

    return(true);
  } // of i2c_init



bool check_i2c_alive(int _addr) {
    int ret_val;

    Wire.beginTransmission(I2C_Panel_addr);
    ret_val = Wire.endTransmission();
    Serial.print("ret_val: ");
    Serial.println(ret_val);

    if (ret_val!=0) {
      // failed to communicate with the i2c device
      Serial.println("ERROR: Panel PCF8574 is Dead");
      return(false);
      } // of if()
    else {
      Serial.print("Panel PCF8574 is OK at adress: ");
      Serial.println(I2C_Panel_addr);
      
      } // of else()
    return(true);
  } // of check_i2c_alive

  

  void write_i2c(int _pin, int _val) {
    i2c_panel.digitalWrite(_pin, _val );
  } // of write_i2c

    int read_i2c(int _pin) {
        return(i2c_panel.digitalRead(_pin));
    } // of read_i2c

  

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

 
  
