include <DC_plug_pcb.scad>
pcb_x = 80;
pcb_y = 60;
pcb_h = 2;
Pillar_h = 6+1;

train_ctrl_pcb();

mk_holes();

module mk_holes() {
    translate([-5,10,10]) color("red")
        DC_plug_pcb(no_hole="true",no_pins="true");
    rotate([0,0,180]) translate([-70,-18,10])  color("red")
        DC_plug_pcb(no_hole="true",no_pins="true");
    // JST 4 pin for I2C
    translate([19,75,0]) color("blue")
        cube([14+3,15,7+7]);
    // USB connector 
        translate([67,40,10+11.5])  color("cyan")
        cube([15,17,15]);
    
   
    
} // of mk_holes()



module train_ctrl_pcb(_dxf=true) {
      
     //translate([0,0,Pillar_h+2]) import("PCB_Train_CTRL_2023-06-11.dxf");
    
    pcb_pillars();
     
} // of train_ctrl_pcb()

module pcb_pillars() {
    x1=3.5;
    y1=3;
    //x1=0;
    //y1=0;
    x2=x1+59;
    y2=y1;
    x3=x1;
    y3=y1+71;
    x4 = x2;
    y4 = y3;
    //import (file = "PCB_Train_CTRL_2023-06-11.dxf");
    color("red") translate([x1,y1,0]) my_pillar();
    color("red")translate([x2,y2,0]) my_pillar();
    color("red")translate([x3,y3,0]) my_pillar();
    color("red") translate([x4,y4,0]) my_pillar();
    translate([-1,-1,0]) color("green") cube([x2+7,y3+5,pcb_h]);
} // of pcb_screws_holes()

module my_pillar() {
    // insert m2 6mm od=3.5
    int_od = 3.2;
    ext_od = 8;
    int_l = Pillar_h;
    ext_l = 8;
    d_l = (ext_l-int_l)/2;
    difference() {
        cylinder(h=ext_l, d=ext_od,$fn=60);
        #translate([0,0,d_l+0.5]) cylinder(h=int_l, d=int_od,$fn=60);
    } // of difference()
} // of my_pillar()


