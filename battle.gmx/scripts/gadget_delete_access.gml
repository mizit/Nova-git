///gadget_delete_access(gadget, obj_grid);
var l_gadget = argument0;
var l_grid = argument1;
var l_access = l_gadget[| GADGET_ACCESS];
var l_pos = ds_list_find_index(l_access, l_grid);
ds_list_delete(l_access, l_pos);
