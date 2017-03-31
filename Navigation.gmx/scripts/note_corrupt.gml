///note_corrupt(msg, factor);
var l_msg = argument0;
var l_factor = argument1;
var l_ans = "";
for (var l_i = 0; l_i < string_length(l_msg); l_i++)
{
    var tmp = random(1);
    //show_message(string(l_factor) + " " + string(tmp));
    if (tmp <= l_factor)
    { 
        l_ans += string_char_at(l_msg, l_i + 1);
    }
    else
    {
        l_ans += ".";
    }
}
return l_ans;
