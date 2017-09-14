fsHole=12;//diameter
ledHole=5;//diameter

screen_size_x=19;
screen_size_y=26;

pb_size_x = 200;
pb_size_y = 120;
pb_size_z = 45;

translate([-pb_size_x/2,-pb_size_y/2])
{
    *color("red",0.5) cube([pb_size_x,pb_size_y,pb_size_z]);
    
    //low fs 
    translate([pb_size_x-60,0,20]) difference()
    {
        {
            cube([60,pb_size_y,5]);
        }
        {
            translate([60-20,20,2.5]) cylinder(r=fsHole/2,h=20,center=true);
            translate([60-20,pb_size_y-20,2.5]) cylinder(r=fsHole/2,h=20,center=true);
            translate([20,20,2.5]) cylinder(r=ledHole/2,h=20,center=true);
            translate([20,pb_size_y-20,2.5]) cylinder(r=ledHole/2,h=20,center=true);
            
        }
    }
    //high fs
    translate([pb_size_x-200,0,20+15]) difference()
    {
        {
            cube([140,pb_size_y,5]);
        }
        translate([pb_size_x-60-60,0,0])
        {
            translate([60-20,20,2.5]) cylinder(r=fsHole/2,h=20,center=true);
            translate([60-20,pb_size_y-20,2.5]) cylinder(r=fsHole/2,h=20,center=true);
            translate([20,20,2.5]) cylinder(r=ledHole/2,h=20,center=true);
            translate([20,pb_size_y-20,2.5]) cylinder(r=ledHole/2,h=20,center=true);
            //screen hole
            translate([-40,pb_size_y/2 +10,2.5]) cube([screen_size_x,screen_size_y,30],center=true);
            translate([-40,pb_size_y/2 -15,2.5]) cylinder(r=7/2,h=20,center=true);
        }
    }
    
}
