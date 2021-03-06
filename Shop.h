#ifndef SHOP_H_INCLUDED
#define SHOP_H_INCLUDED

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
#include <queue>
#include "Object.h"
#include "Circle.h"
#include "global.h"
#include "Window.h"

#define WHITE al_map_rgb(255, 255, 255)
#define BLACK al_map_rgb(0, 0, 0)
#define RED al_map_rgb(205,92,92)
#define WHITE al_map_rgb(255, 255, 255)
#define YELLOW al_map_rgb(245,199,26)
#define Num_ITEM 6
#define ADD_FOOD 100


enum {SHOP_ICON = 0, SHOP_EXIT, GET_CAT, BUY_FOOD, WATCH_AD, SKIP_AD};
class Shop : public Object
{
public:
    Shop();
    virtual ~Shop();

    void Reset();
    void Draw();

    // Detect if cursor hovers over any of tower on menu
    // If so, return its type
    // Otherwise, return -1
    int MouseIn(int, int);
    // static function that detect if one point is on a line
    // This function is just used to simplify "MouseIn"
    static bool isInRange(int, int, int);
    bool shop_clicked(int, int, int); // check if shop object is being clicked
    bool shop_status(){return shop_window_open;};
    void change_window_open(bool change){ shop_window_open = change;};
    // Check if current coin is not less than needed coin
    bool Enough_Coin(int, int);

    int costCoin(int type) { return need_coin[type]; }
    int selectedItem = -1;
    void play_video( int video_index,  ALLEGRO_DISPLAY* display );
    void play_gif( int gif_index,  ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE *gif_event_queue );
    void video_flip_display( ALLEGRO_VIDEO *video_local, ALLEGRO_DISPLAY* video_display_local,ALLEGRO_BITMAP *frame);
private:
    ALLEGRO_BITMAP *Shop_icon = NULL;
    ALLEGRO_FONT *shopFont;
    int shop_X, shop_Y; // location of shop icon on the screen
    int need_coin[Num_ITEM] = {0, 0, -1000, -40, 500}; // cost of each item
    bool shop_window_open = false;
    int object_position[Num_ITEM][2];
    int object_size[Num_ITEM][2];
};

#endif // SHOP_H_INCLUDED
