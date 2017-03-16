///net_send_item_get_num(buffer, socket, num);
var l_buf = argument0;
var l_soc = argument1;
var l_num = argument2;
buffer_seek(l_buf, buffer_seek_start, 2 );
buffer_write(l_buf, buffer_u8, NET_ITEM );
buffer_write(l_buf, buffer_u8, ITEM_GET | ITEM_NUM);
buffer_write(l_buf, buffer_u64, l_num );
buffer_write_size(l_buf);
network_send_raw(l_soc, l_buf, buffer_tell(l_buf));

