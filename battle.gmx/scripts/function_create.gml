///function_create();
var l_list = ds_list_create();
l_list[| FUNC_DRAW] = noone;
l_list[| FUNC_SCRIPT] = noone;
l_list[| FUNC_GRID] = noone;
l_list[| FUNC_POS] = pos_create();
return l_list;
