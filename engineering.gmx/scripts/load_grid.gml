///load_grid(grid);
/*var crnt_grid = argument0;
ini_open("ship_grid.ini");
for (var i = 0; i < 7; i++)
{
    for (var j = 0; j < 7; j++)
    {
        var cell = crnt_grid.ship_grid[# i, j];
        cell[| CELL_PERMISSION] = ini_read_real("Ship permissions", string(i) + "x" + string(j), 0);
    }
}
var part_num = 0;
while (ini_section_exists("Part" + string(part_num)))
{
    var obj;
    obj = asset_get_index(ini_read_string("Part" + string(part_num), "name", noone));
    var part;
    part = instance_create(0, 0, obj);
    part.image_angle = ini_read_real("Part" + string(part_num), "angle", 0);
    with(part)
    {
        part_outputs_shift(part.image_angle);
        part_set(crnt_grid, ini_read_real("Part" + string(part_num), "x", 0),
        ini_read_real("Part" + string(part_num), "y", 0));
    }
    part_num++;
}
part_num = 0;
while (ini_section_exists("Gridded Part" + string(part_num)))
{
    var obj;
    obj = asset_get_index(ini_read_string("Gridded Part" + string(part_num), "name", noone));
    var part;
    part = instance_create(0, 0, obj);
    part.image_angle = ini_read_real("Gridded Part" + string(part_num), "angle", 0);
    with(part)
    {
        gridded_part_outputs_shift(part.image_angle);
        gridded_part_set(crnt_grid, ini_read_real("Gridded Part" + string(part_num), "x", 0),
        ini_read_real("Gridded Part" + string(part_num), "y", 0));
    }
    part_num++;
}
ini_close();*/
