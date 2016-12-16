///gadget_create(type, name, level);
var l_type = argument0;
var l_name = argument1;
var l_level = argument2;
var l_list = ds_list_create();
l_list[| GADGET_TYPE] = l_type;
l_list[| GADGET_FUNC] = ds_list_create();
switch (l_type)
{
    case GT_WEAPON:
    {
        for (var l_i = 0; l_i < l_level; l_i++)
        {
            ds_list_add(l_list[| GADGET_FUNC], function_create());
        }
        if (l_level > 0)
        {
            var grid = ds_grid_create(2, 2);
            ds_grid_set_region(grid, 0, 0, 1, 1, 1);
            var func = ds_list_find_value(l_list[| GADGET_FUNC], 0);
            func[| FUNC_GRID] = grid;
            func[| FUNC_DRAW] = grid_to_surface(grid);
        }
        if (l_level > 1)
        {
            grid = ds_grid_create(3, 3);
            ds_grid_set_region(grid, 0, 0, 2, 2, 0);
            grid[# 1, 0] = 1;
            grid[# 0, 1] = 1;
            grid[# 1, 1] = 1;
            grid[# 1, 2] = 1;
            grid[# 2, 1] = 1;
            var func = ds_list_find_value(l_list[| GADGET_FUNC], 1);
            func[| FUNC_GRID] = grid;
            func[| FUNC_DRAW] = grid_to_surface(grid);
        }
        if (l_level > 2)
        {
            grid = ds_grid_create(3, 3);
            ds_grid_set_region(grid, 0, 0, 2, 2, 1);
            var func = ds_list_find_value(l_list[| GADGET_FUNC], 2);
            func[| FUNC_GRID] = grid;
            func[| FUNC_DRAW] = grid_to_surface(grid);
        }
        if (l_level > 3)
        {
            grid = ds_grid_create(5, 5);
            ds_grid_set_region(grid, 0, 0, 4, 4, 0);
            grid[# 1, 0] = 1;
            grid[# 3, 0] = 1;
            grid[# 0, 1] = 1;
            grid[# 2, 1] = 1;
            grid[# 4, 1] = 1;
            grid[# 1, 2] = 1;
            grid[# 3, 2] = 1;
            grid[# 0, 3] = 1;
            grid[# 2, 3] = 1;
            grid[# 4, 3] = 1;
            grid[# 1, 4] = 1;
            grid[# 3, 4] = 1;
            grid[# 2, 2] = 1;
            var func = ds_list_find_value(l_list[| GADGET_FUNC], 3);
            func[| FUNC_GRID] = grid;
            func[| FUNC_DRAW] = grid_to_surface(grid);
        }
        break;
    }
    case GT_ARMOR:
    case GT_RADAR:
    case GT_JAMMER:
    {
        var figure_num = 0;
        switch (l_level)
        {
            case 1:
                {
                    figure_num = 3;
                    break;
                }
            case 2:
                {
                    figure_num = 5;
                    break;
                }
            case 3:
                {
                    figure_num = 7;
                    break;
                }
            case 4:
                {
                    figure_num = 8;
                    break;
                }
        }
        for (var i = 0; i < figure_num; i++)
        {
            var func = function_create();
            ds_list_add(l_list[| GADGET_FUNC], func);
            var grid = figure_create();
            func[| FUNC_GRID] = grid;
            func[| FUNC_DRAW] = grid_to_surface(grid);
        }
        break;
    }
}
l_list[| GADGET_NAME] = l_name;
l_list[| GADGET_ACCESS] = ds_list_create();
return l_list;
