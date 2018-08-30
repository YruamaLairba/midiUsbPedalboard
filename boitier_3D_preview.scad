include <boitier_modules.scad>


union(){
    color("blue",alpha=0.2) translate([0,0,low_step_height]) low_top_3D();
    translate([0,0,high_step_height])  high_top_3D();

    translate([0,thickness,0]) rotate([90,0,0]) low_front_3D();
    color("green",alpha=0.5) translate([0,60+thickness,0]) rotate([90,0,0]) high_front_3D();
    color("green") translate([0,pb_size_y,0]) rotate([90,0,0]) rear_3D();

    color("red",alpha=0.5) translate([thickness,0,0]) rotate([0,-90,0]) left_3D();
    color("red",alpha=0.5) translate([pb_size_x,0,0]) rotate([0,-90,0]) right_3D();

    color("grey",alpha=0.5) translate([0,0,-thickness]) bottom_3D();
}