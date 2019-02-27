use <footswitch.scad>;
use <angle_bracket.scad>;
use <USB_connector.scad>;
use <midi_connector.scad>;
include <boitier_modules.scad>

//the enclosure
union()
{
    translate([0,0,pb_size.z-thickness])
    top_3D();

    color("blue")
    translate([0,thickness,0])
    rotate([90,0,0])
    front_3D();

    color("red")
    translate([thickness,pb_size.y,0])
    rotate([90,0,-90])
    left_3D();
}

//angle bracket
%union()
{
}

//footswitch
%union(){
}

//connector
