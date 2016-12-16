///inv_cell_with_object(content);
//Находит ячейку инвентаря с данным объектом
var l_obj = argument0;
for (var l_i = 0; l_i < instance_number(obj_inv_cell); l_i++)
{
    var a = instance_find(obj_inv_cell, l_i);
    if (a.my_content == l_obj)
    return a;
}
return noone;
