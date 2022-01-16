#include "Cat.h"
#include "Window.h"
#include <iostream>
using namespace std;
ALLEGRO_BITMAP* Cat::cat_status_hungry = al_load_bitmap("./pictures/hungry.jpg");
ALLEGRO_BITMAP* Cat::cat_status_dirty = al_load_bitmap("./pictures/dirty.jpg");
ALLEGRO_BITMAP* Cat::cat_status_boring = al_load_bitmap("./pictures/play.jpg");
ALLEGRO_BITMAP* Cat::cat_status_touchme = al_load_bitmap("./pictures/touch.jpg");
ALLEGRO_BITMAP* Cat::cat_status_seeme = al_load_bitmap("./pictures/cat.jpg");
//ALLEGRO_BITMAP* Cat::cat_breed_1 = al_load_bitmap("./breed/cat1.jpg");
const int gapX = 40, gapY = 30;
Cat::Cat() {
    circle = new Circle(0, 0, 10);
    cat_status[HUNGRY] = 0;
    cat_status[DIRTY] = 0;
    cat_status[SEEME] = 0;
    breed = rand()%1 + 1;
    already_put = 0;
    frequency = 50;

    cat_status_hungry = al_load_bitmap("./pictures/hungry.jpg");
    if(cat_status_seeme == NULL)
        cat_status_seeme = al_load_bitmap("./pictures/cat.jpg");
    if(cat_status_dirty == NULL)
        cat_status_dirty = al_load_bitmap("./pictures/dirty.jpg");
    if(cat_status_hungry == NULL)
        cat_status_hungry = al_load_bitmap("./pictures/hungry.jpg");
    if(cat_status_boring == NULL)
        cat_status_boring = al_load_bitmap("./pictures/play.jpg");
    if(cat_status_touchme == NULL)
        cat_status_touchme = al_load_bitmap("./pictures/touch.jpg");
//    cout << "breed" << breed << endl;

    number = 0;
}

void Cat::setXY(int x, int y, bool put) {
    if (put) {
        already_put = 1;
    }
    circle->x = x;
    circle->y = y;
}
bool Cat::getting_hungry() {
    if (cat_status[HUNGRY] >= not_hungry ) {
        cat_status[HUNGRY] = -1; // play game
        status_queue.push(HUNGRY);
        return 0;
    }
    else if (cat_status[HUNGRY] == -1 && status_queue.empty()) {
        cat_status[HUNGRY] = 1;
        return 1;
    }
    else if (cat_status[HUNGRY] >= 0) {
        cat_status[HUNGRY]++;
        return 1;
    }
    else return 1;
}

bool Cat::getting_dirty() {
    if (cat_status[DIRTY] >= not_dirty ) {
        cat_status[DIRTY] = -1; // play game
        status_queue.push(DIRTY);
        return 0;
    }
    else if (cat_status[DIRTY] == -1 && status_queue.empty()) {
        cat_status[DIRTY] = 1;
        return 1;
    }
    else if (cat_status[DIRTY] >= 0) {
        cat_status[DIRTY]++;
        return 1;
    }
    else return 1;
}
bool Cat::getting_bored(){
//    cat_status[BORING] =   (rand() % (1 - 0 + 1) + 0);
//    status_queue.push(BORING);
//    return 1;
};
bool Cat::see_me(){
    if ((rand() % 10+1) && cat_status[SEEME] != -1){
        cout << "push boredf\n";
        status_queue.push(SEEME);
        cat_status[SEEME] = -1;
    }
    return 1;
};
bool Cat::want_petting(){};

void Cat::draw_cat_status(int i) {
    switch(i) {
        case HUNGRY:
            al_draw_scaled_rotated_bitmap( cat_status_hungry, al_get_bitmap_width(cat_status_hungry)/2, al_get_bitmap_height(cat_status_hungry)/2,
                                           circle->x + gapX, circle->y - 45, 0.08, 0.08, 0, 0);
            break;
        case DIRTY:
            al_draw_scaled_rotated_bitmap( cat_status_dirty, al_get_bitmap_width(cat_status_dirty)/2, al_get_bitmap_height(cat_status_dirty)/2,
                                           circle->x + gapX, circle->y - 45, 0.08, 0.08, 0, 0);
            break;
        case BORING:
            al_draw_scaled_rotated_bitmap( cat_status_boring, al_get_bitmap_width(cat_status_boring)/2, al_get_bitmap_height(cat_status_boring)/2,
                                           circle->x + gapX, circle->y - 45, 0.08, 0.08, 0, 0);
            break;
        case TOUCHME:
            al_draw_scaled_rotated_bitmap(  cat_status_touchme, al_get_bitmap_width(cat_status_touchme)/2, al_get_bitmap_height(cat_status_touchme)/2,
                                           circle->x + gapX, circle->y - 45, 0.08, 0.08, 0, 0);
            break;
        case SEEME:
            al_draw_scaled_rotated_bitmap( cat_status_seeme, al_get_bitmap_width(cat_status_seeme)/2, al_get_bitmap_height(cat_status_seeme)/2,
                                           circle->x + gapX, circle->y - 45, 0.08, 0.08, 0, 0);
            break;
    }

}

void Cat::Draw() {

//    cout << "draw cat" << endl;

    if (already_put) {
//        cout << "already_put" << endl;
        switch (breed) {
            case 1:
                al_draw_scaled_bitmap(cat_breed_1[number/frequency], 0, 0,al_get_bitmap_width(cat_breed_1[number/frequency]),al_get_bitmap_width(cat_breed_1[number/frequency]),circle->x-20, circle->y-35, 100, 100, 0);
            case 2:
                al_draw_scaled_bitmap(cat_breed_1[number/frequency], 0, 0,al_get_bitmap_width(cat_breed_1[number/frequency]),al_get_bitmap_width(cat_breed_1[number/frequency]),circle->x-20, circle->y-35, 100, 100, 0);
        }
        if (number == 4*frequency-1) number = 0;
        else number++;
    }
    else {
        char pic_name[20];
        switch (breed) {
        case 1:
            if (cat_breed_1.empty()) {
                cat_breed_1.reserve(4);
//                cout << "load cat"<< endl;
//                    sprintf(pic_name, "./breed/cat1-1.jpg");
//                    cat_breed_1[0] = al_load_bitmap(pic_name);
                for (int i = 1; i <= 4; i++) {
                    sprintf(pic_name, "./breed/cat1-%d.jpg", i);
                    cat_breed_1[i-1] = al_load_bitmap(pic_name);
                }
            }
            al_draw_scaled_bitmap(cat_breed_1[0], 0, 0,al_get_bitmap_width(cat_breed_1[0]),al_get_bitmap_width(cat_breed_1[0]),circle->x-20, circle->y-35, 100, 100, 0);
            break;
        }
    }

    return;
}

