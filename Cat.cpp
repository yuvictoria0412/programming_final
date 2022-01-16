#include "Cat.h"
#include "Window.h"
#include <iostream>
ALLEGRO_BITMAP* Cat::cat_status_hungry = al_load_bitmap("./pictures/hungry.jpg");
ALLEGRO_BITMAP* Cat::cat_status_dirty = al_load_bitmap("./pictures/dirty.jpg");
ALLEGRO_BITMAP* Cat::cat_status_boring = al_load_bitmap("./pictures/play.jpg");
ALLEGRO_BITMAP* Cat::cat_status_touchme = al_load_bitmap("./pictures/touch.jpg");
ALLEGRO_BITMAP* Cat::cat_status_seeme = al_load_bitmap("./pictures/cat.jpg");
ALLEGRO_BITMAP* Cat::cat_breed_1 = al_load_bitmap("./breed/cat1.jpg");
const int gapX = 40, gapY = 30;
Cat::Cat() {
    circle = new Circle(0, 0, 10);
    cat_status[HUNGRY] = 0;
    cat_status[DIRTY] = 0;
    breed = rand()%1 + 1;
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
}

void Cat::setXY(int x, int y) {
    circle->x = x;
    circle->y = y;
}
bool Cat::getting_hungry() {
    if (cat_status[HUNGRY] >= not_hungry ) {
        cat_status[HUNGRY] = -1; // play game

        return 0;
    }
    else if ( cat_status[HUNGRY] == -1 && cat_status[DIRTY] != -1) return 0;
    else {
        cat_status[HUNGRY]++;
        return 1;
    }
}

bool Cat::getting_dirty() {
//    std::cout << "getting dirty : " << cat_status[DIRTY] << std::endl;
    if (cat_status[DIRTY] >= not_dirty && cat_status[HUNGRY] != -1) {
//        std::cout << "case 1" << std::endl;
        cat_status[DIRTY] = -1; // play game
//        draw_cat_status(DIRTY);
        return 0;
    }
    else if (cat_status[DIRTY] >= not_dirty && cat_status[HUNGRY] == -1) {
//        std::cout << "case 2" << std::endl;
        return 1;
    }
    else if (cat_status[DIRTY] >= 0){
//        std::cout << "case 3" << std::endl;
        cat_status[DIRTY]++;
        return 1;
    }
    else if (cat_status[DIRTY] == -1) {
//        draw_cat_status(DIRTY);
        return 0;
    }
}

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
    switch (breed) {
    case 1:
        if (cat_breed_1 == NULL)
            cat_breed_1 = al_load_bitmap("./breed/cat1.jpg");
        al_draw_scaled_bitmap(cat_breed_1, 0,0,al_get_bitmap_width(cat_breed_1),al_get_bitmap_width(cat_breed_1),circle->x-20, circle->y-35, 100, 100, 0);
        break;
    }
    return;
}
