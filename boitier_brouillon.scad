fsHole=12;//diameter
ledHole=5;//diameter

screen_size_x=26;
screen_size_y=19;

pb_size_x = 120;
pb_size_y = 200;
pb_size_z = 45;

translate([-pb_size_x/2,-pb_size_y/2])
{
    *color("red",0.5) cube([pb_size_x,pb_size_y,pb_size_z]);
    
    //low fs 
    translate([0,pb_size_y-60,20]) difference()
    {
        {
            cube([pb_size_x,60,5]);
        }
        {
            translate([20,60-20,2.5]) cylinder(r=fsHole/2,h=20,center=true);
            translate([pb_size_x-20,60-20,2.5]) cylinder(r=fsHole/2,h=20,center=true);
            translate([20,20,2.5]) cylinder(r=ledHole/2,h=20,center=true);
            translate([pb_size_x-20,20,2.5]) cylinder(r=ledHole/2,h=20,center=true);
            
        }
    }
    //high fs
    translate([0,pb_size_y-200,20+15]) difference()
    {
        {
            cube([pb_size_x,140,5]);
        }
        translate([0,pb_size_y-60-60,0])
        {
            translate([20,60-20,2.5]) cylinder(r=fsHole/2,h=20,center=true);
            translate([pb_size_x-20,60-20,2.5]) cylinder(r=fsHole/2,h=20,center=true);
            translate([20,20,2.5]) cylinder(r=ledHole/2,h=20,center=true);
            translate([pb_size_x-20,20,2.5]) cylinder(r=ledHole/2,h=20,center=true);
            //screen hole
            translate([pb_size_x/2 +10,-40,2.5]) cube([screen_size_x,screen_size_y,30],center=true);
            translate([pb_size_x/2 -15,-40,2.5]) cylinder(r=7/2,h=20,center=true);
        }
    }
    
}
