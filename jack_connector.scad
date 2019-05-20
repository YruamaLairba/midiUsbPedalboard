module jack_connector()
{
    translate([0,0,-20])
    union()
    {
        cylinder(d=10.8,h=30.5);
        cylinder(d=15,h=21);
        translate([0,0,-4]) cylinder(d=9,h=5);
        translate([0,-10,0]) cube([8,20,21]);
        translate([7.9,-17/2,2]) cube([8.5,1,17,]);
        translate([7.9,17/2-1,2]) cube([8.5,1,17,]);
    }
}
jack_connector();
