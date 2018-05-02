use <footswitch.scad>;
use <angle_bracket.scad>;

$fn=80;
//Holes diameter
fsHole=12;//spec 12, measured 11.8 on fs
ledHole=7.8;//spec 8? measured 7.6 on Led
rotaryHole=8;//spec 8 ? measured 7.8 on rotary coder
swHole=7;//spec 7, measured 6.8 on swHole
screenHole=2.5;//spec 2.5 ? measured 2.4 on screw
M4Hole=4;//spec 4, measured 3.9 on screw
//USBHole=3;//spec 3 ? measured 2.9 on USb screw


thickness=5;

//screen_size_x=26;
//screen_size_y=19;
screen_size_x =28;//measured 26.65, pcb 28mm
screen_size_y =19.4;//measured 19.3


pb_size_x = 140;
pb_size_y = 180;
pb_size_z = 45;

low_step_height= 30-thickness;
high_step_height= low_step_height +15;

fs_side_dist=30;//distance between side and fs hole center

module high_top_3D()
linear_extrude(height=thickness) high_top_2D();

module high_top_2D()
{
    color("blue") translate([0,60]) difference()
    {
        {
            square([pb_size_x,60*2]);
        }
        {
            //screen hole
            translate([pb_size_x/2 -10 ,60+30])
            {
                square([screen_size_x,screen_size_y],center=true);
                translate([0,-screen_size_y/2]) square([12.5,8],center=true);
                translate([0,screen_size_y/2]) square([17,8],center=true);
                translate([11.75,11.75]) circle(d=screenHole);
                translate([-11.75,11.75]) circle(d=screenHole);
                translate([11.75,-11.75]) circle(d=screenHole);
                translate([-11.75,-11.75]) circle(d=screenHole);
            }

            translate([pb_size_x/2 - 40,60+30]) circle(d=rotaryHole,center=true);
            translate([pb_size_x/2 + 20,60+30]) circle(d=swHole,center=true);
            translate([pb_size_x/2 +40,60+30]) circle(d=swHole,center=true);

            //finger hole
            translate([0,60+30-(20/2)]) square([thickness,20]); //left
            translate([pb_size_x-thickness,60+30-(20/2)]) square([thickness,20]); //right
            translate([(pb_size_x/2)-(pb_size_x/6),60+60-thickness]) square([pb_size_x/3,thickness]);//top


            translate([fs_side_dist,20]) circle(d=fsHole);
            translate([pb_size_x-fs_side_dist,20]) circle(d=fsHole);
            translate([fs_side_dist,60-20]) circle(d=ledHole);
            translate([pb_size_x-fs_side_dist,60-20]) circle(d=ledHole);

            //finger hole
            translate([0,30-(20/2)]) square([thickness,20]); //left
            translate([pb_size_x-thickness,30-(20/2)]) square([thickness,20]); //right
            translate([(pb_size_x/2)-(pb_size_x/6),0]) square([pb_size_x/3,thickness]) ;
            //M4 holes
            translate([thickness+12,60-9]) circle(d=M4Hole);
            translate([thickness+12,60+9]) circle(d=M4Hole);
            translate([pb_size_x-thickness-12,60-9]) circle(d=M4Hole);
            translate([pb_size_x-thickness-12,60+9]) circle(d=M4Hole);
        }
    }
}

//top of low step
module low_top_3D() 
{
    linear_extrude(height=thickness) low_top_2D();
}

module low_top_2D()
{
    difference()
    {
        union()
        {
            square([pb_size_x,60]);
            //finger
            translate([(pb_size_x/2)-(pb_size_x/6),60]) square([pb_size_x/3,thickness]);
            //translate([thickness+23,60]) square([25,thickness]);
            //translate([pb_size_x-(thickness+23+25),60]) square([25,thickness]);
        }
        {
            translate([fs_side_dist,20]) circle(d=fsHole);
            translate([pb_size_x-fs_side_dist,20]) circle(d=fsHole);
            translate([fs_side_dist,60-20]) circle(d=ledHole);
            translate([pb_size_x-fs_side_dist,60-20]) circle(d=ledHole);
            //finger hole
            translate([0,30-(20/2)]) square([thickness,20]); //left
            translate([pb_size_x-thickness,30-(20/2)]) square([thickness,20]); //right
            translate([(pb_size_x/2)-(pb_size_x/6),0]) square([pb_size_x/3,thickness]);
            //M4Hole
            translate([pb_size_x/2-7,12+thickness]) circle(d=M4Hole);
            translate([pb_size_x/2+7,12+thickness]) circle(d=M4Hole);
            translate([pb_size_x/2-7,60-12]) circle(d=M4Hole);
            translate([pb_size_x/2+7,60-12]) circle(d=M4Hole);

            translate([12+thickness,60-8]) circle(d=M4Hole);
            translate([pb_size_x-12-thickness,60-8]) circle(d=M4Hole);
        }
    }
}

