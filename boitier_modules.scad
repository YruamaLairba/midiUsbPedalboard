$fn=80;
//Holes diameter
fsHole=12;//spec 12, measured 11.8 on fs
ledHole=7.8;//spec 8? measured 7.6 on Led
rotaryHole=8;//spec 8 ? measured 7.8 on rotary coder
swHole=7;//spec 7, measured 6.8 on swHole
screenHole=2.5;//spec 2.5 ? measured 2.4 on screw
M4Hole=4;//spec 4, measured 3.9 on screw
//USBHole=3;//spec 3 ? measured 2.9 on USb screw

//thickness of material to be laser cutted
thickness=3;

//x: measured 26.65, pcb 28mm
//y: measured 19.3
screen_size = [28,19.4];

pb_size = [140,180,45];

module top_3D()
linear_extrude(height=thickness) high_top_2D();

module top_2D()
{
    //screen holes and clearance
    module screen_clearance()
    {
        square([screen_size.x,screen_size.y],center=true);
        translate([0,-screen_size.y/2]) square([12.5,8],center=true);
        translate([0,screen_size.y/2]) square([17,8],center=true);
        translate([11.75,11.75]) circle(d=screenHole);
        translate([-11.75,11.75]) circle(d=screenHole);
        translate([11.75,-11.75]) circle(d=screenHole);
        translate([-11.75,-11.75]) circle(d=screenHole);
    }
}

module front_3D()
{
    linear_extrude(height=thickness) low_front_2D();
}

module front_2D()    
{
}

module rear_3D()
{
    linear_extrude(height=thickness) rear_2D();
}

module rear_2D()
{
    module usb_clearance()
    {
        square([12,12], center=true);
        translate([-15,0]) circle(d=3.3);
        translate([15,0]) circle(d=3.3);
    }
    module midi_cutout()
    {
        translate([-11.1,0]) circle(d=3.3);
        translate([11.1,0]) circle(d=3.3);
        circle(d=16);
    }
}


module left_3D()
{
    linear_extrude(height=thickness) left_2D();
}

module left_2D()
{
}

module right_3D()
{
    linear_extrude(height=thickness) right_2D();
}

module right_2D()
{
}

module bottom_3D()
{
    linear_extrude(height=thickness) bottom_2D();
}
 
 module bottom_2D()
{
}

