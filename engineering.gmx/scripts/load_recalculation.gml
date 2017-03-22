///load_recalculation();
with (obj_power_parent)
{
    load = 0;
}
with (obj_gridded_part)
{
    if ((grd_x >= 0) && (grd_y >= 0))
    {
        var l_p_list = obj_grid.ship_grid[# grd_x, grd_y];
        l_p_list = l_p_list[| CELL_PS_LIST];
        var l_buf_ec = energy_consumption;
        for (var l_i = 0; l_i < ds_list_size(l_p_list); l_i++)
        {
            if ((l_buf_ec > 0))
            {
                l_p_list[| l_i].load += l_buf_ec;
                //var tmp = l_p_list[| l_i].my_power - l_p_list[| l_i].load;
                //l_p_list[| l_i].load += min(tmp, l_buf_ec);
                //l_buf_ec -= min(tmp, l_buf_ec);
                /*if (keyboard_check(vk_space))
                {
                    show_message("delta = " + string(tmp) + " ec = " + string(l_buf_ec));
                }*/
                //if ((l_i == (ds_list_size(l_p_list) - 1)) && (l_buf_ec > 0))
                //{
                //    l_p_list[| l_i].load += l_buf_ec;
                //}
            }
        }
    }
}
with (obj_power_parent)
{
    if ((grd_x > 0) && (grd_y > 0))
    {
        var all_power = 0;
        var list_tmp = obj_grid.ship_grid[# grd_x, grd_y];
        list_tmp = list_tmp[| CELL_PS_LIST];
        for (var i = 0; i < ds_list_size(list_tmp); i++)
        {
            if !(list_tmp[| i].shut_down)
            {
                all_power += list_tmp[| i].my_power;
            }
        }
        if (load > all_power) && !(shut_down)
        {
            if (my_charge < 0)
            {
                shut_down = 1;
                event_perform(ev_other, ev_user2);
                alarm[0] = shut_down_time;
            }
            else
            {
                my_charge -= (load - all_power) * charge_koeff;
            }
        }
    }
}
