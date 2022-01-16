#ifndef GAMEWINDOW_H_INCLUDED
#define GAMEWINDOW_H_INCLUDED

#include "Window.h"
#include "Status.h"
#include "Shop.h"
#include "Cat.h"
#include <queue>
#include <stdio.h>
#include <vector>

class GameWindow : protected Window {
public:
    GameWindow();
    void game_init();
    void game_reset();
    bool game_play();
    void game_begin();
    int game_update();
    void game_destroy();
    void draw_running_map();
    int process_event();
    bool clicked(int, int, int, int,  int, int);
    bool isInRange(int, int, int);
    bool put_a_cat();
protected:
    Status *status = NULL;
    Shop *shop = NULL;
    int mouse_x, mouse_y;
    bool redraw = false;
    std::vector<Cat*> cats;


};

#endif // WINDOW_H_INCLUDED
