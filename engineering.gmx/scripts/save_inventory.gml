///save_inventory();
file_delete("inventory.ini");
ini_open("inventory.ini");
var part_num = 0;
with (obj_inv_cell)
{
    ini_write_string("Container" + string(part_num), "name", object_get_name(my_content));
    ini_write_real("Container" + string(part_num), "number", number);
    part_num++;
}
ini_close();
