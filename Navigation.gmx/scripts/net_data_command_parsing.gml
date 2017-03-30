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
                //
                show_message("Ошибка! Данные о позиции пришли до создания корабля.");
                break;
            }
            obj_ship.x = buffer_read(l_buf, buffer_s32) / 1000;
            obj_ship.y = buffer_read(l_buf, buffer_s32) / 1000;
            obj_ship.image_angle = buffer_read(l_buf, buffer_s32) / 1000;
            obj_ship.speed = buffer_read(l_buf, buffer_s32) / 1000;
            obj_ship.rot_speed = buffer_read(l_buf, buffer_s32) / 1000;
            obj_ship.direction = buffer_read(l_buf, buffer_s32) / 1000;
            var l_type = buffer_read(l_buf, buffer_string);
            if (asset_get_type(l_type) == asset_sprite)
            {
                l_type = asset_get_index(l_type);
                obj_ship.sprite_index = l_type;
            }   
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
                    var l_type = buffer_read(l_buf, buffer_string);
                    if (asset_get_type(l_type) == asset_sprite)
                    {
                        l_type = asset_get_index(l_type);
                        sprite_index = l_type;
                    }    
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
                var l_type = buffer_read(l_buf, buffer_string);
                if (asset_get_type(l_type) == asset_sprite)
                {
                    l_type = asset_get_index(l_type);
                    l_ship.sprite_index = l_type;
                } 
            }
        }
        break;
    }
    case NET_SHIP_DATA:
    {
        if (instance_exists(obj_ship))
        {
            obj_ship.radar_range = buffer_read(l_buf, buffer_u32);
            obj_ship.radio_range = buffer_read(l_buf, buffer_u32);
            obj_ship.system_level = buffer_read(l_buf, buffer_u32);
            obj_ship.thurst_pwr = buffer_read(l_buf, buffer_u32);
            obj_ship.rot_pwr = buffer_read(l_buf, buffer_u32);
            obj_ship.mnvr_pwr = obj_ship.rot_pwr; 
            obj_ship.back_drive = buffer_read(l_buf, buffer_u32);
            obj_ship.mass = buffer_read(l_buf, buffer_u32);
        }
        break;
    }
}
buffer_delete(l_buf);
