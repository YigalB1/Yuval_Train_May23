$fn=90;
use <Train_ctrl_pcb.scad>
use <screw_holder.scad>


box_x = 90;
box_y = 90;
box_h = 40+20; // working currently 40
box_width = 2;
corner_x = 8;
pcb_vec = [-34,-38,-20];

header1 = "Train Control";

// location of switches & leds
led_h1 = 15;
led_h2 = -5-3;
led_cover_d=5+0.6;// was 11.8, before  12.5;
sw_d = 6.8+0.6;
sw1_vec =  [-30,led_h1,-5];
sw2_vec =  [-5 ,led_h1,-5];
sw3_vec =  [ 20,led_h1,-5];
        
led1_vec = [-30,led_h2,-5];
led2_vec = [-5 ,led_h2,-5];
led3_vec = [ 20,led_h2,-5];


// 1: the box to print
// 2: Cover
// 3: Leds holder
// 4: the box withthe internal
//to_print = 2 ;
//test();
//games();

//corner(ext_pins="false");



print_box(_param=1);
text_vec=[-30,-10,0];


module print_box(_param) {
    if (_param==1) {
        difference() {
            union() {
                box_to_print(_inner="false",ext_pins="false"); 
                // the pillars for the pcb
                translate(pcb_vec) train_ctrl_pcb(); 
            } // of union()
            translate(pcb_vec) mk_holes();
            
            // usb C hole: 14.7,5.2
            translate([30,25,17]) cube([30,14.7,5.2]);
        } // of difference()
    } // of param=1
    
    else if(_param==2) {
        print_cover(_t=header1,_t_vec=text_vec);
    } // pf param=2

    else if(_param==3) {
        // leds holder
        led_sw_holder();
  
    } // of if
    else if(_param==4) {
        box_to_print(_inner="true",ext_pins="false"); 

    } // of if
    
    
} // of print_box();

module led_sw_holder() {
    h1=10;
    delta = 1.5;
    difference() {
    union() {
        cube([60,40,2],center=true);
        translate([5,10,0]) cube([20,60,2],center=true);
        translate([5,0,h1/2]) {
            // switches
            translate(sw1_vec) cylinder(d=sw_d+delta,h=h1,$fn=60);
            translate(sw2_vec) cylinder(d=sw_d+delta,h=h1,$fn=60);
            translate(sw3_vec) cylinder(d=sw_d+delta,h=h1,$fn=60);
            translate([ 25-24, 35,-5]) cylinder(d=sw_d+delta,h=10,$fn=60);             
            // leds
            translate(led1_vec) cylinder(d=led_cover_d+delta,h=h1,$fn=60); // start
            translate(led2_vec) cylinder(d=led_cover_d+delta,h=h1,$fn=60); // cng      
            translate(led3_vec) cylinder(d=led_cover_d+delta,h=h1,$fn=60); // stop

        } // of translate()
    } // of union()
    
    
        
                // cut holes for push buttons
        translate([5,0,h1/2]) {
            //translate(sw1_vec) cylinder(d=sw_d,h=h1,$fn=60); // start
            translate(sw1_vec) cylinder(d=sw_d,h=h1*3,$fn=60,center=true); // start
            translate(sw2_vec) cylinder(d=sw_d,h=h1*3,$fn=60,center=true); // cng       
            translate(sw3_vec) cylinder(d=sw_d,h=h1*3,$fn=60,center=true);  // stop
            
            // leds
            translate(led1_vec) cylinder(d=led_cover_d,h=h1*3,$fn=60,center=true); // start
            translate(led2_vec) cylinder(d=led_cover_d,h=h1*3,$fn=60,center=true); // cng      
            translate(led3_vec) cylinder(d=led_cover_d,h=h1*3,$fn=60,center=true); // stop
            
            // potentiometer
            translate([ 25-24, 35,-5]) cylinder(d=sw_d,h=10*3,$fn=60,center=true);             
        } // of translate()

    } // of difference()
    
   
    
    
    
    module cyl_holder(_delta) {
        cylinder(d=sw_d+_delta,h=h1,$fn=60);
        difference() {
            cylinder(d=sw_d,h=h1,$fn=60);
            cylinder(d=sw_d,h=3*h1,$fn=60,center=true);
        } // of difference()
    } // of cyl_holder
    
    
    
    
    
    
    
} // of leds_holder()

module print_cover(_t="my text",_t_vec) {
    // print the cover            
    rotate([180,0,0])
    difference() {
        translate([0,0,box_h/2+1]) cover_to_print(_text=_t,_t_vec=_t_vec);
        box_to_print(_inner="false",ext_pins="true"); 
         } // of difference()    
} // of print_cover()




// *********************************************
module box_to_print(_inner="false",ext_pins="false") {
    // inner:       to include the non printable inner parts
    // ext_pins:    to create dumy pins up, to make holes for the cover
    // wemos:       wemos board holder 
    // PCB          wemos is mounted to pcb. Connect this pcb to the box.
    
    h_shield     = box_h/2-box_width;
    r_shield_vec = [0,0,-90];
    
    pins_vec = [4,0,-h_shield];
    //t_shield_vec = pins_vec+[0,0,8];  // for Arduino shield ??
    
    us_sensor_vec=[0,0,-box_h/2+20]; // was -30
    servo_vec=[-22,0+0-5,-box_h/4+15]; // was -23
 
