///cell_destructor(ds_cell);
var l_list = argument0;
ds_list_destroy(l_list[| CELL_PS_LIST]);
ds_list_destroy(l_list);
