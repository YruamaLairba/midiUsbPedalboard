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

finger_size_x=20.5;
finger_size_y=20;
finger_size_z=12;

debug=false;

pb_size = [(nbFs-1)*fsSpace+2*fsSpaceBorder, 90, 30];
echo("pb_size : ",pb_size);

//M4 screw positionning from border (corner bracket)
M4_distance_tb=[12,12]; //for top/bottom panel
M4_distance_fr=[12,pb_size.z/2]; //for front/rear panel
M4_distance_lr=[15,pb_size.z/2]; //for left/right panel

//reinforcing positionning
M4_reinforcing_t=10; //distance from the top border
M4_reinforcing_r=pb_size.z/2; //distance from the rear border
reinforcing1_pos=[pb_size.x/2-42,pb_size.y-thickness,pb_size.z-thickness];
reinforcing1_rot=[180,0,-90];
reinforcing2_pos=[pb_size.x/2+34,pb_size.y-thickness,pb_size.z-thickness];
reinforcing2_rot=[180,0,-90];

//connector positionning
usb_pos=[64,pb_size.z/2];
midi1_pos=[pb_size.x/2-10,pb_size.z/2];
midi2_pos=[pb_size.x/2+17,pb_size.z/2];
exp1_pos=[62+36,pb_size.z/2];
exp2_pos=[30,pb_size.z/2];

module fingers(
length=0,
finger_length=10,
width=10,
invert=false,
center=false,
debug=false)
{
    nb_finger=round(length/(finger_length*2));
    inv = invert ? 1 : 0;
    start=-(nb_finger-inv)/2;
    end= (nb_finger-inv)/2;
    a= center ? 0: length/2;
    b= center ? 0: width/2;
    translate([a,b])
    difference()
    {
        for(i =[start:1:end])
        {
            translate([(i)*2*finger_length,0])
            square([finger_length,width],center=true);
        }
        union()
        {
            size = [finger_length+2,width+2];
            translate([-size.x/2-length/2,0])
            square(size,center=true);
            translate([size.x/2+length/2,0])
            square(size,center=true);
        }
    }
    if (debug)
    {
        %union()
        {
            size = [finger_length+2,width+2];
            translate([-size.x/2-length/2,0])
            square(size,center=true);
            translate([size.x/2+length/2,0])
            square(size,center=true);
        }
    }
}
module reinforcing()
{
    r_thickness=3;
    r_size_x=(M4_reinforcing_t-thickness)*2;
    r_size_y=14;
    r_size_z=(M4_reinforcing_r-thickness)*2;
    r_hole=3.3;
    difference()
    {
        union()
        {
            rotate([-90,0,0])
            linear_extrude(height=r_size_y,center=true)
            polygon(points = [[0, 0],[0,-r_size_z],[r_size_x,0]]);
        }
        translate([M4_reinforcing_t-thickness,0,-5])
        cylinder(d=r_hole,h=r_size_z+10);
        translate([-5,0,M4_reinforcing_r-thickness])
        rotate([0,90,0])
        cylinder(d=r_hole,h=r_size_z+10);
        translate([r_thickness,-r_size_y/2+r_thickness,r_thickness])
        cube([r_size_x,r_size_y-r_thickness*2,r_size_z]);
    }
}
module corner_bracket()
{
    cb_thickness=3;
    cb_size_x= 9+(max(M4_distance_tb.x,M4_distance_fr.x)-thickness);
    cb_size_y= 9+(max(M4_distance_tb.y,M4_distance_lr.x)-thickness);
    cb_size=[cb_size_x,cb_size_y,pb_size.z-2*thickness];
    cb_hole=3.3;
    bottom_hole_pos=[for(i=M4_distance_tb) i-thickness];
    top_hole_pos=[for(i=M4_distance_tb) i-thickness];
    left_hole_pos=[for(i=M4_distance_lr) i-thickness];
    front_hole_pos=[for(i=M4_distance_fr) i-thickness];
    e=0.1; //epsilon margin
    difference()
    {
        union()
        {
            cube(cb_size);
        }
        union()
        {
            //clearance
            translate([cb_thickness, cb_thickness, cb_thickness])
            cube([cb_size.x,cb_size.y,cb_size.z-2*cb_thickness]);

            //bottom hole
            translate([bottom_hole_pos.x,bottom_hole_pos.y,-e])
            cylinder(h=cb_thickness+2*e,d=cb_hole);

            //top hole
            translate([top_hole_pos.x,top_hole_pos.y,cb_size.z-cb_thickness-e])
            cylinder(h=cb_thickness+2*e,d=cb_hole);

            //left hole
            translate([-e,left_hole_pos.x,left_hole_pos.y])
            rotate([0,90,0])
            cylinder(h=cb_thickness+2*e,d=cb_hole);

            //front hole
            translate([front_hole_pos.x,-e,front_hole_pos.y])
            rotate([-90,0,0])
            cylinder(h=cb_thickness+2*e,d=cb_hole);
        }
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
            a=40;
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
            fingers(pb_size.x+2,finger_size_x,thickness*2,true,true,debug);
            translate([pb_size.x/2,pb_size.y])
            fingers(pb_size.x+2,finger_size_x,thickness*2,true,true,debug);

            translate([0,pb_size.y/2]) rotate(90)
            fingers(pb_size.y+2,finger_size_y,thickness*2,true,true,debug);
            translate([pb_size.x,pb_size.y/2]) rotate(90)
            fingers(pb_size.y+2,finger_size_y,thickness*2,true,true,debug);

            //m4 holes for corner bracket
            d1=M4_distance_tb;
            d2=[pb_size.x-M4_distance_tb.x,M4_distance_tb.y];
            d3=[M4_distance_tb.x,pb_size.y-M4_distance_tb.y];
            d4=[pb_size.x-M4_distance_tb.x,pb_size.y-M4_distance_tb.y];
            translate(d1) circle(d=M4Hole);
            translate(d2) circle(d=M4Hole);
            translate(d3) circle(d=M4Hole);
            translate(d4) circle(d=M4Hole);

            //m4 holes for reinforcement
            translate([reinforcing1_pos.x,pb_size.y-M4_reinforcing_t])
            circle(d=M4Hole);
            translate([reinforcing2_pos.x,pb_size.y-M4_reinforcing_t])
            circle(d=M4Hole);

            //m4 holes for perfboard mounting
            p_hole_space = 22.86;// 1"
            translate([(pb_size.x-p_hole_space)/2,50]) circle(d=M4Hole);
            translate([(pb_size.x+p_hole_space)/2,50]) circle(d=M4Hole);
        }
    }
}

