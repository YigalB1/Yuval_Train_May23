// sizes trials
cube_x = 85;
cube_y = 35;


//try_leds(_led=5,_d=0.2,_dx=13,_x=90);
//try_leds(_led=8,_d=0.2,_dx=13,_x=110);
try_leds(_led=11,_d=0.2,_dx=15,_x=130);
//try_usb();

module try_leds(_led=5,_d=0.2,_dx=10,_x=85) {
    // param is for led 5mm or 8mm
    x0 = -_x/2+ _led;
    //echo(_led +1*_d);
    echo(_led +5*_d);
    
    
    difference() {
        cube([_x,cube_y,2],center=true);
        #translate([x0+0*_dx,cube_y/4,0]) cylinder(d=_led +1*_d,h=5,$fn=60,center=true);
        translate([x0+1*_dx,cube_y/4,0]) cylinder(d=_led +2*_d,h=5,$fn=60,center=true);
        translate([x0+2*_dx,cube_y/4,0]) cylinder(d=_led +3*_d,h=5,$fn=60,center=true);
        translate([x0+3*_dx,cube_y/4,0]) cylinder(d=_led +4*_d,h=5,$fn=60,center=true);
        #translate([x0+4*_dx,cube_y/4,0]) cylinder(d=_led +5*_d,h=5,$fn=60,center=true);
        translate([x0+5*_dx,cube_y/4,0]) cylinder(d=_led +6*_d,h=5,$fn=60,center=true);
        translate([x0+6*_dx,cube_y/4,0]) cylinder(d=_led +7*_d,h=5,$fn=60,center=true);
        translate([x0+7*_dx,cube_y/4,0]) cylinder(d=_led +8*_d,h=5,$fn=60,center=true);
        
        translate([x0+0*_dx,-cube_y/4,0]) cylinder(d=_led +8*_d,h=5,$fn=60,center=true);
        translate([x0+1*_dx,-cube_y/4,0]) cylinder(d=_led +9*_d,h=5,$fn=60,center=true);
        translate([x0+2*_dx,-cube_y/4,0]) cylinder(d=_led +10*_d,h=5,$fn=60,center=true);
        translate([x0+3*_dx,-cube_y/4,0]) cylinder(d=_led +11*_d,h=5,$fn=60,center=true);
        translate([x0+4*_dx,-cube_y/4,0]) cylinder(d=_led +12*_d,h=5,$fn=60,center=true);
        translate([x0+5*_dx,-cube_y/4,0]) cylinder(d=_led +13*_d,h=5,$fn=60,center=true);
        translate([x0+6*_dx,-cube_y/4,0]) cylinder(d=_led +14*_d,h=5,$fn=60,center=true);
        translate([x0+7*_dx,-cube_y/4,0]) cylinder(d=_led +15*_d,h=5,$fn=60,center=true);
        
        
    } // of difference()
} // of module try_leds()

module try_usb() {
    difference() {
        cube([cube_x,cube_y,2],center=true);
        translate([-cube_x/2+10, cube_y/4,0]) cube([14.5,5.1,10],center=true);
        translate([-cube_x/2+29, cube_y/4,0]) cube([14.7,5.1,10],center=true);
        translate([-cube_x/2+48, cube_y/4,0]) cube([14.9,5.1,10],center=true);
        translate([-cube_x/2+67, cube_y/4,0]) cube([15.1,5.1,10],center=true);
        
        translate([-cube_x/2+10,-cube_y/4,0]) cube([14.5,5.2,10],center=true);
        translate([-cube_x/2+29,-cube_y/4,0]) cube([14.7,5.2,10],center=true); // this is good
        
        translate([-cube_x/2+48,-cube_y/4,0]) cube([14.9,5.3,10],center=true);
        translate([-cube_x/2+67,-cube_y/4,0]) cube([15.1,5.3,10],center=true);
  
        
    } // of difference()
} // of module try_usb()

