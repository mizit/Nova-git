///grid_delete_object(ds_grid, object);
var l_grid = argument0.ship_grid;
var l_obj = argument1;
for (var l_i = 0; l_i < ds_grid_width(l_grid); l_i++)
{
    for (var l_j = 0; l_j < ds_grid_height(l_grid); l_j++)
    {
        var a = l_grid[# l_i, l_j];
        if (a[| CELL_OBJECT] == l_obj)
        {
            a[| CELL_OBJECT] = noone;
            a[| CELL_OUTPUTS] = 0;
        }
    }
}
