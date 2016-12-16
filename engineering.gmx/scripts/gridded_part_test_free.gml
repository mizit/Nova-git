///gridded_part_test_free(ds_grid, x, y);
var l_grid = argument0;
var l_x = argument1;
var l_y = argument2;
for (var l_i = 0; l_i < width; l_i++)
{
    for (var l_j = 0; l_j < height; l_j++)
    {
        var l_cell = l_grid.ship_grid[# l_x + l_i, l_y + l_j];
        if (l_cell[| CELL_OBJECT] != noone)
        {
            return false;
        }
    }
}
return true;
