///save_grid(grid);
var crnt_grid = argument0;
file_delete("ship_grid.ini");
ini_open("ship_grid.ini");
for (var i = 0; i < 7; i++)
{
    for (var j = 0; j < 7; j++)
    {
        var cell = crnt_grid.ship_grid[# i, j];
        ini_write_real("Ship permissions", string(i) + "x" + string(j), cell[| CELL_PERMISSION]);
    }
}
var part_num = 0;
with (obj_part)
{
    ini_write_string("Part" + string(part_num), "name", object_get_name(object_index));
    ini_write_real("Part" + string(part_num), "angle", image_angle);
    ini_write_real("Part" + string(part_num), "x", floor((x - crnt_grid.x) / crnt_grid.cell_size));
    ini_write_real("Part" + string(part_num), "y", floor((y - crnt_grid.y) / crnt_grid.cell_size));
    part_num++;
}
part_num = 0;
with (obj_gridded_part)
{
    ini_write_string("Gridded Part" + string(part_num), "name", object_get_name(object_index));
    ini_write_real("Gridded Part" + string(part_num), "angle", image_angle);
    ini_write_real("Gridded Part" + string(part_num), "x", floor((x - abs(lengthdir_x(sprite_xoffset, image_angle))
    - abs(lengthdir_y(sprite_yoffset, image_angle)) - crnt_grid.x) / crnt_grid.cell_size));
    ini_write_real("Gridded Part" + string(part_num), "y", floor((y - abs(lengthdir_y(sprite_xoffset, image_angle))
    - abs(lengthdir_x(sprite_yoffset, image_angle)) - crnt_grid.y) / crnt_grid.cell_size));
    part_num++;
}
ini_close();
