///LogAddString(string);
var l_str = argument0;
with (obj_gui)
{
        if (!surface_exists(log_surf))
        {
            log_surf = surface_create(log_width, log_height);
        }
        if (!surface_exists(log_buf_surf))
        {
            log_buf_surf = surface_create(log_width, log_height);
        }
        surface_set_target(log_buf_surf);
        draw_surface(log_surf, 0, -string_height_ext(l_str, -1, log_width));
        draw_set_colour(c_black);
        draw_rectangle(0, log_height - string_height_ext(l_str, -1, log_width), 
        log_width, log_height, 0);
        draw_set_colour(c_red);
        draw_text_ext(0, log_height - string_height_ext(l_str, -1, log_width), l_str,
        -1, log_width);            
        surface_reset_target();
        surface_set_target(log_surf);
        draw_surface(log_buf_surf, 0, 0);
        surface_reset_target();
}
