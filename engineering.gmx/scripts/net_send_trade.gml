///net_send_trade(buffer, socket, item);
var l_buf = argument0;
var l_soc = argument1;
var l_item = argument2;
buffer_seek(l_buf, buffer_seek_start, 2 );
buffer_write(l_buf, buffer_u8, NET_TRADE );
buffer_write(l_buf, buffer_u64, l_item.net_id);
buffer_write(l_buf, buffer_string, obj_out.points_list[| obj_out.selected]);
buffer_write_size(l_buf);
network_send_raw(l_soc, l_buf, buffer_tell(l_buf));
