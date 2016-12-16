///grid_find_active();
for (var l_i = 0; l_i < instance_number(obj_grid); l_i++)
{
    var a = instance_find(obj_grid, l_i);
    if (a.active == true)
    return a;
}
return noone;
