///gridded_part_set_internal_outputs();
for (var l_i = 0; l_i < width; l_i++)
{
    for (var l_j = 0; l_j < height; l_j++)
    {
        if (l_i > 0)
        {
            grid_outputs[# l_i, l_j] |= LEFT;
        }
        if (l_j > 0)
        {
            grid_outputs[# l_i, l_j] |= UP;
        }
        if (l_i < (width - 1))
        {
            grid_outputs[# l_i, l_j] |= RIGHT;
        }
        if (l_j < (height - 1))
        {
            grid_outputs[# l_i, l_j] |= DOWN;
        }
    }
}
