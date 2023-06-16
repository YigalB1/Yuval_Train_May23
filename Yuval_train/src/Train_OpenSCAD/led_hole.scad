// this is just a module for the led's hole
// creates a cylinder
// TBD: get a real led model

led_hole(size=8);

module led_hole(size=5) {
    d_led = size+0.2;
    color("green") cylinder(d=d_led,h=8,$fn=60);
    } // of led_hole()