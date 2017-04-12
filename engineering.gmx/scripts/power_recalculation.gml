///power_recalculation(ds_grid);
var l_grid = argument0;
if (obj_on.image_index == 0)
{
    for (var l_i = 0; l_i < ds_grid_width(l_grid); l_i++)
    {
        for (var l_j = 0; l_j < ds_grid_height(l_grid); l_j++)
        {
            var l_a = l_grid[# l_i, l_j];
            ds_list_clear(l_a[| CELL_PS_LIST]);
        }
    }
    return 0;
}
var l_process_queue = ds_queue_create();
for (var l_i = 0; l_i < ds_grid_width(l_grid); l_i++)
{
    for (var l_j = 0; l_j < ds_grid_height(l_grid); l_j++)
    {
        var l_a = l_grid[# l_i, l_j];
        ds_list_clear(l_a[| CELL_PS_LIST]);
        if (l_a[| CELL_OBJECT])
        {
            if (object_get_parent(l_a[| CELL_OBJECT].object_index) == obj_power_parent)
            {
                ds_list_add(l_a[| CELL_PS_LIST], l_a[| CELL_OBJECT]);
                ds_queue_enqueue(l_process_queue, l_a);
            }
            else
            {
                ds_list_clear(l_a[| CELL_PS_LIST]);
            }
        }
        else
        {
            ds_list_clear(l_a[| CELL_PS_LIST]);
        }
    }
}
while (ds_queue_size(l_process_queue) > 0)
{
    var l_a = ds_queue_dequeue(l_process_queue);
    if (l_a[| CELL_X] > 0)
    {
        var l_checked = l_grid[# (l_a[| CELL_X] - 1), l_a[| CELL_Y]];
        if (l_a[| CELL_OUTPUTS] & LEFT) && (l_checked[| CELL_OUTPUTS] & RIGHT)
        {
            if (ds_list_complement_list(l_checked[| CELL_PS_LIST], l_a[| CELL_PS_LIST]))
            {
                ds_queue_enqueue(l_process_queue, l_checked);
            }
        }
    }
    if (l_a[| CELL_X] < (ds_grid_width(l_grid) - 1))
    {
        var l_checked = l_grid[# (l_a[| CELL_X] + 1), l_a[| CELL_Y]];
        if (l_a[| CELL_OUTPUTS] & RIGHT) && (l_checked[| CELL_OUTPUTS] & LEFT)
        {
            if (ds_list_complement_list(l_checked[| CELL_PS_LIST], l_a[| CELL_PS_LIST]))
            {
                ds_queue_enqueue(l_process_queue, l_checked);
            }
        }
    }
    if (l_a[| CELL_Y] > 0)
    {
        var l_checked = l_grid[# l_a[| CELL_X], (l_a[| CELL_Y] - 1)];
        if (l_a[| CELL_OUTPUTS] & UP) && (l_checked[| CELL_OUTPUTS] & DOWN)
        {
            if (ds_list_complement_list(l_checked[| CELL_PS_LIST], l_a[| CELL_PS_LIST]))
            {
                ds_queue_enqueue(l_process_queue, l_checked);
            }
        }
    }
    if (l_a[| CELL_Y] < (ds_grid_height(l_grid) - 1))
    {
        var l_checked = l_grid[# l_a[| CELL_X], (l_a[| CELL_Y] + 1)];
        if (l_a[| CELL_OUTPUTS] & DOWN) && (l_checked[| CELL_OUTPUTS] & UP)
        {
            if (ds_list_complement_list(l_checked[| CELL_PS_LIST], l_a[| CELL_PS_LIST]))
            {
                ds_queue_enqueue(l_process_queue, l_checked);
            }
        }
    }
}
ds_queue_destroy(l_process_queue);
