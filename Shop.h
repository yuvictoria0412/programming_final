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

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <queue>
#include "Object.h"
#include "Circle.h"
#include "global.h"

#define WHITE al_map_rgb(255, 255, 255)
#define BLACK al_map_rgb(0, 0, 0)
#define RED al_map_rgb(205,92,92)
#define Num_ITEM 5
#define ADD_FOOD 100


enum {SHOP_ICON = 0, SHOP_EXIT, GET_CAT, BUY_FOOD, WATCH_AD};
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

    // Check if current coin is not less than needed coin
    bool Enough_Coin(int, int);

    int costCoin(int type) { return need_coin[type]; }
    int selectedItem = -1;

private:
    ALLEGRO_BITMAP *Shop_icon = NULL;
    ALLEGRO_FONT *shopFont;
    int shop_X, shop_Y; // location of shop icon on the screen
    int need_coin[Num_ITEM] = {0, 0, -20, -40, 100}; // cost of each item
    bool shop_window_open = false;
    int object_position[Num_ITEM][2];
    int object_size[Num_ITEM][2];
};

#endif // SHOP_H_INCLUDED
