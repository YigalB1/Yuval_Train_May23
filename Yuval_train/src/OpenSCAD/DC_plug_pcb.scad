//DC_plug_pcb();

module DC_plug_pcb(no_hole="true",no_pins="true"){
    // the no_hole parameters target is to eliminate 
    // the hole with the pin, to allow substraction 
    // in the box (so we don't remain with a circle
    // in the middle
    
    
    x1 = 3.5; // was13.9; the front cube
    x2 = 14.5; // the hole length
    y = 9+1.3; // 13 dec changed from 9+1.0
    h1 = 10.7+1; // the +1 is spare
    h2 = 6.2;
    h3 = h1-h2;
    diameter = y;
    hole_d = 6.4;
    hole_h = 10.9;
    pin_d = 2.0;
    pin_delta_h = 6.5;
    
    difference() {
        union(){
            cube([x1,y,h1]);
            translate([-10,0,0]) cube([x1+10,y,h1]); // added just for better hole
            
            cube([x2,y,h2]);
            rotate([0,90,0]) translate([-h3 ,y/2,0])
                cylinder(d=diameter,h=x2,$fn=60);
            if (no_pins=="false") {
                translate([0,0,0]) connectors();
            } // of if()
        } // of union
    
    
    if (no_hole=="false") hole();
    } // of difference()

    
    center_pin();

    module connectors() {
        color("red") conn();
        module conn() {
            conn_x = 0.3;
            conn_y = 2.1;
            conn_h = 4.6;
            center1_deep = 7.8;
            center2_deep = 13.6;
            w_delta = conn_x*2;
            conn2_h = 11.6;
            conn3_h = 8.8;
            conn3_deep = 10.6;
            
            translate([center1_deep+w_delta ,y/2-conn_y/2,-conn_h])
                cube([conn_x,conn_y,conn_h],center="true");
            
            translate([center2_deep+w_delta,y/2-conn_y/2,-conn_h])
                cube([conn_x,conn_y,conn2_h],center="true");
            
            rotate([0,0,90]) translate([0,-conn3_deep,-conn_h])
                cube([conn_x,conn_y,conn3_h],center="true");
            

        } // of conn()
    } // of connectors()



    module hole() {        
        translate([-1,y/2,pin_delta_h]) rotate([0,90,0]) 
            cylinder(d=hole_d,h=hole_h,$fn=60);
    } // of hole()  
  
    module center_pin() {    
        translate([2,y/2,pin_delta_h]) rotate([0,90,0])
            cylinder(d=pin_d,h=hole_h-2,$fn=60);        
    } // of center_pin();
    
} // of dc_plug



