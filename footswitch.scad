module contact()
{
    rotate([90,0,0]) union()
    {
        linear_extrude(height =1,center=true)  difference()
        {
            union()
            {
                square([5,3 ]);
                translate([5,5/2]) circle(d=5);
            }
            translate([5,5/2]) circle(d=2,center=true);
        }    
     }
 }

module footswitch()
 {
    translate([-15/2,-17/2,0]) cube([15,17,20]);
    translate([0,0,20]) cylinder(d1=14,d2=10,h=2);
    translate([0,0,10]) cylinder(d=12,h=12+10);
    translate([0,0,20+12]) cylinder(d1=12,d2=10,h=1);
    translate([0,0,10+13]) cylinder(d=8,h=5+10);
    translate ([0,0,20+13+5]) cylinder(d=10,h=5);
     
    mirror()
    {
        translate([7,-8,0]) contact();
        translate([7,0,0]) contact();
        translate([7,8,0]) contact();
    }
    {
        translate([7,-8,0]) contact();
        translate([7,0,0]) contact();
        translate([7,8,0]) contact();
    }
}

footswitch();

