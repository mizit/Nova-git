///net_send_oxygen_up(buffer, socket, oxygen);
var l_buf = argument0;
var l_soc = argument1;
var l_oxygen = argument2;
buffer_seek(l_buf, buffer_seek_start, 2 );
buffer_write(l_buf, buffer_u8, NET_SUPPLIES);
buffer_write(l_buf, buffer_u32, SP_OXY_ADD);
buffer_write(l_buf, buffer_u32, l_oxygen);
buffer_write_size(l_buf);
network_send_raw(l_soc, l_buf, buffer_tell(l_buf));

