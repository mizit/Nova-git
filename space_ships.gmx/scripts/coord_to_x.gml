///coord_to_x(string, num);
var l_str = argument0;
var l_num = argument1;

var l_x = 0;
for (var l_i = 0; l_i < 10; l_i ++)
{
    if (obj_gui.sign_arr[l_i] == l_str)
    {
        l_x += l_i * 25000;
        break;
    }
}
switch (l_num)
{
    case 1:
    case 7:
    case 8:
        l_x += 4166;
        break;
    case 2:
    case 9:
    case 6:
        l_x += 12500;
        break;
    case 3:
    case 4:
    case 5:
        l_x += 20834;
        break;
}
return l_x;
