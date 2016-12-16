///part_set_selected(enable);
if (argument0)
{
    with(obj_part_parent)
    {
        part_set_selected(0);
    }
    selected = 1;
    if (object_get_parent(object_index) != obj_tube_parent)
    {
        var tmp = instance_create(832, 224, obj_part_grid);
        tmp.width = width * abs(cos(degtorad(image_angle))) + height * abs(sin(degtorad(image_angle)));
        tmp.height = width * abs(sin(degtorad(image_angle))) + height * abs(cos(degtorad(image_angle)));
        tmp.back_sprite = sprite_index;
        tmp.elements_max = width * height;
        tmp.mask_index = sprite_index;
        tmp.base = object_index;
        tmp.elements_list = elements_list;
    }
}
else
{
    if (selected)
    {
        with (obj_part_grid)
        {
            instance_destroy();
        }
    }
    selected = 0;
}
