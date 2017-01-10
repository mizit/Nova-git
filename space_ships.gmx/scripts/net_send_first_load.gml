///net_send_first_load(buffer, socket);
var l_buf = argument0;
var l_soc = argument1;
buffer_seek(l_buf, buffer_seek_start, 2 );
buffer_write(l_buf, buffer_u8, NET_FIRST_LOAD );
buffer_write_size(l_buf);
network_send_raw(l_soc, l_buf, buffer_tell(l_buf));
