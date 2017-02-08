///buffer_write_size(buffer);
var l_buf = argument0;
var size = buffer_tell(l_buf) - 2;
size = min(size, $FFFD);
buffer_seek(l_buf, buffer_seek_start, 0);
buffer_write(l_buf, buffer_u16, size);
buffer_seek(l_buf, buffer_seek_start, size + 2);