module plastic_cover_3D()
{
    linear_extrude(height=3)  plastic_cover_2D();
}
module plastic_cover_2D()
{
    difference()
    {
       {
           square([pb_size_x,60]);
       }
       {
           translate([pb_size_x/2 -10 ,60-30])
           {
               translate([2-screen_size_x/2,2-screen_size_y/2]) circle(d=screenHole);
               translate([2-screen_size_x/2,screen_size_y/2-2]) circle(d=screenHole);
               translate([screen_size_x/2-2,2-screen_size_y/2]) circle(d=screenHole);
               translate([screen_size_x/2-2,screen_size_y/2-2]) circle(d=screenHole);
           }
       }
   }
}

module low_front_3D()
{
    linear_extrude(height=thickness) low_front_2D();
}
 
 module low_front_2D()    
{
    difference() {
        union(){
            translate([thickness,0]) square([pb_size_x-2*thickness, low_step_height]);
        //top finger
            translate([(pb_size_x/2)-(pb_size_x/6),low_step_height]) square([pb_size_x/3,thickness]);
        //bottom finger
            translate([(pb_size_x/2)-(pb_size_x/6),-thickness]) square([pb_size_x/3,thickness]);
        //side fingers
            translate([0,low_step_height/3]) square([thickness, low_step_height/3]);
            translate([pb_size_x-thickness,low_step_height/3]) square([thickness, low_step_height/3]);
        }
        {
            //M4 holes
            translate([8+thickness,12]) circle(d=M4Hole);
            translate([pb_size_x-8-thickness,12]) circle(d=M4Hole);
            translate([pb_size_x/2-7, low_step_height-12]) circle(d=M4Hole);
            translate([pb_size_x/2+7, low_step_height-12]) circle(d=M4Hole);
        }
    }
}

module high_front_3D()
{
    linear_extrude(height=thickness) high_front_2D();
}
 
module high_front_2D()
{   
    module cable_hole()
    {
        polygon(points=[[-20,0],[-10,10],[10,10],[20,0]]);
    }
    difference()
    {
        union()
        {
            translate([thickness,0]) square([pb_size_x-2*thickness,high_step_height]);
            //translate([(pb_size_x/2)-(40/2),high_step_height]) square([40,thickness]);
            translate([0,low_step_height/3]) square([thickness, low_step_height/3]);
            translate([pb_size_x-thickness,low_step_height/3]) square([thickness, low_step_height/3]);
            translate([(pb_size_x/2)-(pb_size_x/6),high_step_height]) square([pb_size_x/3,thickness]);
        }
        {
            translate([(pb_size_x/2)-(pb_size_x/6),low_step_height]) square([pb_size_x/3,thickness]);
            //translate([thickness+23,low_step_height]) square([25,thickness]);
            //translate([pb_size_x-(thickness+23+25),low_step_height]) square([25,thickness]);
            //hole for cable
            translate([fs_side_dist,0]) cable_hole();
            translate([pb_size_x-fs_side_dist,0]) cable_hole();
            //M4 holes
            translate([pb_size_x/2-7,low_step_height-12]) circle(d=M4Hole);
            translate([pb_size_x/2+7,low_step_height-12]) circle(d=M4Hole);
            translate([12+thickness,high_step_height-8]) circle(d=M4Hole);
            translate([pb_size_x-12-thickness,high_step_height-8]) circle(d=M4Hole);
        }
    }
}

module rear_3D()
{
    linear_extrude(height=thickness) rear_2D();
}
    
