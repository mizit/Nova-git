///net_send_ship_data(buffer, socket);
var l_buf = argument0;
var l_soc = argument1;
buffer_seek(l_buf, buffer_seek_start, 2 );
buffer_write(l_buf, buffer_u8, NET_SHIP_DATA);

var l_air_output = 0, l_air_bank = 0, l_safely = 0;
var l_radar_range = 0, l_radio_range = 0, l_system_level = 0;
var l_main_drive = 0, l_man_drive = 0, l_back_drive = 0;
for (var l_i = 0; l_i < instance_number(obj_ls_parent); l_i++)
{
    var tmp = instance_find(obj_ls_parent, l_i);
    if (part_check_electricity(tmp))
    {
        l_air_output += tmp.air_output;
        l_air_bank += tmp.air_bank;
        l_safely += tmp.safely;
    }
}
for (var l_i = 0; l_i < instance_number(obj_nav_parent); l_i++)
{
    var tmp = instance_find(obj_nav_parent, l_i);
    if (part_check_electricity(tmp))
    {
        l_radar_range += tmp.radar_range;
        l_radio_range += tmp.radio_range;
        l_system_level += tmp.system_level;
    }
}
for (var l_i = 0; l_i < instance_number(obj_engine_parent); l_i++)
{
    var tmp = instance_find(obj_engine_parent, l_i);
    if (part_check_electricity(tmp))
    {
        l_main_drive += tmp.main_drive;
        l_man_drive += tmp.man_drive;
        l_back_drive += tmp.back_drive;
    }
}
var l_weapon_num = 0;
for (var l_i = 0; l_i < instance_number(obj_weapon_parent); l_i++)
{
    var tmp = instance_find(obj_weapon_parent, l_i);
    if (part_check_electricity(tmp))
    {
        l_weapon_num++;
    }
}

buffer_write(l_buf, buffer_u32, l_air_output);
buffer_write(l_buf, buffer_u32, l_air_bank);
buffer_write(l_buf, buffer_u32, l_safely);
buffer_write(l_buf, buffer_u32, l_radar_range);
buffer_write(l_buf, buffer_u32, l_radio_range);
buffer_write(l_buf, buffer_u32, l_system_level);
buffer_write(l_buf, buffer_u32, l_main_drive);
buffer_write(l_buf, buffer_u32, l_man_drive);
buffer_write(l_buf, buffer_u32, l_back_drive);
buffer_write(l_buf, buffer_u32, obj_grid.mass);
buffer_write(l_buf, buffer_u32, l_weapon_num);
for (var l_i = 0; l_i < instance_number(obj_weapon_parent); l_i++)
{
    var tmp = instance_find(obj_weapon_parent, l_i);
    if (part_check_electricity(tmp))
    {
        buffer_write(l_buf, buffer_u32, tmp.weapon);
        buffer_write(l_buf, buffer_u32, tmp.shields);
        buffer_write(l_buf, buffer_u32, tmp.electronic_warfare);
    }
}

buffer_write_size(l_buf);
network_send_raw(l_soc, l_buf, buffer_tell(l_buf));
