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

nbFs=4; //number of footswitch
fsSpace=80; //space between footswitch
fsSpaceBorder= 30; //space between footswitch and a border

pb_size = [(nbFs-1)*fsSpace+2*fsSpaceBorder, 90, 30];
echo("pb_size : ",pb_size);

module fingers(alternation=0, length=0, width=0, invert=false,center=false)
{
    finger_length=length/alternation;
    a= center ? length/2 : 0;
    b= center ? width/2 : 0;
    start= invert ? 1 : 0;
    for(i =[start:2:alternation-1])
    {
        translate([i*finger_length-a,-b]) square([finger_length,width]);
    }
}

module top_3D()
linear_extrude(height=thickness) top_2D();

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
    difference()
    {
        union()
        {
            square([pb_size.x,pb_size.y]);
        }
        union()
        {
            a=30;
            b=a+15+screen_size.x/2;
            c=b+screen_size.x/2+15;
            d=c+20;
            translate([a,pb_size.y-(thickness+20)])
            circle(d=rotaryHole);
            translate([b, pb_size.y-(thickness+20)])
            screen_clearance();
            translate([c, pb_size.y-(thickness+20)])
            circle(d=swHole);
            translate([d, pb_size.y-(thickness+20)])
            circle(d=swHole);
            //footswitches and leds holes
            translate([fsSpaceBorder,20])
            for(i = [0:nbFs-1])
            {
                translate([i*fsSpace,0]) circle(d=fsHole);
                translate([i*fsSpace,20]) circle(d=ledHole);
            }
            //fingers
            translate([pb_size.x/2,0])
            fingers(15,pb_size.x+20,thickness*2,true,true);
            translate([pb_size.x/2,pb_size.y])
            fingers(15,pb_size.x+20,thickness*2,true,true);
            translate([0,pb_size.y/2]) rotate(90)
            fingers(15,pb_size.y+2,thickness*2,true,true);
            translate([pb_size.x,pb_size.y/2]) rotate(90)
            fingers(15,pb_size.y+2,thickness*2,true,true);
        }
    }
}

module front_3D()
{
    linear_extrude(height=thickness) front_2D();
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

