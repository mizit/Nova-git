///cell_constructor(x, y);
var l_x = argument0;
var l_y = argument1;
var l_list = ds_list_create();
l_list[| CELL_X] = l_x;
l_list[| CELL_Y] = l_y;
l_list[| CELL_PERMISSONS] = 0;
return l_list;
