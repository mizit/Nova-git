///part_set(grid, x, y);
var l_grid = argument0;
var l_x = argument1;
var l_y = argument2;
if ((l_x >= 0) && (l_x < l_grid.width) && (l_y >= 0) && (l_y < l_grid.height))
{
    var crnt_cell = l_grid.ship_grid[# l_x, l_y];
    if ((crnt_cell[| CELL_PERMISSION] & need_permission) && (crnt_cell[| CELL_OBJECT] == noone))
    {
        crnt_cell[| CELL_OBJECT] = id;
        crnt_cell[| CELL_ANGLE] = image_angle;
        crnt_cell[| CELL_OUTPUTS] = outputs;
        crnt_cell[| CELL_DRAW] = true;
        x = l_grid.x + (l_x + 0.5) * l_grid.cell_size;
        y = l_grid.y + (l_y + 0.5) * l_grid.cell_size;
        dragging = 0;
        power_recalculation(l_grid.ship_grid);
        return 1;
    }
}
return 0;
