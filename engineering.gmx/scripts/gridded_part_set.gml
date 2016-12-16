///gridded_part_set(grid, x, y);
var l_grid = argument0;
var l_x = argument1;
var l_y = argument2;
if (l_grid)
{
    if ((l_x >= 0) && ((l_x + width - 1) < l_grid.width) && (l_y >= 0) && ((l_y + height - 1) < l_grid.height))
    {
        var crnt_cell = l_grid.ship_grid[# l_x, l_y];
        if (gridded_part_test_permission(l_grid, l_x, l_y) && gridded_part_test_free(l_grid, l_x, l_y))
        {
            gridded_part_fill(l_grid, l_x, l_y);
            x = l_grid.x + (l_x + width / 2) * l_grid.cell_size;
            y = l_grid.y + (l_y + height / 2) * l_grid.cell_size;
            dragging = 0;
            event_perform(ev_other, ev_user0);
            power_recalculation(l_grid.ship_grid);
            return 1;
        }
    }
}
return 0;