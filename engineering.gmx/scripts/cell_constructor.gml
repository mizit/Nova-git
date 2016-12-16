///cell_constructor(x, y);
var l_x = argument0;
var l_y = argument1;
var l_list = ds_list_create();
l_list[| CELL_OBJECT] = noone;
l_list[| CELL_ANGLE] = 0;
l_list[| CELL_PERMISSION] = PM_TUBE;
l_list[| CELL_OUTPUTS] = 0;
l_list[| CELL_DRAW] = 0;
l_list[| CELL_PS_LIST] = ds_list_create();
l_list[| CELL_UPDATE] = 0;
l_list[| CELL_X] = l_x;
l_list[| CELL_Y] = l_y;
return l_list;
