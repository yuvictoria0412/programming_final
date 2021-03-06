#ifndef GAMEWINDOW_H_INCLUDED
#define GAMEWINDOW_H_INCLUDED

#include "Window.h"
#include "Status.h"
#include "Shop.h"
#include "Cat.h"
#include "Literbox.h"
#include "Tree.h"
#include <queue>
#include <stdio.h>
#include <string>
#include <vector>

#define feed_food 10
#define WHITE al_map_rgb(255, 255, 255)
#define BLACK al_map_rgb(0, 0, 0)
#define YELLOW al_map_rgb(245,199,26)
class GameWindow : protected Window {
public:
    GameWindow();
    ~GameWindow(){}
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

    //little games
    void see_cat(int);
    void hungry_cat(int);
    void touch_me(int);
    void rock_paper_scissors(int);
protected:
    Status *status = NULL;
    Shop *shop = NULL;
    Literbox *clean_cat = NULL;
    int mouse_x, mouse_y;
    std::vector<Tree*> trees;
    int error_message;
    bool redraw = false;
    std::vector<Cat*> cats;
    ALLEGRO_SAMPLE *sample;
    ALLEGRO_SAMPLE_INSTANCE *startSound;

};

#endif // WINDOW_H_INCLUDED
