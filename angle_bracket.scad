thickness1=2.5;
thickness2=3.3;
hole=2;//diameter
$fs=0.1;

module angle_bracket_double()
{
    translate([-30/2,0,0]) intersection()
    {
        union()
        {
            linear_extrude(height=thickness2) translate([0,-20])  
            {
                difference()
                {
                    union()
                    {
                        square([30,20]);
                    }
                    {
                        translate([30/4+thickness1/4,20/2-hole]) circle(d=hole);
                        translate([30-(30+thickness1)/4,20/2-hole]) circle(d=hole);
                    }
                }
            }
            rotate([90,0,0]) linear_extrude(height=thickness2)
            {
                difference()
                {
                    union()
                    {
                        square([30,20]);
                    }
                    {
                        translate([30/4+thickness1/4,20/2+hole]) circle(d=hole);
                        translate([30-(30+thickness1)/4,20/2+hole]) circle(d=hole);
                    }
                }
            }
            
            translate([thickness1,0,0]) rotate([0,-90,0])
            linear_extrude(height=thickness1)
            polygon(points = [[0, 0],[0,-20],[20,0]]);

            translate([15,0,0]) rotate([0,-90,0])
            linear_extrude(height=thickness1,center=true)    
            polygon(points = [[0, 0],[0,-20],[20,0]]);

            translate([30,0,0]) rotate([0,-90,0])
            linear_extrude(height=thickness1)
            polygon(points = [[0, 0],[0,-20],[20,0]]);
        }
        
        translate([30,0,0]) rotate([0,-90,0])
        linear_extrude(height=30)
        polygon(points = [[0, 0],[0,-20],[20,0]]);
    }
}

module angle_bracket_simple()
{
    translate([-16/2,0,0]) intersection()
    {
        union()
        {
            linear_extrude(height=thickness2) translate([0,-20])  
            {
                difference()
                {
                    union()
                    {
                        square([16,20]);
                    }
                    {
                        translate([16/2,20/2-hole]) circle(d=hole);

                    }
                }
            }
            rotate([90,0,0]) linear_extrude(height=thickness2)
            {
                difference()
                {
                    union()
                    {
                        square([16,20]);
                    }
                    {
                        translate([16/2,20/2+hole]) circle(d=hole);
                    }
                }
            }
            
            translate([thickness1,0,0]) rotate([0,-90,0])
            linear_extrude(height=thickness1)
            polygon(points = [[0, 0],[0,-20],[20,0]]);

            translate([16,0,0]) rotate([0,-90,0])
            linear_extrude(height=thickness1)    
            polygon(points = [[0, 0],[0,-20],[20,0]]);

        }
        
        translate([16,0,0]) rotate([0,-90,0])
        linear_extrude(height=16)
        polygon(points = [[0, 0],[0,-20],[20,0]]);
    }
}
angle_bracket_simple();
*angle_bracket_double();

