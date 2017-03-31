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
    case NET_TEXT:
    {
        var l_ch = buffer_read(l_buf, buffer_u32);
        var l_flags = buffer_read(l_buf, buffer_u32);
        var l_msg = buffer_read(l_buf, buffer_string);
        var l_dis = buffer_read(l_buf, buffer_u32) / 100000;
        with (obj_gui)
        {
            var l_test = 0;
            for (var l_i = 0; l_i < 4; l_i++)
            {
                if (channels[l_i] == l_ch)
                {
                    l_test = 1;
                }
            }
            if ((l_test) || (l_flags & TX_SYSTEM))
            {
                surface_set_target(log_buf_surf);
                var l_clr = c_white;
                if (l_flags & TX_MESSAGE)
                {
                    l_msg = note_corrupt(l_msg, max(1, obj_ship.radio_range) / max(1, l_dis));
                    //show_message("radio - " + string(obj_ship.radio_range) + " distance - " + string(l_dis));
                    l_clr = c_green;
                    l_msg = "[" + string(l_ch) + "] " + l_msg;
                }
                if (l_flags & TX_SYSTEM)
                {
                    l_clr = c_red;
                    l_msg = "*" + l_msg + "*";
                }
                if (!surface_exists(log_surf))
                {
                    log_surf = surface_create(log_width, log_height);
                }
                if (!surface_exists(log_buf_surf))
                {
                    log_buf_surf = surface_create(log_width, log_height);
                }
                draw_surface(log_surf, 0, -string_height_ext(l_msg, -1, log_width));
                draw_set_colour(c_black);
                draw_rectangle(0, log_height - string_height_ext(l_msg, -1, log_width), 
                log_width, log_height, 0);
                draw_set_colour(l_clr);
                draw_text_ext(0, log_height - string_height_ext(l_msg, -1, log_width), l_msg,
                -1, log_width);            
                surface_reset_target();
                surface_set_target(log_surf);
                draw_surface(log_buf_surf, 0, 0);
                surface_reset_target();
            }
        }
        break;
    }
}
buffer_delete(l_buf);
