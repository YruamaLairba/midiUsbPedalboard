use <footswitch.scad>;

fsHole=12;//diameter
ledHole=5;//diameter

thickness=5;

//screen_size_x=26;
//screen_size_y=19;
screen_size_x =28;
screen_size_y =28;

pb_size_x = 120;
pb_size_y = 180;
pb_size_z = 45;

module high_top()
linear_extrude(height=thickness) 
{
    color("blue") translate([0,60])difference()
    {
        {
            square([pb_size_x,60]);
        }
        {
            translate([20,20]) circle(d=fsHole);
            translate([pb_size_x-20,20]) circle(d=fsHole);
            translate([20,60-20]) circle(d=ledHole);
            translate([pb_size_x-20,60-20]) circle(d=ledHole);           
        }
    }
    translate([0,60+60]) difference()
    {
        {
            square([pb_size_x,60]);
        }
        {
                        //screen hole
            translate([pb_size_x/2 -10 ,60-30,2.5]) square([screen_size_x,screen_size_y],center=true);
            translate([pb_size_x/2 - 40,60-30,2.5]) circle(d=5,center=true);
            translate([pb_size_x/2 + 20,60-30,2.5]) circle(d=5,center=true);
            translate([pb_size_x/2 +40,60-30,2.5]) circle(d=5,center=true);
        }
    }
}

module low_top() //top of low step
{
    linear_extrude(height=thickness) difference()
    {
        {
            square([pb_size_x,60]);
        }
        {
            translate([20,20]) circle(d=fsHole);
            translate([pb_size_x-20,20]) circle(d=fsHole);
            translate([20,60-20]) circle(d=ledHole);
            translate([pb_size_x-20,60-20]) circle(d=ledHole); 
            //finger hole
            translate([0,30-(20/2)]) square([thickness,20]); //left
            translate([pb_size_x-thickness,30-(20/2)]) square([thickness,20]); //right
            translate([(pb_size_x/2)-(40/2),0]) square([40,thickness]);
        }
    }
}
 
module plastic_cover()
{
    linear_extrude(height=2) difference()
    {
       {
           square([pb_size_x,60]);
       }
       { 
           translate([pb_size_x/2 -10 ,60-30])
           {
               translate([2-screen_size_x/2,2-screen_size_y/2]) circle(d=2);
               translate([2-screen_size_x/2,screen_size_y/2-2]) circle(d=2);
               translate([screen_size_x/2-2,2-screen_size_y/2]) circle(d=2);
               translate([screen_size_x/2-2,screen_size_y/2-2]) circle(d=2);
           }
       }
   }
}

module low_front()
{
    linear_extrude(height=thickness)
   {
       square([pb_size_x-2*thickness, 20]);
       translate([(pb_size_x/2-thickness)-(40/2),20]) square([40,thickness]);
   }
}

module high_front()
{
    linear_extrude(height=thickness) square([pb_size_x-2*thickness,20+15]);
}

module rear()
{
    linear_extrude(height=thickness) square([pb_size_x-2*thickness,20+15]);
}

module left()
{
    linear_extrude(height=thickness)
    {
        square([20,60]);
        translate([0,60]) square([20+15,pb_size_y-60]);
        //finger
        translate([20,30-(20/2)]) square([thickness,20]);
    }
}

module right()
{
    linear_extrude(height=thickness)
    {
        square([20,60]);
        translate([0,60]) square([20+15,pb_size_y-60]);
        //finger
        translate([20,30-(20/2)]) square([thickness,20]);
    }
}


//translate([-pb_size_x/2,-pb_size_y/2])
{
    //color("red",0.5) cube([pb_size_x,pb_size_y,pb_size_z]);
    color("blue",alpha=0.2) translate([0,0,20]) low_top();
    translate([0,0,20+15])  high_top();
    color([0.8,0.8,0.8,0.3]) translate([0,120,20+15+thickness]) plastic_cover();
    translate([thickness,thickness,0]) rotate([90,0,0]) low_front();
    color("green") translate([thickness,60+thickness,0]) rotate([90,0,0]) high_front();
    color("green") translate([thickness,pb_size_y,0]) rotate([90,0,0]) rear();
    
    color("red",alpha=0.2) translate([thickness,0,0]) rotate([0,-90,0]) left();
    color("red",alpha=0.2) translate([pb_size_x,0,0]) rotate([0,-90,0]) right();
    
    

}

%translate([20,20,-4]) footswitch();

