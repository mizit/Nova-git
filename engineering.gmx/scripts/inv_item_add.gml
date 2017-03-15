///inv_item_add(obj)
var l_obj = argument0;
var l_perm = noone;
if (object_is_ancestor(l_obj.object_index, obj_element_parent))
{
    l_perm = INV_ELEMENTS;
}
if (object_is_ancestor(l_obj.object_index, obj_item))
{
    l_perm = INV_ITEMS;
}
if (object_is_ancestor(l_obj.object_index, obj_part)) || (object_is_ancestor(l_obj.object_index, obj_gridded_part))
{
    if (l_obj.need_permission = PM_TUBE)
    {
        l_perm = INV_TUBE;
    }
    else
    {
        l_perm = INV_CONT;
    }
}
if (l_perm)
{
    var l_inv;
    with(obj_inv)
    {
        if (l_perm == permission)
            l_inv = id;
    }
    if (point_in_rectangle(l_obj.x, l_obj.y, l_inv.x, l_inv.y, l_inv.x + l_inv.sprite_width,
    l_inv.y + l_inv.sprite_height))
    {
        l_obj.x = clamp(l_obj.x, l_inv.x + l_obj.sprite_width / 2, l_inv.x + l_inv.sprite_width - l_obj.sprite_width / 2);
        l_obj.y = clamp(l_obj.y, l_inv.y + l_obj.sprite_height/ 2, l_inv.y + l_inv.sprite_height - l_obj.sprite_height / 2);
        ds_list_add(l_inv.items_list, l_obj);
    }
    else if (point_in_rectangle(l_obj.x, l_obj.y, obj_space.x, obj_space.y, obj_space.x + obj_space.sprite_width,
    obj_space.y + obj_space.sprite_height))
    {
        l_obj.x = clamp(l_obj.x, obj_space.x + l_obj.sprite_width / 2, obj_space.x + obj_space.sprite_width - l_obj.sprite_width / 2);
        l_obj.y = clamp(l_obj.y, obj_space.y + l_obj.sprite_height/ 2, obj_space.y + obj_space.sprite_height - l_obj.sprite_height / 2);
        ds_list_add(obj_space.items_list, l_obj);
        net_send_item_drop(obj_net.net_buf, obj_net.socket, l_obj);
    }
    else
    {
        l_obj.x = random_range(l_inv.x + l_obj.sprite_width / 2, l_inv.x + l_inv.sprite_width - l_obj.sprite_width / 2);
        l_obj.y = random_range(l_inv.y + l_obj.sprite_height/ 2, l_inv.y + l_inv.sprite_height - l_obj.sprite_height / 2);
        ds_list_add(l_inv.items_list, l_obj);
    }
    l_obj.visible = false;
    
}
