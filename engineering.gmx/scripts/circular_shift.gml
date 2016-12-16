///circular_shift(number, bit_number, shift)
var l_number = argument0;
var l_bit_number = argument1;
var l_shift = argument2;
if (l_shift < 0)
{
    l_shift = abs(l_shift);
    var l_mask = power(2, l_shift) - 1;
    var l_buf_data = l_number & l_mask;
    l_number = l_number >> l_shift;
    l_number += (l_buf_data << (l_bit_number - l_shift));
}else if (l_shift > 0)
{   
    var l_mask = (power(2, l_shift) - 1) << (l_bit_number - l_shift);
    var l_buf_data = l_number & l_mask;
    l_number = l_number << l_shift;
    l_number += (l_buf_data >> (l_bit_number - l_shift));
}
var l_mask = power(2, l_bit_number) - 1;
l_number &= l_mask;
return l_number;
