///part_check_electricity(item);
var l_item = argument0;
if (obj_on.image_index == 0)
{
    return 0;
}
if !((l_item.grd_x < 0) || (l_item.grd_y < 0))
{
    var l_list = obj_grid.ship_grid[# l_item.grd_x, l_item.grd_y];
    l_list = l_list[| CELL_PS_LIST];
    for (var l_i = 0; l_i < ds_list_size(l_list); l_i++)
    {
        if !(l_list[| l_i].shut_down)
        {
            l_item.charged = 1;
            l_item.charge_cnt = 0;
            return 1;
        }
    }
    if (l_item.charge_cnt <= l_item.capacitor)
    {
        l_item.charge_cnt++;
        return 1;
    }
    else
    {
        return 0;
    }
}
return 0;
