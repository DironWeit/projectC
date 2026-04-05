/* gui.h */


int gui_init();
void gui_draw(int pole[4][4], int score, int best_score, const char* best_date, int show_lost, int lost_score);
void draw_tile(int value, int x, int y);

int gui_handle_input(int pole[4][4], int *score, int *show_lost);
void gui_destroy();
