///part_outputs_recalculation(angle);
var l_angle = argument0;
while (l_angle < 0)
{
    l_angle += 360;
}
while (l_angle > 360)
{
    l_angle -= 360;
}
outputs = circular_shift(outputs, 4, -l_angle / 90);
