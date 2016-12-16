///gridded_part_fill(ds_grid, x, y);
var l_grid = argument0;
var l_x = argument1;
var l_y = argument2;
var l_x_shift = 0, l_y_shift = 0;
while (image_angle < 0)
{
    image_angle += 360;
}
while (image_angle > 360)
{
    image_angle -= 360;
}
if (image_angle == 270)
{
    l_x_shift = grid_size - width;
}
if (image_angle == 180)
{
    l_y_shift = grid_size - height;
}
for (var l_i = 0; l_i < width; l_i++)
{
    for (var l_j = 0; l_j < height; l_j++)
    {
        var l_cell = l_grid.ship_grid[# l_x + l_i, l_y + l_j];
        l_cell[| CELL_OBJECT] = id;
        l_cell[| CELL_ANGLE] = image_angle;
        l_cell[| CELL_OUTPUTS] = grid_outputs[# l_i + l_x_shift, l_j + l_y_shift];
    }
}
var l_cell = l_grid.ship_grid[# l_x, l_y];
l_cell[| CELL_DRAW] = true;
return true;
