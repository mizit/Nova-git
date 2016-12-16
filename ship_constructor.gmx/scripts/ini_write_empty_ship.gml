///ini_write_empty_ship(name);
for (var i = 0; i < 7; i++)
{
    for (var j = 0; j < 7; j++)
    {
        ini_write_real(argument0, string(i) + "x" + string(j), 0);
    }
}
