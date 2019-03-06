module custom_angle_bracket(
size=[0,0,0],
hole_diameter=4,
thickness=3,
bottom_hole_pos=[0,0],
top_hole_pos=[0,0],
left_hole_pos=[0,0],
front_hole_pos=[0,0]
)
{
    //size_x = size.x;
    //size_y = size.y;
    //size_z = size.z;
    echo("top_hole_pos",top_hole_pos);

    cond_x = (size.x<=0 && top_hole_pos.x>0);
    size_x = size.x>0? size.x : (bottom_hole_pos.x>0 ? bottom_hole_pos.x*2 : 0);
    echo(size_x);
    cond_y = size.y<=0 && bottom_hole_pos.y>0;
    size_y = size.y>0? size.y : (bottom_hole_pos.y>0 ? bottom_hole_pos.y*2 : 0);

    size_z= size.z;

    size=[size_x,size_y,size_z];
    echo(size);

    e=0.1; //epsilon margin
    difference()
    {
        union()
        {
            cube(size);
        }
        union()
        {
            //clearance
            translate([thickness, thickness, thickness])
            cube([size.x,size.y,size.z-2*thickness]);

            //bottom hole
            translate([bottom_hole_pos.x,bottom_hole_pos.y,-e])
            cylinder(h=thickness+2*e,d=hole_diameter);

            //top hole
            translate([top_hole_pos.x,top_hole_pos.y,size.z-thickness-e])
            cylinder(h=thickness+2*e,d=hole_diameter);

            //left hole
            translate([-e,left_hole_pos.x,left_hole_pos.y])
            rotate([0,90,0])
            cylinder(h=thickness+2*e,d=hole_diameter);

            //front hole
            translate([front_hole_pos.x,-e,front_hole_pos.y])
            rotate([-90,0,0])
            cylinder(h=thickness+2*e,d=hole_diameter);
        }
    }
}

size=[20,20,20];
thickness=3;
hole_diameter=4;
holes= [[10,10],[10,10],[10,10],[10,10]];

param =
[for(a=[[size,thickness,hole_diameter],holes]) for(b=a) b];
echo("param",param);

custom_angle_bracket(
    size=[24,24,24],
    hole_diameter=4,
    thickness=3,
    bottom_hole_pos=[10,10],
    top_hole_pos=[10,10],
    left_hole_pos=[10,10],
    front_hole_pos=[10,10]
)
    ;
//custom_angle_bracket(size=[20,20,20],bottom_hole_pos=[10,10]);
