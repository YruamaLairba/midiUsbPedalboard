include <boitier_modules.scad>


union(){
    translate([0,0]) low_front_2D();
    translate([0,32]) low_top_2D();
    translate([0,98]) high_front_2D();
    translate([0,89]) high_top_2D();
    translate([0,320]) rotate([0,0,180]) mirror(v=[1,0,0]) rear_2D(); 
    translate([200,177]) rotate([0,0,0]) left_2D();
    translate([191,177]) rotate([0,0,0]) mirror(v=[1,0,0]) right_2D();
    translate([142,-5]) bottom_2D();
}