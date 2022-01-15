#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

#include "Window.h"
#include "Status.h"
#include "Shop.h"

#include <queue>

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
private:
    Status *status = NULL;
    Shop *shop = NULL;
    int mouse_x, mouse_y;
    bool redraw = false;


};

#endif // WINDOW_H_INCLUDED
