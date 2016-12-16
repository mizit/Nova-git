///ship_grid_fill(ds_grid);
var l_grid = argument0;
for (var l_i = 0; l_i < ds_grid_width(l_grid); l_i++)
{
    for (var l_j = 0; l_j < ds_grid_height(l_grid); l_j++)
    {
        l_grid[# l_i, l_j] = cell_constructor(l_i, l_j);
    }
}
