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
    case NET_POSITION:
    {
        var ship_name = buffer_read(l_buf, buffer_string);
        if (ship_name == login)
        {
            if (!instance_exists(obj_ship))
            {
                show_message("Ошибка! Данные о позиции пришли до создания корабля.");
                break;
            }
            obj_ship.x = buffer_read(l_buf, buffer_s32) / 1000;
            obj_ship.y = buffer_read(l_buf, buffer_s32) / 1000;
            obj_ship.image_angle = buffer_read(l_buf, buffer_s32) / 1000;
            obj_ship.speed = buffer_read(l_buf, buffer_s32) / 1000;
            obj_ship.rot_speed = buffer_read(l_buf, buffer_s32) / 1000;
            obj_ship.direction = buffer_read(l_buf, buffer_s32) / 1000;
        }
        else
        {
            var l_test = 0;
            with(obj_enemy_ship)
            {
                if (ship_name == name)
                {
                    l_test = 1;
                    x = buffer_read(l_buf, buffer_s32) / 1000;
                    y = buffer_read(l_buf, buffer_s32) / 1000;
                    image_angle = buffer_read(l_buf, buffer_s32) / 1000;
                    speed = buffer_read(l_buf, buffer_s32) / 1000;
                    rot_speed = buffer_read(l_buf, buffer_s32) / 1000;
                    direction = buffer_read(l_buf, buffer_s32) / 1000;
                }
            }
            if (!l_test)
            {
                var l_ship = instance_create(0, 0, obj_enemy_ship);
                l_ship.name = ship_name;
                l_ship.x = buffer_read(l_buf, buffer_s32) / 1000;
                l_ship.y = buffer_read(l_buf, buffer_s32) / 1000;
                l_ship.image_angle = buffer_read(l_buf, buffer_s32) / 1000;
                l_ship.speed = buffer_read(l_buf, buffer_s32) / 1000;
                l_ship.rot_speed = buffer_read(l_buf, buffer_s32) / 1000;
                l_ship.direction = buffer_read(l_buf, buffer_s32) / 1000;
            }
        }
        break;
    }
    case NET_MARK:
    {
        if (instance_exists(obj_mark))
        {
            obj_mark.x = buffer_read(l_buf, buffer_s32) / 1000;
            obj_mark.y = buffer_read(l_buf, buffer_s32) / 1000;
        }
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
            var l_net_id = buffer_read(l_buf, buffer_u32);
            var l_obj = noone;
            with (l_name)
            {
                if (net_id == l_net_id)
                {
                    l_obj = id;
                }
            }
            if !(l_obj)
            {
                l_obj = instance_create(0, 0, l_name);
                l_obj.net_id = l_net_id;
            }
            buffer_read(l_buf, buffer_u32);
            l_obj.x = buffer_read(l_buf, buffer_u32) / 1000;
            l_obj.y = buffer_read(l_buf, buffer_u32) / 1000;
            l_obj.image_angle = buffer_read(l_buf, buffer_s32) / 1000;
            l_obj.hp = buffer_read(l_buf, buffer_u32);
            if ((l_obj.x < 10) && (l_obj.x > -1) && 
            (l_obj.y < 10) && (l_obj.y > -1))
            {
                with(l_obj)
                {
                    instance_destroy();
                }
            }
        }
        if (first_load)
        {
            net_send_item_get_num(obj_net.net_buf, obj_net.socket, obj_ship.item_counter);
            obj_ship.item_counter++;
        }
    }
}
buffer_delete(l_buf);
