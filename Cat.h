#ifndef CAT_H_INCLUDED
#define CAT_H_INCLUDED
#define not_hungry 100
#define not_dirty 100000
#define want_to_play 3
#define want_to_touch 4
#define want
//new!
#define cat_status_num 5
#define status_image_size 50

#include "Object.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
// too hungry minus score
// buy food minus food

enum {HUNGRY, DIRTY, BORING, TOUCHME, SEEME};

class Cat : protected Object {
public:
    Cat();
    void setXY(int, int);
    void Draw();    // draw cat itself
    void draw_cat_status(int); // draw the button of cat's condition
    bool getting_hungry();  // update as timer counts
    bool getting_dirty();   // update as timer counts
    int get_cat_status( int index ){ return cat_status[index];}

    //new
    int cat_x(){ return circle->x;}
    int cat_y(){ return circle->y;}
//    void hungry();
//    void game_hungry();
private:
    int cat_status[5];
    int breed;
    /*adjust*/
    static ALLEGRO_BITMAP *cat_status_hungry;
    static ALLEGRO_BITMAP *cat_status_dirty;
    static ALLEGRO_BITMAP *cat_status_boring;
    static ALLEGRO_BITMAP *cat_status_touchme;
    static ALLEGRO_BITMAP *cat_status_seeme;

    static ALLEGRO_BITMAP *cat_breed_1;
};

#endif // CAT_H_INCLUDED