module front_3D()
{
    linear_extrude(height=thickness) front_2D();
}

module front_2D()
{
    difference()
    {
        union()
        {
            square([pb_size.x,pb_size.z]);
        }
        union()
        {
            //fingers
            translate([pb_size.x/2,0])
            fingers(pb_size.x+2,finger_size_x,thickness*2,false,true,debug);
            translate([pb_size.x/2,pb_size.z])
            fingers(pb_size.x+2,finger_size_x,thickness*2,false,true,debug);

            translate([0,pb_size.z/2]) rotate(90)
            fingers(pb_size.z+2,finger_size_z,thickness*2,true,true,debug);
            translate([pb_size.x,pb_size.z/2]) rotate(90)
            fingers(pb_size.z+2,finger_size_z,thickness*2,true,true,debug);

            //m4 holes
            d1=M4_distance_fr;
            d2=[pb_size.x-M4_distance_fr.x,M4_distance_fr.y];
            translate(d1) circle(d=M4Hole);
            translate(d2) circle(d=M4Hole);
        }
    }
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
        //size taken from rean (neutrik) drawing
        translate([-11.1,0]) circle(d=3.2);
        translate([11.1,0]) circle(d=3.2);
        circle(d=15.1);
    }
    difference()
    {
        union()
        {
            square([pb_size.x,pb_size.z]);
        }
        union()
        {
            //connector cutout
            translate(usb_pos)
            usb_clearance();
            translate(midi1_pos)
            rotate(35)
            midi_cutout();
            translate(midi2_pos)
            rotate(35)
            midi_cutout();
            //jack inputs
            translate(exp1_pos) circle(d=11);
            translate(exp2_pos) circle(d=11);
            //fingers
            translate([pb_size.x/2,0])
            fingers(pb_size.x+2,finger_size_x,thickness*2,false,true,debug);
            translate([pb_size.x/2,pb_size.z])
            fingers(pb_size.x+2,finger_size_x,thickness*2,false,true,debug);

            translate([0,pb_size.z/2]) rotate(90)
            fingers(pb_size.z+2,finger_size_z,thickness*2,true,true,debug);
            translate([pb_size.x,pb_size.z/2]) rotate(90)
            fingers(pb_size.z+2,finger_size_z,thickness*2,true,true,debug);

            //m4 holes
            d1=M4_distance_fr;
            d2=[pb_size.x-M4_distance_fr.x,M4_distance_fr.y];
            translate(d1) circle(d=M4Hole);
            translate(d2) circle(d=M4Hole);

            //m4 holes for reinforcement
            translate([pb_size.x-reinforcing1_pos.x,
                pb_size.z-M4_reinforcing_r])
            circle(d=M4Hole);
            translate([pb_size.x-reinforcing2_pos.x,
                pb_size.z-M4_reinforcing_r])
            circle(d=M4Hole);
        }
    }
}


