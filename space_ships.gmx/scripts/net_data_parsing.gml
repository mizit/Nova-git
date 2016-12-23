///net_data_parsing(buffer);
var l_buf = argument0;
buffer_seek(l_buf, buffer_seek_start, 0);
var l_command = buffer_read(l_buf, buffer_u8);
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
            obj_ship.x = buffer_read(l_buf, buffer_u32) / 1000;
            obj_ship.y = buffer_read(l_buf, buffer_u32) / 1000;
            obj_ship.image_angle = buffer_read(l_buf, buffer_u32) / 1000;
            obj_ship.speed = buffer_read(l_buf, buffer_u32) / 1000;
            obj_ship.rot_speed = buffer_read(l_buf, buffer_u32) / 1000;
            //obj_ship.direction = buffer_read(l_buf, buffer_u32) / 1000;
        }
        break;
    }
}
