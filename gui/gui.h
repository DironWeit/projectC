/* gui.h */


int gui_init();
void gui_draw(int pole[4][4]);
void draw_tile(int value, int x, int y);

int gui_handle_input(int pole[4][4]);
void gui_destroy();