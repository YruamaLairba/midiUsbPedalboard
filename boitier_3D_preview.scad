use <footswitch.scad>;
use <angle_bracket.scad>;
use <USB_connector.scad>;
use <midi_connector.scad>;
include <boitier_modules.scad>

//the enclosure
union()
{
    top_3D();
}

//angle bracket
%union()
{
}

//footswitch
%union(){
}

//connector
