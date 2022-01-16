#ifndef MENUWINDOW_H_INCLUDED
#define MENUWINDOE_H_INCLUDED

#include "Window.h"
#include <stdio.h>
class MenuWindow : protected Window {
public:
    MenuWindow();
    void game_init();
    bool game_play();
    void game_begin();
    void game_reset();
     int game_update();
    void game_destroy();
    void draw_running_map();
    int process_event();
    void draw_menu(bool);
    bool entering_name();
private:
    ALLEGRO_BITMAP *playbutton;
    bool correct_return;
};

#endif // MENUWINDOW_H_INCLUDED
