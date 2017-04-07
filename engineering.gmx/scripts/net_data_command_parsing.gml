///net_data_command_parsing(buffer);
var l_buf = argument0;
buffer_seek(l_buf, buffer_seek_start, 0);
var l_command = buffer_read(l_buf, buffer_u8);
//show_message("command = " + string(l_command));
switch (l_command)
{
    case NET_GOOD_DAY:
    {
        var l_answer = buffer_read(l_buf, buffer_u8);
        if (l_answer == YES)
        {
            if (room == r_authorization)
            {
                room_goto_next();
            }
        }
        if (l_answer == NO)
        {
            show_message("Неверный логин-пароль!");
            game_restart();
        }
        if (l_answer == ERROR)
        {
            show_message("Неизвестная ошибка со стороны сервера!");
            game_restart();
        }
        if (l_answer == BUSY)
        {
            show_message("Данная позиция занята!");
            game_restart();
        }
        break;
    }
    case NET_SHELL:
    {
        for (var i = 0; i < 7; i++)
        {
            for (var j = 0; j < 7; j++)
            {
                cell_set_permission(obj_grid.ship_grid, i, j, buffer_read(l_buf, buffer_u32));
            }
        }
        net_send_item_get_num(obj_net.net_buf, obj_net.socket, 0);
        obj_grid.item_counter++;
        break;
    }
    case NET_ITEM:
    {
        var l_com = buffer_read(l_buf, buffer_u32);
        var l_str = buffer_read(l_buf, buffer_string);
        if (l_str == "noone")
        {
            first_load = 0;
            break;
        }
        var l_name = asset_get_index(l_str);
        if (l_name > 0)
        {
            if ((l_com & $0F) == ITEM_SET)
            {
                var l_id = buffer_read(l_buf, buffer_u32);
                l_id += (buffer_read(l_buf, buffer_u32) << 32);
                var l_obj = noone;
                with(obj_global_item)
                {
                    if (net_id == l_id)
                    {
                        l_obj = id;
                    }
                }
                if !(l_obj)
                {
                    l_obj = instance_create(0, 0, l_name);
                }
                var l_x = buffer_read(l_buf, buffer_u32);
                var l_y = buffer_read(l_buf, buffer_u32);
                l_obj.net_id = l_id;
                l_obj.image_angle = buffer_read(l_buf, buffer_s32);
                l_obj.hp = buffer_read(l_buf, buffer_u32);
                if ((l_x == 0) || (l_y == 0))
                {
                    if (object_is_ancestor(l_obj.object_index, obj_part))
                    {
                        with(l_obj)
                        {
                            part_outputs_shift(image_angle);
                        }
                    }
                    if (object_is_ancestor(l_obj.object_index, obj_gridded_part))
                    {
                        with(l_obj)
                        {
                            gridded_part_outputs_shift(image_angle);
                        }
                    }
                    inv_item_add(l_obj);
                }
                else 
                {
                    l_x--;
                    l_y--;
                    if (object_is_ancestor(l_obj.object_index, obj_part))
                    {
                        with(l_obj)
                        {
                            part_outputs_shift(image_angle);
                            if (!part_set(obj_grid, l_x, l_y, 0))
                            {
                                inv_item_add(id);
                                dragging = 0;
                            }
                        }
                    }
                    if (object_is_ancestor(l_obj.object_index, obj_gridded_part))
                    {
                        with(l_obj)
                        {
                            gridded_part_outputs_shift(image_angle);
                            if (!gridded_part_set(obj_grid, l_x, l_y, 0))
                            {
                                inv_item_add(id);
                                dragging = 0;
                            }
                        }
                    }
                    if (object_is_ancestor(l_obj.object_index, obj_element_parent))
                    {
                        with(l_obj)
                        {
                            inv_item_add(id);
                            grd_x = l_x;
                            grd_y = l_y;
                            must_set_up = 1;
                        }
                    }
                }
            }
            if ((l_com & $0F) == ITEM_PICKUP)
            {
                var l_id = buffer_read(l_buf, buffer_u32);
                l_id += (buffer_read(l_buf, buffer_u32) << 32);
                var l_obj = noone;
                with(obj_global_item)
                {
                    if (net_id == l_id)
                    {
                        buffer_read(l_buf, buffer_u32);
                        buffer_read(l_buf, buffer_u32);
                        buffer_read(l_buf, buffer_s32);
                        buffer_read(l_buf, buffer_u32);
                        return 0;
                    }
                }
                l_obj = instance_create(0, 0, l_name);
                var l_x = buffer_read(l_buf, buffer_u32);
                var l_y = buffer_read(l_buf, buffer_u32);
                l_obj.net_id = l_id;
                l_obj.image_angle = buffer_read(l_buf, buffer_s32);
                l_obj.hp = buffer_read(l_buf, buffer_u32);
                l_obj.x = random_range(obj_space.x + sprite_get_width(l_obj.sprite_index) / 2, 
                    obj_space.x + sprite_get_width(obj_space.sprite_index) - sprite_get_width(l_obj.sprite_index) / 2);
                l_obj.y = random_range(obj_space.y + sprite_get_height(l_obj.sprite_index) / 2, 
                    obj_space.y + sprite_get_height(obj_space.sprite_index) - sprite_get_height(l_obj.sprite_index) / 2);
                inv_item_add(l_obj);
            }
            if ((l_com & $0F) == ITEM_DROP)
            {
                var l_id = buffer_read(l_buf, buffer_u32);
                l_id += (buffer_read(l_buf, buffer_u32) << 32);
                var l_obj = noone;
                with(obj_global_item)
                {
                    if (net_id == l_id)
                    {
                        l_obj = id;
                    }
                }
                if (l_obj)
                {
                    var l_pos = ds_list_find_index(obj_space.items_list, l_obj);
                    with (l_obj)
                    {
                        instance_destroy();
                    }
                    ds_list_delete(obj_space.items_list, l_pos);
                }
            }
            if ((l_com & $0F) == ITEM_DEL)
            {
                var l_id = buffer_read(l_buf, buffer_u32);
                l_id += (buffer_read(l_buf, buffer_u32) << 32);
                var l_obj = noone;
                with(obj_global_item)
                {
                    if (net_id == l_id)
                    {
                        l_obj = id;
                    }
                }
                if (l_obj)
                {
                    var l_pos = ds_list_find_index(obj_space.items_list, l_obj);
                    if (l_pos >= 0)
                    {
                        ds_list_delete(obj_space.items_list, l_pos);
                    }
                    with (obj_inv)
                    {
                        l_pos = ds_list_find_index(items_list, l_obj);
                        if (l_pos >= 0)
                        {
                            ds_list_delete(items_list, l_pos);
                        }
                    }
                    with (l_obj)
                    {
                        instance_destroy();
                    }
                }
            }
        }
        if (obj_grid.first_load)
        {
            net_send_item_get_num(obj_net.net_buf, obj_net.socket, obj_grid.item_counter);
            obj_grid.item_counter++;
        }
        break;
    }
    case NET_SHIP_DATA:
    {
        if (instance_exists(obj_grid))
        {
            obj_grid.cnt_hp = buffer_read(l_buf, buffer_u32);
        }
        break;
    }
}
buffer_delete(l_buf);
