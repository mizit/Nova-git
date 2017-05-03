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
                //show_message("Ошибка! Данные о позиции пришли до создания корабля.");
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
            obj_ship.max_hp = buffer_read(l_buf, buffer_u32);
            obj_ship.max_oxygen = buffer_read(l_buf, buffer_u32);
            obj_ship.hp = buffer_read(l_buf, buffer_u32);
            obj_ship.oxygen = buffer_read(l_buf, buffer_u32);
            obj_ship.oxygen_output = buffer_read(l_buf, buffer_u32);
            obj_ship.safely = buffer_read(l_buf, buffer_u32);
        }
        break;
    }
    case NET_TEXT:
    {
        var l_ch = buffer_read(l_buf, buffer_u32);
        var l_flags = buffer_read(l_buf, buffer_u32);
        var l_msg = buffer_read(l_buf, buffer_string);
        var l_dis = buffer_read(l_buf, buffer_u32);// / 100000;
        /*var tmp_ship;
        with (obj_enemy_ship)
        {
            if (name == "Nova")
            {tmp_ship = id;}
        }
        show_message(point_distance(obj_ship.x, obj_ship.y, tmp_ship.x, tmp_ship.y));*/
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
                LogAddString(l_msg);
                /*
                if (!surface_exists(log_surf))
                {
                    log_surf = surface_create(log_width, log_height);
                }
                if (!surface_exists(log_buf_surf))
                {
                    log_buf_surf = surface_create(log_width, log_height);
                }
                surface_set_target(log_buf_surf);
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
                surface_reset_target();*/
            }
        }
        break;
    }
    case NET_ITEM:
    {
        var l_com = buffer_read(l_buf, buffer_u32);
        if (((l_com & $0F) == ITEM_SET) || ((l_com & $0F) == ITEM_DROP))
        {
            var l_str = buffer_read(l_buf, buffer_string);
            if (l_str == "noone")
            {
                first_load = 0;
                break;
            }
            var l_name = asset_get_index(l_str);
            if (l_name == -1)
            {
                l_name = obj_box;
            }
            
            var l_net_id = buffer_read(l_buf, buffer_u32);
            l_net_id += (buffer_read(l_buf, buffer_u32) << 32);
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
            l_obj.name = l_str;
            l_obj.x = buffer_read(l_buf, buffer_u32) / 1000;
            l_obj.y = buffer_read(l_buf, buffer_u32) / 1000;
            l_obj.image_angle = buffer_read(l_buf, buffer_s32) / 1000;
            l_obj.hp = buffer_read(l_buf, buffer_u32);
            if (first_load)
            {
                net_send_item_get_num(obj_net.net_buf, obj_net.socket, obj_ship.item_counter);
                obj_ship.item_counter++;
            }
        }
        if (((l_com & $0F) == ITEM_PICKUP) || ((l_com & $0F) == ITEM_DEL))
        {
            var l_str = buffer_read(l_buf, buffer_string);
            var l_name = asset_get_index(l_str);
            if (l_name == -1)
            {
                l_name = obj_box;
            }
            var l_net_id = buffer_read(l_buf, buffer_u32);
            l_net_id += (buffer_read(l_buf, buffer_u32) << 32);
            var l_obj = noone;
            with (l_name)
            {
                if (net_id == l_net_id)
                {
                    instance_destroy();
                }
            }
            buffer_read(l_buf, buffer_u32);
            buffer_read(l_buf, buffer_u32);
            buffer_read(l_buf, buffer_s32);
            buffer_read(l_buf, buffer_u32);
        }
        break;
    }
    case NET_ASTEROID:
    {
        var l_size = buffer_read(l_buf, buffer_u32);
        for (var l_i = 0; l_i < l_size; l_i++)
        {
            var l_x = buffer_read(l_buf, buffer_u32) * 100;
            var l_y = buffer_read(l_buf, buffer_u32) * 100;
            var l_type = buffer_read(l_buf, buffer_string);
            var l_tmp = instance_position(l_x, l_y, obj_asteroid_profit);
            if (!l_tmp)
            {
                l_tmp = instance_create(l_x, l_y, obj_asteroid_profit);
            }
            name = l_type;
            switch (l_type)
            {
                case "obj_gold":
                {
                    l_tmp.sprite_index = s_astr_gold;
                    break;
                }
                case "obj_ruby":
                {
                    l_tmp.sprite_index = s_astr_ruby;
                    break;
                }
                case "obj_emerald":
                {
                    l_tmp.sprite_index = s_astr_emerald;
                    break;
                }
                default:
                {
                    sprite_index = obj_great_ship;
                }
            }
            l_tmp.num = buffer_read(l_buf, buffer_u32);
        }
        break;
    }
    case NET_BOT:
    {
        var l_name = buffer_read(l_buf, buffer_string);
        var l_id = buffer_read(l_buf, buffer_u32);
        var l_active = buffer_read(l_buf, buffer_u32);
        var l_x = buffer_read(l_buf, buffer_u32);
        var l_y = buffer_read(l_buf, buffer_u32);
        var l_speed = buffer_read(l_buf, buffer_u32);
        var l_direction = buffer_read(l_buf, buffer_u32);
        var l_hp = buffer_read(l_buf, buffer_u32);
        var l_com_type = buffer_read(l_buf, buffer_u32);
        var l_bot = noone;
        with (obj_bot_parent)
        {
            if (net_id == l_id)
                l_bot = id;
        }
        if (l_bot == noone)
        {
            l_name = asset_get_index(l_name);
            if (l_name == -1)
            {
                break;
            }
            l_bot = instance_create(l_x, l_y, l_name);
            l_bot.net_id = l_id;
        }
        l_bot.active = l_active;
        l_bot.x = l_x;
        l_bot.y = l_y;
        l_bot.speed = l_speed;
        l_bot.direction = l_direction;
        l_bot.hp = l_hp;
        l_bot.com_type = l_com_type;
        break;
    }
}
buffer_delete(l_buf);
