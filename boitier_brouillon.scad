use <footswitch.scad>;

fsHole=12;//diameter
ledHole=5;//diameter

screen_size_x=26;
screen_size_y=19;

pb_size_x = 120;
pb_size_y = 180;
pb_size_z = 45;

//translate([-pb_size_x/2,-pb_size_y/2])
{
    //color("red",0.5) cube([pb_size_x,pb_size_y,pb_size_z]);
    
    //low fs 
    color("blue",alpha=0.5) translate([0,0,20]) difference()
    {
        {
            cube([pb_size_x,60,5]);
        }
        {
            translate([20,20,2.5]) cylinder(d=fsHole,h=20,center=true);
            translate([pb_size_x-20,20,2.5]) cylinder(d=fsHole,h=20,center=true);
            translate([20,60-20,2.5]) cylinder(d=ledHole,h=20,center=true);
            translate([pb_size_x-20,60-20,2.5]) cylinder(d=ledHole,h=20,center=true); 
        }
    }
    //high fs
    color("blue") translate([0,60,20+15]) difference()
    {
        {
            cube([pb_size_x,60,5]);
        }
        translate([0,0,0])
        {
            translate([20,20,2.5]) cylinder(d=fsHole,h=20,center=true);
            translate([pb_size_x-20,20,2.5]) cylinder(d=fsHole,h=20,center=true);
            translate([20,60-20,2.5]) cylinder(d=ledHole,h=20,center=true);
            translate([pb_size_x-20,60-20,2.5]) cylinder(d=ledHole,h=20,center=true);

        }
    }
    
    //
     translate([0,60+60,20+15]) difference()
    {
        {
            cube([pb_size_x,60,5]);
        }
        {
                        //screen hole
            translate([pb_size_x/2 ,60-25,2.5]) cube([screen_size_x,screen_size_y,30],center=true);
            translate([pb_size_x/2 -30,60-25,2.5]) cylinder(d=5,h=20,center=true);
            translate([pb_size_x/2 - 10,60-45,2.5]) cylinder(d=5,h=20,center=true);
            translate([pb_size_x/2 +10,60-45,2.5]) cylinder(d=5,h=20,center=true);
            }
    }
    
    %cube([pb_size_x,5, 20]);
    
    
    color("green") translate([0,60,0]) cube([pb_size_x,5,20+15]);
    color("green") translate([0,pb_size_y-5,0]) cube([pb_size_x,5,20+15]);
    
    color("red",alpha=0.2) union()
    {
        cube([5,60,20]);
        translate([0,60,0]) cube([5,pb_size_y-60,20+15]);
    }
    
     translate([pb_size_x-5,0,0]) color("red",alpha=0.2) union()
    {
        cube([5,60,20]);
        translate([0,60,0]) cube([5,pb_size_y-60,20+15]);
    }  
}

translate([20,20,-5]) footswitch();

