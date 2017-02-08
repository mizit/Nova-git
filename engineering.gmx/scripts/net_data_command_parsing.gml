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
        var l_str = buffer_read(l_buf, buffer_string);
        if (l_str == "noone")
        {
            first_load = 0;
            break;
        }
        var l_name = asset_get_index(l_str);
        if (l_name > 0)
        {
            var l_obj = instance_create(0, 0, l_name);
            var l_id = buffer_read(l_buf, buffer_u64);
            var l_x = buffer_read(l_buf, buffer_u32);
            var l_y = buffer_read(l_buf, buffer_u32);
            var l_ia = buffer_read(l_buf, buffer_u32);
            var l_hp = buffer_read(l_buf, buffer_u32);
            l_obj.net_id = l_id;
            l_obj.hp = l_hp;
            l_obj.image_angle = l_ia;
            if ((l_x == 0) || (l_y == 0))
            {
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
                        part_outputs_shift(l_obj.image_angle);
                        part_set(obj_grid, l_x, l_y);
                    }
                }
                if (object_is_ancestor(l_obj.object_index, obj_gridded_part))
                {
                    with(l_obj)
                    {
                        gridded_part_outputs_shift(l_obj.image_angle);
                        gridded_part_set(obj_grid, l_x, l_y);
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
}
buffer_delete(l_buf);