module left_3D()
{
    linear_extrude(height=thickness) left_2D();
}

module left_2D()
{
    difference()
    {
        union()
        {
            square([pb_size.y,pb_size.z]);
        }
        union()
        {
            //fingers
            translate([pb_size.y/2,0])
            fingers(pb_size.y+2,finger_size_y,thickness*2,false,true,debug);
            translate([pb_size.y/2,pb_size.z,])
            fingers(pb_size.y+2,finger_size_y,thickness*2,false,true,debug);

            translate([0,pb_size.z/2]) rotate(90)
            fingers(pb_size.z+2,finger_size_z,thickness*2,false,true,debug);
            translate([pb_size.y,pb_size.z/2]) rotate(90)
            fingers(pb_size.z+2,finger_size_z,thickness*2,false,true,debug);

            //m4 holes
            d1=M4_distance_lr;
            d2=[pb_size.y-M4_distance_lr.x,M4_distance_lr.y];
            translate(d1) circle(d=M4Hole);
            translate(d2) circle(d=M4Hole);
        }
    }
}

module right_3D()
{
    linear_extrude(height=thickness) right_2D();
}

module right_2D()
{
    difference()
    {
        union()
        {
            square([pb_size.y,pb_size.z]);
        }
        union()
        {
            //fingers
            translate([pb_size.y/2,0])
            fingers(pb_size.y+2,finger_size_y,thickness*2,false,true,debug);
            translate([pb_size.y/2,pb_size.z,])
            fingers(pb_size.y+2,finger_size_y,thickness*2,false,true,debug);

            translate([0,pb_size.z/2]) rotate(90)
            fingers(pb_size.z+2,finger_size_z,thickness*2,false,true,debug);
            translate([pb_size.y,pb_size.z/2]) rotate(90)
            fingers(pb_size.z+2,finger_size_z,thickness*2,false,true,debug);

            //m4 holes
            d1=M4_distance_lr;
            d2=[pb_size.y-M4_distance_lr.x,M4_distance_lr.y];
            translate(d1) circle(d=M4Hole);
            translate(d2) circle(d=M4Hole);
        }
    }
}

module bottom_3D()
{
    linear_extrude(height=thickness) bottom_2D();
}

 module bottom_2D()
{
    difference()
    {
        union()
        {
            square([pb_size.x,pb_size.y]);
        }
        union()
        {
            //fingers
            translate([pb_size.x/2,0])
            fingers(pb_size.x+2,finger_size_x,thickness*2,true,true,debug);
            translate([pb_size.x/2,pb_size.y])
            fingers(pb_size.x+2,finger_size_x,thickness*2,true,true,debug);
            translate([0,pb_size.y/2]) rotate(90)
            fingers(pb_size.y+2,finger_size_y,thickness*2,true,true,debug);
            translate([pb_size.x,pb_size.y/2]) rotate(90)
            fingers(pb_size.y+2,finger_size_y,thickness*2,true,true,debug);

            //m4 holes
            d1=M4_distance_tb;
            d2=[pb_size.x-M4_distance_tb.x,M4_distance_tb.y];
            d3=[M4_distance_tb.x,pb_size.y-M4_distance_tb.y];
            d4=[pb_size.x-M4_distance_tb.x,pb_size.y-M4_distance_tb.y];
            translate(d1) circle(d=M4Hole);
            translate(d2) circle(d=M4Hole);
            translate(d3) circle(d=M4Hole);
            translate(d4) circle(d=M4Hole);
        }
    }
}

