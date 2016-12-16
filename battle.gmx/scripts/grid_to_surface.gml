///grid_to_surface(grid);
var l_grid = argument0;
var l_size = 16;
var l_surf = surface_create(ds_grid_width(l_grid) * l_size, 
ds_grid_height(l_grid) * l_size);
surface_set_target(l_surf);

for (var l_i = 0; l_i < ds_grid_width(l_grid); l_i++)
{
    for (var l_j = 0; l_j < ds_grid_height(l_grid); l_j++)
    {
        if (l_grid[# l_i, l_j] == 1)
        {
            draw_set_color(c_black);
            draw_rectangle(l_size * l_i, l_size * l_j, l_size * (l_i + 1), l_size * (l_j + 1), 0);
            draw_set_colour(c_white);
            draw_rectangle(l_size * l_i, l_size * l_j, l_size * (l_i + 1), l_size * (l_j + 1), 1); 
        }
    }
}
surface_reset_target();
return l_surf;
