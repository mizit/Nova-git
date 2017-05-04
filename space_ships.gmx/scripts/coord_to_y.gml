///coord_to_y(big_num, num);
var l_bn = argument0;
var l_num = argument1;

var l_y = 0;
l_y += ((l_bn - 30) * 25000);
switch (l_num)
{
    case 1:
    case 2:
    case 3:
        l_y += 4166;
        break;
    case 8:
    case 9:
    case 4:
        l_y += 12500;
        break;
    case 7:
    case 6:
    case 5:
        l_y += 20834;
        break;
}
return l_y;
