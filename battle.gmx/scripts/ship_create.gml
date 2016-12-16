///ship_create(name);
var l_ship = ds_list_create();
l_ship[| SHIP_SPRITE] = s_ship_original;
l_ship[| SHIP_NAME] = argument0;
var l_grid = instance_create(0, 0, obj_grid);
l_grid.name = argument0;
l_ship[| SHIP_GRID] = l_grid;
return l_ship;
