///net_send_position(buffer, socket);
/*var l_buf = argument0;
var l_soc = argument1;
buffer_seek(l_buf, buffer_seek_start, 2 );
buffer_write(l_buf, buffer_u8, NET_POSITION );
buffer_write(l_buf, buffer_u32, obj_ship.x * 1000);
buffer_write(l_buf, buffer_u32, obj_ship.y * 1000);
buffer_write(l_buf, buffer_u32, obj_ship.image_angle * 1000);
buffer_write(l_buf, buffer_u32, obj_ship.speed * 1000);
buffer_write(l_buf, buffer_u32, obj_ship.rot_speed * 1000);
buffer_write(l_buf, buffer_u32, obj_ship.direction * 1000);
buffer_write_size(l_buf);
network_send_raw(l_soc, l_buf, buffer_tell(l_buf));*/