    h_delta = -box_h/2+1;
    //bat_vec = [0,-19+3,-box_h/2+1+5];
    bat_vec = [3,16+1,-box_h/2+10];
    bat_rot_vec = [0,0,180];
    //arduino_vec=[10,15,-box_h/2+2];
    arduino_vec=[0,-15,-box_h/2+2+5];
    box(ext_pins);
       
    
    if (_inner=="true") {
        // Show the innser parts (servo, US sensor, Arduino)
        // not for real printing, of course
        translate(servo_vec) servo();
        translate(us_sensor_vec) ultra_sonic();
        translate(arduino_vec) rotate([0,0,90])
            Arduino_nano(_sig_pins_up=1,_sig_pins_down=0,_6_pins_up=0,_6_pins_down=0,_pcb_pins=0);
        translate(bat_vec+[0,0,0])  rotate (bat_rot_vec)
            18650_shield(_prod=0);
        //
        //18650_shield;
    } // of IF
} // of box_to_print()



module corner(ext_pins="false") {
    // ext_ins - to add dummy external pins to make a hole in the cover
    cone_h=4;           
    
    if (ext_pins=="true") {
        translate([0,0,box_h/2-cone_h/2+2])
            union() {
                cylinder(d=2,h=8);
                color("red") cylinder(d1=4,d2=2,h=2);
            } // of union()
    } // of if()
    
    difference() {
        cube ([corner_x,corner_x,box_h], center=true);  
        translate([0,0,box_h/2-cone_h/2-7]) pin_negative(size=2);
        //translate([0,0,box_h/2-cone_h/2-2]) cone();
    } // of difference()
    

    
    module cone() {
        // to make it easy to push the screw holder
        color("red") cylinder(r1=0,r2=2,h=cone_h);
    } // of cone() module
    
} // of corner()



module box(ext_pins="false") {
    inner_x = box_x - 2*box_width;
    inner_y = box_y - 2*box_width;
    difference() {
        cube ([box_x,box_y,box_h], center=true);  
        color("red") translate([0,0,box_width]) cube ([inner_x,inner_y,box_h], center=true);
    } // of difference     
    x_shift = box_x/2-corner_x/2;
    y_shift = box_y/2-corner_x/2;
    translate([x_shift,y_shift,0]) corner(ext_pins); // the screw holder
    translate([x_shift,-y_shift,0]) corner(ext_pins);
    translate([-x_shift,y_shift,0]) corner(ext_pins);
    translate([-x_shift,-y_shift,0]) corner(ext_pins);
            
} // of box()



module cover_to_print(_text="texttt",_t_vec) {
 
    cover_h = 2;
    header=_text;
    font = "Liberation Sans";
    //font = "Liberation Mono";
    //font = "Liberation Serif";
    txt1 = "";
    txt2 = "change";
    txt3 = "";
    font_big = 9;
    font_small = 5;
    
    
    
    
    difference() {
        union() {
            cube ([box_x,box_y,cover_h], center=true);  
            
            translate(_t_vec) translate([-4,-20,0])
                rotate([180,0,0])
                    color("red")
                        linear_extrude(height = 2)                         
                            text(text = header, font = font, size = font_big);
            
            // start
            translate([-37-2,7,0]) rotate([180,0,0]) color("red")
                linear_extrude(height = 2)                         
                    text(text = "START", font = font, size = font_small);
            /*
            // change
            translate([-37+16,7,0]) rotate([180,0,0]) color("red")
                linear_extrude(height = 2)                         
                    text(text = txt2, font = font, size = font_small);
            */
            // stop
            translate([-37+46+3,7,0]) rotate([180,0,0]) color("red")
                linear_extrude(height = 2)                         
                    text(text = "STOP", font = font, size = font_small);
           // Speed
            translate([-37+30-3,29,0]) rotate([180,0,0]) color("red")
                linear_extrude(height = 2)                         
                    text(text = "SPEED", font = font, size = font_small);
           // arrows
           color("green") translate([-15-1,7-5,-1.5+1]) linear_extrude(height = 3, center = true, convexity = 10) {
               translate([1,0,0]) unicode_character(left_arrow, 15, font);
               translate([0,0,0]) unicode_character(right_arrow, 15, font);
           } // of translate()
           
        } // of union
        
        
        // cut holes for push buttons
        translate(sw1_vec) cylinder(d=sw_d,h=10,$fn=60); // start
        translate(sw2_vec) cylinder(d=sw_d,h=10,$fn=60); // cng       
        translate(sw3_vec) cylinder(d=sw_d,h=10,$fn=60);  // stop
        
        // leds
        translate(led1_vec) cylinder(d=led_cover_d,h=10,$fn=60); // start
        translate(led2_vec) cylinder(d=led_cover_d,h=10,$fn=60); // cng      
        translate(led3_vec) cylinder(d=led_cover_d,h=10,$fn=60); // stop
        
        // potentiometer
        translate([ 25-24, 35,-5]) cylinder(d=sw_d,h=10,$fn=60);              
        } // of difference()
} // of cover_to_print()





left_arrow = "\u2192"; // This is the Unicode character for a right arrow.
right_arrow = "\u2190"; // This is the Unicode character for a right arrow.
size = 50;
font1 = "DejaVuSans";

module unicode_character(character, size, font) {
  text(character, size = size, font = font);
} // of unicode_character()
