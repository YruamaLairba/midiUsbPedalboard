use <footswitch.scad>;
use <angle_bracket.scad>;
use <custom_angle_bracket.scad>;
use <USB_connector.scad>;
use <midi_connector.scad>;
include <boitier_modules.scad>

module my_angle_bracket()
{
    custom_angle_bracket(
    size=[15,25,pb_size.z-2*thickness],
    hole_diameter=3,
    thickness=3,
    bottom_hole_pos=[for(i=M4_distance_bottom) i-thickness],
    top_hole_pos=[for(i=M4_distance_top) i-thickness],
    left_hole_pos=[for(i=M4_distance_sides) i-thickness],
    front_hole_pos=[for(i=M4_distance_sides) i-thickness]
    );
}

//angle bracket
union()
{
    translate([thickness,thickness,thickness])
    my_angle_bracket();
    translate([pb_size.x-thickness,thickness,pb_size.z-thickness])
    rotate([0,180,0])
    my_angle_bracket();
    translate([thickness,pb_size.y-thickness,pb_size.z-thickness])
    rotate([180,0,0])
    my_angle_bracket();
    translate([pb_size.x-thickness,pb_size.y-thickness,thickness])
    rotate([180,180,0])
    my_angle_bracket();
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