module rear_2D()
{
    difference(){
        union(){
            translate([thickness,0]) square([pb_size_x-2*thickness,high_step_height]);
            //side fingers
            translate([0,high_step_height/3]) square([thickness, high_step_height/3]);
            translate([pb_size_x-thickness,high_step_height/3]) square([thickness, high_step_height/3]);
            //top finger
            translate([(pb_size_x/2)-(pb_size_x/6),high_step_height]) square([pb_size_x/3,thickness]);
            //bottom finger
            translate([(pb_size_x/2)-(pb_size_x/6),-thickness]) square([pb_size_x/3,thickness]);
        }
        {
            //M4 holes
            translate([12+thickness,high_step_height-8]) circle(d=M4Hole);
            translate([pb_size_x-12-thickness,high_step_height-8]) circle(d=M4Hole);
            translate([8+thickness,12]) circle(d=M4Hole);
            translate([pb_size_x-8-thickness,12]) circle(d=M4Hole);
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
        union(){
            square([low_step_height,60]);
            translate([0,60]) square([high_step_height,pb_size_y-60]);
            //top finger
            translate([low_step_height,30-(20/2)]) square([thickness,20]);
            translate([high_step_height,60+30-(20/2)]) square([thickness,20]);
            translate([high_step_height,60+60+30-(20/2)]) square([thickness,20]);
            //bottom finger
            translate([-thickness,30-(20/2)]) square([thickness,20]);
            translate([-thickness,60+30-(20/2)]) square([thickness,20]);
            translate([-thickness,60+60+30-(20/2)]) square([thickness,20]);
        }
        {
            translate([low_step_height/3,0]) square([low_step_height/3,thickness]);
            translate([low_step_height/3,60]) square([low_step_height/3,thickness]);
            translate([high_step_height/3,pb_size_y-thickness]) square([high_step_height/3, thickness,]);
            //M4 holes
            translate([low_step_height-12,60-8]) circle(d=M4Hole);
            translate([high_step_height-8,60+12+thickness]) circle(d=M4Hole);
            translate([high_step_height-12,60+60-9]) circle(d=M4Hole);
            translate([high_step_height-12,60+60+9]) circle(d=M4Hole);
            translate([high_step_height-8,60*3-12-thickness]) circle(d=M4Hole);
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
        union(){
            square([low_step_height,60]);
            translate([0,60]) square([high_step_height,pb_size_y-60]);
            //top finger
            translate([low_step_height,30-(20/2)]) square([thickness,20]);
            translate([high_step_height,60+30-(20/2)]) square([thickness,20]);
            translate([high_step_height,60+60+30-(20/2)]) square([thickness,20]);
            //bottom finger
            translate([-thickness,30-(20/2)]) square([thickness,20]);
            translate([-thickness,60+30-(20/2)]) square([thickness,20]);
            translate([-thickness,60+60+30-(20/2)]) square([thickness,20]);
        }
        {
            //finger hole
            translate([low_step_height/3,0]) square([low_step_height/3,thickness]);
            translate([low_step_height/3,60]) square([low_step_height/3,thickness]);
            translate([high_step_height/3,pb_size_y-thickness]) square([high_step_height/3, thickness,]);
            //M4 holes
            translate([low_step_height-12,60-8]) circle(d=M4Hole);
            translate([high_step_height-8,60+12+thickness]) circle(d=M4Hole);
            translate([high_step_height-12,60+60-9]) circle(d=M4Hole);
            translate([high_step_height-12,60+60+9]) circle(d=M4Hole);
            translate([high_step_height-8,60*3-12-thickness]) circle(d=M4Hole);
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
            square([pb_size_x,pb_size_y]);
        }
        {
            //front finger hole
            translate([(pb_size_x/2)-(pb_size_x/6),0]) square([pb_size_x/3,thickness]);
            //rear finger hole
            translate([(pb_size_x/2)-(pb_size_x/6),pb_size_y-thickness]) square([pb_size_x/3,thickness]);
            //left side fingers
            translate([0,30-(20/2)]) square([thickness,20]);
            translate([0,60+30-(20/2)]) square([thickness,20]);
            translate([0,60+60+30-(20/2)]) square([thickness,20]);
            //right side fingers
            translate([pb_size_x-thickness,30-(20/2)]) square([thickness,20]);
            translate([pb_size_x-thickness,60+30-(20/2)]) square([thickness,20]);
            translate([pb_size_x-thickness,60+60+30-(20/2)]) square([thickness,20]);
            //M4 holes
            translate([8+thickness,12+thickness]) circle(d=M4Hole);
            translate([pb_size_x-8-thickness,12+thickness]) circle(d=M4Hole);
            translate([8+thickness,pb_size_y-12-thickness]) circle(d=M4Hole);
            translate([pb_size_x-8-thickness,pb_size_y-12-thickness]) circle(d=M4Hole);
        }
    }
}

//2D projection
union(){
    low_top_2D();
    translate([0,10]) high_top_2D();
    
    translate([0,-35]) low_front_2D();
    translate([145,-40]) high_front_2D();
    
    translate([180,255]) rotate([0,0,90]) left_2D();
    translate([180,200]) rotate([0,0,90]) right_2D();

    translate([145,10]) bottom_2D();
}

//translate([-pb_size_x/2,-pb_size_y/2])
//box in 3D
*union(){
    //color("red",0.5) cube([pb_size_x,pb_size_y,pb_size_z]);
    color("blue",alpha=0.2) translate([0,0,low_step_height]) low_top_3D();
    translate([0,0,high_step_height])  high_top_3D();

    translate([0,thickness,0]) rotate([90,0,0]) low_front_3D();
    color("green",alpha=0.5) translate([0,60+thickness,0]) rotate([90,0,0]) high_front_3D();
    color("green") translate([0,pb_size_y,0]) rotate([90,0,0]) rear_3D();

    color("red",alpha=0.5) translate([thickness,0,0]) rotate([0,-90,0]) left_3D();
    color("red",alpha=0.5) translate([pb_size_x,0,0]) rotate([0,-90,0]) right_3D();

    color([0.8,0.8,0.8,0.3]) translate([0,120,high_step_height+thickness]) plastic_cover_3D();

    color("grey",alpha=0.5) translate([0,0,-thickness]) bottom_3D();
}

//footswitch
*%union(){
    translate([fs_side_dist,20,0]) rotate([0,0,90]) footswitch();
    translate([pb_size_x-fs_side_dist,20,0]) rotate([0,0,90]) footswitch();
    translate([fs_side_dist,60+20,high_step_height-low_step_height]) rotate([0,0,0]) footswitch();
    translate([pb_size_x-fs_side_dist,60+20,high_step_height-low_step_height]) rotate([0,0,90]) footswitch();
}


//angle bracket
*%union()
{
    translate([pb_size_x/2,thickness,low_step_height]) rotate([180,0,0]) angle_bracket_double();
    translate([pb_size_x/2,60,low_step_height]) rotate([90,0,0]) angle_bracket_double();
    //translate([pb_size_x/2,60+thickness,high_step_height]) rotate([180,0,0]) angle_bracket_double();
    //translate([40,60,low_step_height]) rotate([90,0,0]) angle_bracket();
    //translate([pb_size_x-40,60,low_step_height]) rotate([90,0,0]) angle_bracket();

    //translate([pb_size_x/2,60+thickness,high_step_height]) rotate([180,0,0]) angle_bracket_double();

    translate([thickness,52,low_step_height])rotate([90,0,90]) angle_bracket_simple();
    translate([pb_size_x-thickness,52,low_step_height])rotate([90,0,-90]) angle_bracket_simple();
    translate([thickness,51+60,high_step_height])rotate([90,0,90]) angle_bracket_simple();
    translate([pb_size_x-thickness,51+60,high_step_height])rotate([90,0,-90]) angle_bracket_simple();

    translate([thickness,9+120,high_step_height])rotate([90,0,90]) angle_bracket_simple();
    translate([pb_size_x-thickness,9+120,high_step_height]) rotate([90,0,-90]) angle_bracket_simple();

    //translate([thickness+8,3*60-thickness,high_step_height]) rotate([90,0,0]) angle_bracket_simple();
    //translate([pb_size_x-thickness-8,3*60-thickness,high_step_height]) rotate([90,0,0]) angle_bracket_simple();

    translate([thickness+8,thickness,0]) rotate([0,0,180]) angle_bracket_simple();
    translate([pb_size_x-(thickness+8),thickness,0]) rotate([0,0,180]) angle_bracket_simple();

    translate([thickness+8,pb_size_y-thickness,0]) rotate([0,0,0]) angle_bracket_simple();
    translate([pb_size_x-(thickness+8),pb_size_y-thickness,0]) rotate([0,0,0]) angle_bracket_simple();

    translate([thickness,60+thickness,high_step_height-8]) rotate([0,-90,180]) angle_bracket_simple();
    translate([pb_size_x-thickness,60+thickness,high_step_height-8]) rotate([0,90,180]) angle_bracket_simple();

    translate([thickness,180-thickness,high_step_height-8]) rotate([0,+90,0]) angle_bracket_simple();
    translate([pb_size_x-thickness,180-thickness,high_step_height-8]) rotate([0,-90,0]) angle_bracket_simple();
}
