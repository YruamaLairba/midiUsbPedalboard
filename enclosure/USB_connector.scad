//distance trous 30 mm
//vis M3, tap 2.5, clearance 3.4


module usb_connector() {
    height= 14;
    linear_extrude(6) difference() {
        hull() {
            translate([-15,0]) circle(d=height);
            translate([15,0]) circle(d=height);
        }
        {
            translate([-15,0]) circle(d=2.5);
            translate([15,0]) circle(d=2.5);
        }
    }
    translate([0,0,25/2]) cube([21,height,25],center=true);
}

usb_connector();