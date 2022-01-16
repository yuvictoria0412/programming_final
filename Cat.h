#ifndef CAT_H_INCLUDED
#define CAT_H_INCLUDED
#define not_hungry 100
#define not_dirty 200
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

#include <queue>
// too hungry minus score
// buy food minus food

enum {HUNGRY, DIRTY, BORING, TOUCHME, SEEME};

class Cat : protected Object {
public:
    Cat();
    void setXY(int, int, bool);
    void Draw();    // draw cat itself
    void draw_cat_status(int); // draw the button of cat's condition
    bool getting_hungry();  // update as timer counts
    bool getting_dirty();   // update as timer counts
    bool getting_bored();
    bool want_petting();
    bool see_me();

    int get_cat_status( int index ){ return cat_status[index];}
    void change_cat_status( int index, int change ){ cat_status[index] = change;}
    int cat_queue_top(){ return status_queue.front();}
    void cat_queue_pop(){ status_queue.pop();};
    void cat_queue_push(int i){ status_queue.push(i);};
    //new
    int cat_x(){ return circle->x;}
    int cat_y(){ return circle->y;}
    int cat_breed(){return breed;};
    int cat_freq(){return frequency;};
    int reward(int i){ return cat_score[i];};//reward for fufilling cat's need
    ALLEGRO_BITMAP *cat_pic(int i){ return cat_breed_1[i];};
    bool cat_queue_empty(){ return status_queue.empty();}
//    void hungry();
//    void game_hungry();
private:
    int cat_status[5];
    int cat_score[5]= { 50, 40, 30, 20, 10};
    int breed;
    bool already_put;
    int frequency;
    std::queue<int> status_queue;
    /*adjust*/
    static ALLEGRO_BITMAP *cat_status_hungry;
    static ALLEGRO_BITMAP *cat_status_dirty;
    static ALLEGRO_BITMAP *cat_status_boring;
    static ALLEGRO_BITMAP *cat_status_touchme;
    static ALLEGRO_BITMAP *cat_status_seeme;
    int number;//for cat draw gif
    std::vector<ALLEGRO_BITMAP*> cat_breed_1;
};

#endif // CAT_H_INCLUDED


