///createLetter(letter);
var l_let = argument0;

var l_tmp = surface_create(obj_gui.surf_width, obj_gui.surf_height);
surface_set_target(l_tmp);
draw_text(obj_gui.surf_width / 2, obj_gui.surf_height / 2, l_let);
surface_reset_target();
return l_tmp;
