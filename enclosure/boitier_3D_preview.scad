use <footswitch.scad>;
use <USB_connector.scad>;
use <midi_connector.scad>;
use <jack_connector.scad>;

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
color("lightgrey")
union()
{
    //top
    translate([0,0,pb_size.z])
    union()
    {
        //corner barcket
        d1=[M4_distance_tb.x,M4_distance_tb.y];
        d2=[pb_size.x-M4_distance_tb.x,M4_distance_tb.y];
        d3=[M4_distance_tb.x,pb_size.y-M4_distance_tb.y];
        d4=[pb_size.x-M4_distance_tb.x,pb_size.y-M4_distance_tb.y];
        translate(d1) screw();
        translate(d2) screw();
        translate(d3) screw();
        translate(d4) screw();

        //reinforcement
        translate([reinforcing1_pos.x,pb_size.y-M4_reinforcing_t])
        screw();
        translate([reinforcing2_pos.x,pb_size.y-M4_reinforcing_t])
        screw();

        //perfboard mounting
        p_hole_space = 22.86;// 1"
        translate([(pb_size.x-p_hole_space)/2,50]) screw();
        translate([(pb_size.x+p_hole_space)/2,50]) screw();
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
        //corner bracket
        d1=M4_distance_fr;
        d2=[pb_size.x-M4_distance_fr.x,M4_distance_fr.y];
        translate(d1) screw();
        translate(d2) screw();

        //reinforcement
        translate([pb_size.x-reinforcing1_pos.x,pb_size.z-M4_reinforcing_r])
        screw();
        translate([pb_size.x-reinforcing2_pos.x,pb_size.z-M4_reinforcing_r])
        screw();
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

translate([pb_size.x/2,50-6,pb_size.z-thickness])
rotate([0,180,0])
import("perfboard.stl");

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

//reinforcing
union()
{
    translate(reinforcing1_pos)
    rotate(reinforcing1_rot)
    reinforcing();
    translate(reinforcing2_pos)
    rotate(reinforcing2_rot)
    reinforcing();
}

//footswitch
color("lightgrey")
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
        translate([usb_pos.x,usb_pos.y,-thickness])
        rotate([180,0,0])
        usb_connector();
        //midi connector
        translate(midi1_pos)
        rotate(35)
        midi_connector();
        translate(midi2_pos)
        rotate(35)
        midi_connector();
        //jacks 
        translate([exp1_pos.x,exp1_pos.y,-thickness])
        rotate(180)
        jack_connector();
        translate([exp2_pos.x,exp2_pos.y,-thickness])
        jack_connector();
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
