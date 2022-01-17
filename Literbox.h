#ifndef LITERBOX_H_INCLUDED
#define LITERBOX_H_INCLUDED

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_video.h>
#include <allegro5/allegro_acodec.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "algif5/src/algif.h"

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
//using namespace std;
#include <queue>
#include "Object.h"
#include "Circle.h"
#include "global.h"
#include "Window.h"


#define WHITE al_map_rgb(255, 255, 255)
#define BLACK al_map_rgb(0, 0, 0)
#define RED al_map_rgb(205,92,92)
#define h_bound 100
#define w_bound 100
#define poop_state_num 2
struct Poop{
    int appearence;
    int poop_pic_count;
    int x, y;
    ALLEGRO_BITMAP *pic_buried;
    ALLEGRO_BITMAP *pic_half_buried;
};

class Literbox : public Object
{
public:
    Literbox();
    ~Literbox();

    void Reset();
    void Draw(){};
    void Draw_box(int, int, int);

    // Detect if cursor hovers over any of tower on menu
    // If so, return its type
    // Otherwise, return -1
    int MouseIn(int, int);
    // static function that detect if one point is on a line
    // This function is just used to simplify "MouseIn"
    static bool isInRange(int, int, int);
    bool clicked(int, int, int, int, int, int); // check if shop object is being clicked
    bool literbox_status(){return literbox_window_open;};
    void change_window_open(bool change){ literbox_window_open = change;};
    void game_play(ALLEGRO_EVENT_QUEUE  *event_queue);
private:
    ALLEGRO_BITMAP *box = NULL;
    std::vector<Poop> poops;
    std::vector<ALLEGRO_BITMAP*> shovel;
    std::vector<std::vector<ALLEGRO_BITMAP*>*> poops_pic;
    ALLEGRO_FONT *Font;
    ALLEGRO_FONT *LargeFont;
//    int shop_X, shop_Y; // location of shop icon on the screen
//    int need_coin[Num_ITEM] = {0, 0, -1000, -40, 500}; // cost of each item
    bool literbox_window_open = false;
//    int object_position[Num_ITEM][2];
//    int object_size[Num_ITEM][2];
};

#endif // LITERBOX_H_INCLUDED
