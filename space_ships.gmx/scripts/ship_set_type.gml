///ships_set_type(shipt, type);
var l_ship = argument0;
var l_type = argument1;
if (l_ship.sprite_index == l_type)
{
    return 0;
}
l_ship.sprite_index = l_type;

switch (l_type)
{
    case s_bazar:
    {
        var tmp_dock = instance_create(x, y, obj_dock);
        tmp_dock.xoff = 194;
        tmp_dock.yoff = 7;
        tmp_dock.owner = l_ship;
        tmp_dock.angle_off = 0;
        ds_list_add(l_ship.my_docks, tmp_dock);
        var tmp_dock = instance_create(x, y, obj_dock);
        tmp_dock.xoff = -192;
        tmp_dock.yoff = 5;
        tmp_dock.owner = l_ship;
        tmp_dock.angle_off = 180;
        ds_list_add(l_ship.my_docks, tmp_dock);
        var tmp_dock = instance_create(x, y, obj_dock);
        tmp_dock.xoff = 50;
        tmp_dock.yoff = 189;
        tmp_dock.owner = l_ship;
        tmp_dock.angle_off = 75;
        ds_list_add(l_ship.my_docks, tmp_dock);
        break;
    }
    default:
    {
        var tmp_dock = instance_create(x, y, obj_dock);
        tmp_dock.xoff = 45;
        tmp_dock.yoff = 0;
        tmp_dock.owner = l_ship;
        tmp_dock.angle_off = 0;
        ds_list_add(l_ship.my_docks, tmp_dock);
        break;
    }
}
