use <footswitch.scad>;
use <angle_bracket.scad>;
use <USB_connector.scad>;
use <midi_connector.scad>;
include <boitier_modules.scad>

//proxy for screw
module screw()
{
    e=0.1;
    translate([0,0,e-10])
    cylinder(h=e+10,d=4);
    cylinder(h=3,d=7);
}

//screw placement
union()
{
    //top
    union()
    {
        d1=[M4_distance_tb.x,M4_distance_tb.y,pb_size.z];
        d2=[pb_size.x-M4_distance_tb.x,M4_distance_tb.y,pb_size.z];
        d3=[M4_distance_tb.x,pb_size.y-M4_distance_tb.y,pb_size.z];
        d4=[pb_size.x-M4_distance_tb.x,pb_size.y-M4_distance_tb.y,pb_size.z];
        translate(d1) screw();
        translate(d2) screw();
        translate(d3) screw();
        translate(d4) screw();
    }

    //front
    translate([0,0,0])
    rotate([90,0,0])
    union()
    {
        d1=M4_distance_fr;
        d2=[pb_size.x-M4_distance_fr.x,M4_distance_fr.y];
        translate(d1) screw();
        translate(d2) screw();
    }

    //rear
    translate([pb_size.x,pb_size.y,0])
    rotate([90,0,180])
    union()
    {
        d1=M4_distance_fr;
        d2=[pb_size.x-M4_distance_fr.x,M4_distance_fr.y];
        translate(d1) screw();
        translate(d2) screw();
    }

    //left
    translate([0,pb_size.y,0])
    rotate([90,0,-90])
    union()
    {
        d1=M4_distance_lr;
        d2=[pb_size.y-M4_distance_lr.x,M4_distance_lr.y];
        translate(d1) screw();
        translate(d2) screw();
    }

    //right
    translate([pb_size.x,0,0])
    rotate([90,0,90])
    union()
    {
        d1=M4_distance_lr;
        d2=[pb_size.y-M4_distance_lr.x,M4_distance_lr.y];
        translate(d1) screw();
        translate(d2) screw();
    }

    //bottom
    translate([0,pb_size.y,0])
    rotate([180,0,0])
    union()
    {
        d1=M4_distance_tb;
        d2=[pb_size.x-M4_distance_tb.x,M4_distance_tb.y];
        d3=[M4_distance_tb.x,pb_size.y-M4_distance_tb.y];
        d4=[pb_size.x-M4_distance_tb.x,pb_size.y-M4_distance_tb.y];
        translate(d1) screw();
        translate(d2) screw();
        translate(d3) screw();
        translate(d4) screw();
    }
}

//angle bracket
union()
{
    translate([thickness,thickness,thickness])
    corner_bracket();
    translate([pb_size.x-thickness,thickness,pb_size.z-thickness])
    rotate([0,180,0])
    corner_bracket();
    translate([thickness,pb_size.y-thickness,pb_size.z-thickness])
    rotate([180,0,0])
    corner_bracket();
    translate([pb_size.x-thickness,pb_size.y-thickness,thickness])
    rotate([180,180,0])
    corner_bracket();
}

//footswitch
union()
{   translate([fsSpaceBorder,20,thickness])
    for( i = [0:nbFs-1])
    {
        translate([i*fsSpace,0,0])
        rotate(90)
        footswitch();
    }
}

//connector
union()
{
    translate([pb_size.x,pb_size.y,0])
    rotate([90,0,180])
    {
        //USB connector
        translate([pb_size.x/2,pb_size.z/2,-thickness])
        rotate([180,0,0])
        usb_connector();
        //midi connector
        translate([pb_size.x/2-40,pb_size.z/2])
        rotate(35)
        midi_connector();
        translate([pb_size.x/2-40-30,pb_size.z/2])
        rotate(35)
        midi_connector();
    }
}

//the enclosure
color("yellow",alpha=0.25)
union()
{
    translate([0,0,pb_size.z-thickness])
    top_3D();

    color("blue")
    translate([0,thickness,0])
    rotate([90,0,0])
    front_3D();

    color("lightblue")
    translate([pb_size.x,pb_size.y-thickness,0])
    rotate([90,0,180])
    rear_3D();

    color("red")
    translate([thickness,pb_size.y,0])
    rotate([90,0,-90])
    left_3D();

    color("red")
    translate([pb_size.x-thickness,0,0])
    rotate([90,0,90])
    right_3D();

    color("ivory")
    translate([0,pb_size.y,thickness])
    rotate([180,0,0])
    bottom_3D();
}
