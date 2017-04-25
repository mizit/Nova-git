///net_send_mark(buffer, socket);
var l_buf = argument0;
var l_soc = argument1;
if (ds_list_size(obj_globnav.marks_list) > 0)
{
    var l_mark = obj_globnav.marks_list[| 0];
    buffer_seek(l_buf, buffer_seek_start, 2 );
    buffer_write(l_buf, buffer_u8, NET_MARK);
    buffer_write(l_buf, buffer_u32, l_mark.x * 1000);
    buffer_write(l_buf, buffer_u32, l_mark.y * 1000);
    buffer_write_size(l_buf);
    network_send_raw(l_soc, l_buf, buffer_tell(l_buf));
}
