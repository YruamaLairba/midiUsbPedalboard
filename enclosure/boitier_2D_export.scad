include <boitier_modules.scad>

echo("design not ready to export");
union()
{
    m=2;//margin between element
    pos_0=[0,0];
    translate(pos_0)
    front_2D();
    pos_1= pos_0 + [0,pb_size.z+m];
    translate(pos_1)
    top_2D();
    pos_2= pos_1 + [0,pb_size.y+m];
    translate(pos_2)
    rear_2D();
    pos_3= pos_2 + [0,pb_size.z+m];
    translate(pos_3)
    bottom_2D();
    pos_4= pos_3 + [0,pb_size.y+m];
    translate(pos_4)
    left_2D();
    pos_5= pos_4 + [pb_size.y+m,0];
    translate(pos_5)
    right_2D();
}
