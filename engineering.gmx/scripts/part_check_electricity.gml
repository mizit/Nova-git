///part_check_electricity(item);
var l_item = argument0;
if !((l_item.grd_x < 0) || (l_item.grd_y < 0))
{
    var l_list = obj_grid.ship_grid[# l_item.grd_x, l_item.grd_y];
    l_list = l_list[| CELL_PS_LIST];
    for (var l_i = 0; l_i < ds_list_size(l_list); l_i++)
    {
        if !(l_list[| l_i].shut_down)
        {
            return 1;
        }
    }
    return 0;
}
return 0;
