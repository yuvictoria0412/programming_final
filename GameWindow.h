#ifndef GAMEWINDOW_H_INCLUDED
#define GAMEWINDOW_H_INCLUDED

#include "Window.h"

class GameWindow : public Window {
public:
    GameWindow();
    void game_init();
    void game_reset();
    void game_play();
    void game_begin();
    int game_update();
    void game_destroy();
    void draw_running_map();
    int process_event();

};

#endif // GAMEWINDOW_H_INCLUDED
