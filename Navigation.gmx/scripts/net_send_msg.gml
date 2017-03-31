///net_send_msg(buffer, socket);
var l_buf = argument0;
var l_soc = argument1;
buffer_seek(l_buf, buffer_seek_start, 2 );
buffer_write(l_buf, buffer_u8, NET_TEXT );
buffer_write(l_buf, buffer_u32, obj_gui.channels[obj_gui.select]);
buffer_write(l_buf, buffer_string, obj_gui.msg_text);
buffer_write_size(l_buf);
network_send_raw(l_soc, l_buf, buffer_tell(l_buf));

