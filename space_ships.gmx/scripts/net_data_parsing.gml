///net_data_parsing(fifo);
var l_fifo = argument0;
var l_rem = noone;
var l_com_buf = noone;
var l_len = 0;
while (ds_queue_size(l_fifo) > 0)
{
    var l_buf = ds_queue_dequeue(l_fifo);
    buffer_seek(l_buf, buffer_seek_start, 0);
    while (true)
    {
        if (l_rem == noone)
        {
            l_len = buffer_read(l_buf, buffer_u16);
            show_message("length = " + string(l_len));
            if (l_len <= (buffer_get_size(l_buf) - buffer_tell(l_buf)))
            {
                l_com_buf = buffer_create(l_len, buffer_fixed, 1);
                buffer_seek(l_com_buf, buffer_seek_start, 0);
                buffer_copy(l_buf, buffer_tell(l_buf), l_len, l_com_buf, 0);
                net_data_command_parsing(l_com_buf);
                buffer_seek(l_buf, buffer_seek_relative, l_len);
                if (buffer_get_size(l_buf) == buffer_tell(l_buf))
                {
                    break;
                }
            }
            else
            {
                l_rem = l_len - (buffer_get_size(l_buf) - buffer_tell(l_buf));
                l_com_buf = buffer_create(l_len, buffer_fixed, 1);
                buffer_seek(l_com_buf, buffer_seek_start, 0);
                buffer_copy(l_com_buf, 0, l_len - l_rem, l_buf, buffer_tell(l_buf));
                break;
            }
        }
        else
        {
            show_message("net carry-on");
            if (l_rem <= (buffer_get_size(l_buf) - buffer_tell(l_buf)))
            {
                buffer_copy(l_com_buf, l_len - l_rem, l_rem, l_buf, buffer_tell(l_buf));
                net_data_command_parsing(l_com_buf);
                buffer_seek(l_buf, buffer_seek_relative, l_rem);
                if (buffer_get_size(l_buf) == buffer_tell(l_buf))
                {
                    break;
                }
            }
            else
            {
                show_message("net strange carry-on");
                var tmp_rem = l_len - l_rem - (buffer_get_size(l_buf) - buffer_tell(l_buf));
                buffer_copy(l_com_buf, l_len - l_rem, l_rem - tmp_rem, l_buf, buffer_tell(l_buf));
                break;
            }
        }
    }
}


