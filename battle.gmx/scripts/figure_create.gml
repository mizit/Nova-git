///figure_create();
var l_x;
l_x[0] = 0;
var l_y;
l_y[0] = 0;
for (var l_i = 1; l_i < 4; l_i++)
{
    var l_test = 1;
    while (l_test)
    {
        switch (choose(0, 1, 2, 3))
        {
            case 0:
            {
                l_x[l_i] = l_x[l_i - 1] - 1;
                l_y[l_i] = l_y[l_i - 1];
                break;
            }
            case 1:
            {
                l_x[l_i] = l_x[l_i - 1] + 1;
                l_y[l_i] = l_y[l_i - 1];
                break;
            }
            case 2:
            {
                l_x[l_i] = l_x[l_i - 1];
                l_y[l_i] = l_y[l_i - 1] - 1;
                break;
            }
            case 3:
            {
                l_x[l_i] = l_x[l_i - 1];
                l_y[l_i] = l_y[l_i - 1] + 1;
                break;
            }
        }
        l_test = 0;
        for (var l_j = 0; l_j < l_i; l_j++)
        {
            if ((l_x[l_i] == l_x[l_j]) && (l_y[l_i] == l_y[l_j]))
            {
                l_test = 1;
            }
        }
    }
}
var minx, miny, maxx, maxy;
minx = min(l_x[0], l_x[1], l_x[2], l_x[3]);
maxx = max(l_x[0], l_x[1], l_x[2], l_x[3]);
miny = min(l_y[0], l_y[1], l_y[2], l_y[3]);
maxy = max(l_y[0], l_y[1], l_y[2], l_y[3]);
var l_grid = ds_grid_create(maxx - minx + 1, maxy - miny + 1);
ds_grid_set_region(l_grid, 0, 0, maxx - minx + 1, maxy - miny + 1, 0);
for (var l_i = 0; l_i < 4; l_i++)
{
    l_grid[# (l_x[l_i] - minx), (l_y[l_i] - miny)] = 1;
}
return l_grid;
