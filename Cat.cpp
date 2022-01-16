#include "Cat.h"
#include "Window.h"

ALLEGRO_BITMAP* Cat::cat_status_hungry = al_load_bitmap("./pictures/hungry.jpg");
ALLEGRO_BITMAP* Cat::cat_status_dirty = al_load_bitmap("./pictures/dirty.jpg");
ALLEGRO_BITMAP* Cat::cat_status_boring = al_load_bitmap("./pictures/play.jpg");
ALLEGRO_BITMAP* Cat::cat_status_touchme = al_load_bitmap("./pictures/touch.jpg");
ALLEGRO_BITMAP* Cat::cat_status_seeme = al_load_bitmap("./pictures/cat.jpg");
ALLEGRO_BITMAP* Cat::cat_breed_1 = al_load_bitmap("./breed/cat1.jpg");

Cat::Cat() {
    circle = new Circle(0, 0, 10);
    cat_status[HUNGRY] = 0;
    cat_status[DIRTY] = 0;
    breed = rand()%1 + 1;
//    cout << "breed" << breed << endl;
}

void Cat::setXY(int x, int y) {
    circle->x = x;
    circle->y = y;
}
bool Cat::getting_hungry() {
    if (cat_status[HUNGRY] >= not_hungry) {
        cat_status[HUNGRY] = -1; // play game
        draw_cat_status(HUNGRY);
        return 0;
    }
    else {
        cat_status[HUNGRY]++;
        return 1;
    }
}

bool Cat::getting_dirty() {
    if (cat_status[DIRTY] >= not_dirty && cat_status[HUNGRY] != -1) {
        cat_status[DIRTY] = -1; // play game
        draw_cat_status(DIRTY);
        return 0;
    }
    else if (cat_status[DIRTY] >= not_dirty && cat_status[HUNGRY] == -1) {
        return 1;
    }
    else {
        cat_status[DIRTY]++;
        return 1;
    }
}

void Cat::draw_cat_status(int i) {
    switch(i) {
        case HUNGRY:
            al_draw_bitmap(cat_status_hungry, circle->x, circle->x, 0);
            break;
        case DIRTY:
            al_draw_bitmap(cat_status_dirty, circle->x, circle->x, 0);
            break;
        case BORING:
            al_draw_bitmap(cat_status_boring, circle->x, circle->x, 0);
            break;
        case TOUCHME:
            al_draw_bitmap(cat_status_touchme, circle->x, circle->x, 0);
            break;
        case SEEME:
            al_draw_bitmap(cat_status_seeme, circle->x, circle->x, 0);
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
