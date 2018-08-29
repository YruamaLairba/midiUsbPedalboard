//cutout parameter :
//  center hole : 16 mm
//  screw hole : 3.3mm
//  screw hole distance : 22.2 mm


module midi_connector()  {
    module contact() {
        translate([-1,0,-5]) cube([2,1,6]);
    }
    linear_extrude(height=2)
        difference() {
            hull(){
                translate([-11.1,0]) circle(d=6.6);
                translate([11.1,0]) circle(d=6.6);
                circle(d=19);
            }
            {
                translate([-11.1,0]) circle(d=3.3);
                translate([11.1,0]) circle(d=3.3);
            }
        }
     mirror(v=[0,0,1]) cylinder(d=15.5,h=11.3);
     for (a = [0:45:180]) {
        rotate([0,0,a]) translate([-4,0,-11.3]) contact();
     }
}

midi_connector();