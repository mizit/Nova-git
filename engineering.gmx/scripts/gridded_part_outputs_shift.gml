///gridded_part_outputs_shift(angle);
var l_angle = argument0;
while (l_angle < 0)
{
    l_angle += 360;
}
while (l_angle > 360)
{
    l_angle -= 360;
}
repeat(l_angle / 90)
{
    for (var i = 0; i < grid_size; i++)
    {
        for (var j = 0; j < grid_size; j++)
        {
            grid_outputs[# i, j] = circular_shift(grid_outputs[# i, j], 4, -1);
        }
    }
    for (var i = 1; i < grid_size; i++)
    {
        var tmp = grid_outputs[# i, 0];
        grid_outputs[# i, 0] = grid_outputs[# grid_size - 1, i];
        grid_outputs[# grid_size - 1, i] = grid_outputs[# grid_size - 1 - i , grid_size - 1];
        grid_outputs[# grid_size - 1 - i , grid_size - 1] = grid_outputs[# 0, grid_size - 1 - i];
        grid_outputs[# 0, grid_size - 1 - i] = tmp;
    }
    var tmp = width;
    width = height;
    height = tmp;
}
