$fn=80;
//Holes diameter
fsHole=12;//spec 12, measured 11.8 on fs
ledHole=7.8;//spec 8? measured 7.6 on Led
rotaryHole=8;//spec 8 ? measured 7.8 on rotary coder
swHole=7;//spec 7, measured 6.8 on swHole
screenHole=2.5;//spec 2.5 ? measured 2.4 on screw
M4Hole=4;//spec 4, measured 3.9 on screw
//USBHole=3;//spec 3 ? measured 2.9 on USb screw


thickness=3;

//screen_size_x=26;
//screen_size_y=19;
screen_size_x =28;//measured 26.65, pcb 28mm
screen_size_y =19.4;//measured 19.3


pb_size_x = 140;
pb_size_y = 180;
pb_size_z = 45;

low_step_height= 30-thickness;
high_step_height= low_step_height +16+thickness;

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
            translate([pb_size_x/2-35,120-thickness-12]) circle(d=M4Hole);
            translate([pb_size_x/2+30-7,120-thickness-12]) circle(d=M4Hole);
            translate([pb_size_x/2+30+7,120-thickness-12]) circle(d=M4Hole);
            translate([thickness+12,60+20-7]) circle(d=M4Hole);
            translate([thickness+12,60+20+7]) circle(d=M4Hole);
            translate([pb_size_x-thickness-12,60+20-7]) circle(d=M4Hole);
            translate([pb_size_x-thickness-12,60+20+7]) circle(d=M4Hole);
            translate([thickness+12,60-15-7]) circle(d=M4Hole);
            translate([thickness+12,60-15+7]) circle(d=M4Hole);
            translate([pb_size_x-thickness-12,60-15-7]) circle(d=M4Hole);
            translate([pb_size_x-thickness-12,60-15+7]) circle(d=M4Hole);
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
            translate([pb_size_x/2+15.5-7,12+thickness]) circle(d=M4Hole);
            translate([pb_size_x/2+15.5+7,12+thickness]) circle(d=M4Hole);
            translate([pb_size_x/2-15.5-7,12+thickness]) circle(d=M4Hole);
            translate([pb_size_x/2-15.5+7,12+thickness]) circle(d=M4Hole);
            translate([pb_size_x/2-18-7,60-12]) circle(d=M4Hole);
            translate([pb_size_x/2-18+7,60-12]) circle(d=M4Hole);
            translate([pb_size_x/2+18-7,60-12]) circle(d=M4Hole);
            translate([pb_size_x/2+18+7,60-12]) circle(d=M4Hole);
            translate([12+thickness,60-15-7]) circle(d=M4Hole);
            translate([12+thickness,60-15+7]) circle(d=M4Hole);
            translate([pb_size_x-12-thickness,60-15-7]) circle(d=M4Hole);
            translate([pb_size_x-12-thickness,60-15+7]) circle(d=M4Hole);
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
            translate([pb_size_x/2-15.5-7, low_step_height-12]) circle(d=M4Hole);
            translate([pb_size_x/2-15.5+7, low_step_height-12]) circle(d=M4Hole);
            translate([pb_size_x/2+15.5-7, low_step_height-12]) circle(d=M4Hole);
            translate([pb_size_x/2+15.5+7, low_step_height-12]) circle(d=M4Hole);
        }
    }
}

module high_front_3D()
{
    linear_extrude(height=thickness) high_front_2D();
}
 
module high_front_2D()
{   
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
            translate([fs_side_dist-5,low_step_height/2]) square([10,5], center=true);
            translate([pb_size_x-fs_side_dist+5,low_step_height/2]) square([10,5], center=true);
            //M4 holes
            translate([pb_size_x/2-18-7,low_step_height-12]) circle(d=M4Hole);
            translate([pb_size_x/2-18+7,low_step_height-12]) circle(d=M4Hole);
            translate([pb_size_x/2+18-7,low_step_height-12]) circle(d=M4Hole);
            translate([pb_size_x/2+18+7,low_step_height-12]) circle(d=M4Hole);
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
    module usb_clearance() {
            square([12,12], center=true);
            translate([-15,0]) circle(d=3.3);
            translate([15,0]) circle(d=3.3);
    }
    module midi_cutout() {
        translate([-11.1,0]) circle(d=3.3);
        translate([11.1,0]) circle(d=3.3);
        circle(d=16);
    }
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
            translate([pb_size_x/2-35,high_step_height-12]) circle(d=M4Hole);
            translate([pb_size_x/2+30-7,high_step_height-12]) circle(d=M4Hole);
            translate([pb_size_x/2+30+7,high_step_height-12]) circle(d=M4Hole);

            translate([95,13]) usb_clearance();
            translate([35,13]) rotate(-35) midi_cutout();
            translate([58,13]) rotate(-35) midi_cutout();
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
            translate([low_step_height-12,45-7]) circle(d=M4Hole);
            translate([low_step_height-12,45+7]) circle(d=M4Hole);
            translate([high_step_height-8,60+12+thickness]) circle(d=M4Hole);
            translate([high_step_height-12,120-15-7]) circle(d=M4Hole);
            translate([high_step_height-12,120-15+7]) circle(d=M4Hole);
            translate([high_step_height-12,120+20-7]) circle(d=M4Hole);
            translate([high_step_height-12,120+20+7]) circle(d=M4Hole);
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
            translate([low_step_height-12,45-7]) circle(d=M4Hole);
            translate([low_step_height-12,45+7]) circle(d=M4Hole);
            translate([high_step_height-8,60+12+thickness]) circle(d=M4Hole);
            translate([high_step_height-12,120-15-7]) circle(d=M4Hole);
            translate([high_step_height-12,120-15+7]) circle(d=M4Hole);
            translate([high_step_height-12,120+20-7]) circle(d=M4Hole);
            translate([high_step_height-12,120+20+7]) circle(d=M4Hole);
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

