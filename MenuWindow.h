#ifndef MENUWINDOW_H_INCLUDED
#define MENUWINDOE_H_INCLUDED

#include "Window.h"

#include <stdio.h>
class MenuWindow : protected Window {
public:
    MenuWindow();
    void game_init();
    void game_reset();
    void game_play();
    void game_begin();
    int game_update();
    void game_destroy();
    void draw_running_map();
    int process_event();
    void draw_menu(bool);
    bool entering_name();


private:
    ALLEGRO_BITMAP *playbutton;
};

#endif // MENUWINDOW_H_INCLUDED
