///ship_add(name);
var l_ship = ship_create(argument0);
var l_grid = l_ship[| SHIP_GRID];
l_grid.x = basex + (ds_list_size(my_list) - selector) * shiftx;
l_grid.y = basey;
set_active_grid(l_grid);
ds_list_add(my_list, l_ship);
return l_ship;
