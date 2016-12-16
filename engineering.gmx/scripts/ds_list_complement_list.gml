///ds_list_add_list(ds_destination_list, ds_source_list);
var l_dst = argument0;
var l_src = argument1;
var l_test = 0;
for (var l_i = 0; l_i < ds_list_size(l_src); l_i++)
{
    var l_tmp = l_src[| l_i];
    if (ds_list_find_index(l_dst, l_tmp) == -1)
    {
        ds_list_add(l_dst, l_tmp);
        l_test ++;
    }
}
return l_test;
