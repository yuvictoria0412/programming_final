#include "Cat.h"
#include "Window.h"
#include <iostream>
using namespace std;
ALLEGRO_BITMAP* Cat::cat_status_hungry = al_load_bitmap("./pictures/hungry.png");
ALLEGRO_BITMAP* Cat::cat_status_dirty = al_load_bitmap("./pictures/dirty.png");
ALLEGRO_BITMAP* Cat::cat_status_boring = al_load_bitmap("./pictures/play.png");
ALLEGRO_BITMAP* Cat::cat_status_touchme = al_load_bitmap("./pictures/touch.png");
ALLEGRO_BITMAP* Cat::cat_status_seeme = al_load_bitmap("./pictures/boring.png");
//ALLEGRO_BITMAP* Cat::cat_breed_1 = al_load_bitmap("./breed/cat1.jpg");
#define kind_of_cat 5
#define gif_count 2
std::vector<std::vector<ALLEGRO_BITMAP*>*> cat_breeds;
std::vector<std::vector<ALLEGRO_BITMAP*>*> cat_see_cat;
#define index_i 5
#define index_j 4
bool init = 0;
const int gapX = 40, gapY = 30;

Cat::Cat() {
    circle = new Circle(0, 0, 10);
    cat_status[HUNGRY] = 0;
    cat_status[DIRTY] = 0;
    cat_status[SEEME] = 0;
    breed = rand()%5;
    already_put = 0;
    frequency = 50;
    frequency2 = 10;
    see_cat = 0;

//    cat_status_hungry = al_load_bitmap("./pictures/hungry.png");
    if(cat_status_seeme == NULL)
        cat_status_seeme = al_load_bitmap("./pictures/boring.png");
    if(cat_status_dirty == NULL)
        cat_status_dirty = al_load_bitmap("./pictures/dirty.png");
    if(cat_status_hungry == NULL)
        cat_status_hungry = al_load_bitmap("./pictures/hungry.png");
    if(cat_status_boring == NULL)
        cat_status_boring = al_load_bitmap("./pictures/play.png");
    if(cat_status_touchme == NULL)
        cat_status_touchme = al_load_bitmap("./pictures/touch.png");
//    cout << "breed" << breed << endl;

    number = 0;
    number2 = 0;


    if (cat_touch.empty()) {
        char pic_name[19];
        cat_touch.reserve(5);
        for (int i = 1; i <= 5; i++) {
            sprintf(pic_name, "./touch_me/%d.png", i);
            cat_touch[i-1] = al_load_bitmap(pic_name);
        }
    }
    if (r_p_y_game.empty()) {
        char pic_name[19];
        r_p_y_game.reserve(3);
        for (int i = 1; i <= 3; i++) {
            sprintf(pic_name, "./rock/%d.png", i);
            r_p_y_game[i-1] = al_load_bitmap(pic_name);
        }
    }

    if (!init && cat_breeds.empty()) {
        cat_breeds.reserve(kind_of_cat);
        for (int i = 1; i <= kind_of_cat; i++) {
            cat_breeds[i-1] = new std::vector<ALLEGRO_BITMAP*>(gif_count);
//            cout << "i" << endl;
            cout << "loading..." << endl;
            for (int j = 1; j <= gif_count; j++) {
//                cout << "j" << endl;
                char pic_name[19];
                sprintf(pic_name, "./breed/h%d-%d.png", i, j);
                (*cat_breeds[i-1])[j-1] = al_load_bitmap(pic_name);
//                (*cat_breeds[i-1])[j-1] = al_load_bitmap("./breed/1-1.png");
            }
        }

        cat_see_cat.reserve(index_i);
        for (int i = 1; i <= index_i; i++) {
            cat_see_cat[i-1] = new std::vector<ALLEGRO_BITMAP*>(index_j);
            cout << "loading..." << endl;
            for (int j = 1; j <= index_j; j++) {
//                cout << "loading..." << endl;
                char pic_name[19];
                sprintf(pic_name, "./breed/%d-%d.png", i, j);
                (*cat_see_cat[i-1])[j-1] = al_load_bitmap(pic_name);
//                (*cat_breeds[i-1])[j-1] = al_load_bitmap("./breed/1-1.png");
            }
        }

        init = 1;
    }
    cout << "finished loading" << endl;
}
Cat::~Cat() {

    for (int s = cat_touch.size() - 1, i = s; i >= 0; --i) {
        al_destroy_bitmap(cat_touch[i]);
    }

    for (int s = r_p_y_game.size() - 1, i = s; i >= 0; --i) {
        al_destroy_bitmap(r_p_y_game[i]);
    }

    if (init) {
        al_destroy_bitmap(cat_status_hungry);
        al_destroy_bitmap(cat_status_boring);
        al_destroy_bitmap(cat_status_dirty);
        al_destroy_bitmap(cat_status_seeme);
        al_destroy_bitmap(cat_status_touchme);

        for (int i = kind_of_cat - 1; i >= 0; i--) {
            for (int j = gif_count - 1; j >= 0; j--) {
                al_destroy_bitmap((*cat_breeds[i])[j]);
            }
            delete cat_breeds[i];
        }

        for (int i = index_i - 1; i >= 0; i--) {
            for (int j = index_j - 1; j >= 0; j--) {
                al_destroy_bitmap((*cat_see_cat[i])[j]);
            }
            delete cat_see_cat[i];
        }
        init = 0;
    }
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
bool Cat::touch_me() {
    if ((rand() % 6) == 1 && cat_status[TOUCHME] != -1){
        status_queue.push(TOUCHME);
        cat_status[TOUCHME] = -1;
    }
    return 1;
}
bool Cat::see_me(){
    if ((rand() % 6) == 1 && cat_status[SEEME] != -1){
//        cout << "push boredf\n";
        status_queue.push(SEEME);
        cat_status[SEEME] = -1;
    }
    return 1;
};
bool Cat::getting_bored(){
    if ((rand() % 20 - 18) && cat_status[BORING] != -1){
//        cout << "push boredf\n";
        status_queue.push(BORING);
        cat_status[BORING] = -1;
    }
    return 1;
}

void Cat::draw_cat_status(int i) {
    float scale = 0.2;
    switch(i) {
        case HUNGRY:
            al_draw_scaled_rotated_bitmap( cat_status_hungry, al_get_bitmap_width(cat_status_hungry)/2, al_get_bitmap_height(cat_status_hungry)/2,
                                           circle->x + gapX + 50, circle->y - 45*2, scale, scale, 0, 0);
            break;
        case DIRTY:
            al_draw_scaled_rotated_bitmap( cat_status_dirty, al_get_bitmap_width(cat_status_dirty)/2, al_get_bitmap_height(cat_status_dirty)/2,
                                           circle->x + gapX  + 50, circle->y - 45*2, scale, scale, 0, 0);
            break;
        case BORING:
            al_draw_scaled_rotated_bitmap( cat_status_boring, al_get_bitmap_width(cat_status_boring)/2, al_get_bitmap_height(cat_status_boring)/2,
                                           circle->x + gapX  + 50, circle->y - 45*2,  scale, scale, 0, 0);
            break;
        case TOUCHME:
            al_draw_scaled_rotated_bitmap(  cat_status_touchme, al_get_bitmap_width(cat_status_touchme)/2, al_get_bitmap_height(cat_status_touchme)/2,
                                           circle->x + gapX  + 50, circle->y - 45*2,  scale, scale, 0, 0);
            break;
        case SEEME:
            al_draw_scaled_rotated_bitmap( cat_status_seeme, al_get_bitmap_width(cat_status_seeme)/2, al_get_bitmap_height(cat_status_seeme)/2,
                                           circle->x + gapX + 50, circle->y - 45*2,  scale, scale, 0, 0);
            break;
    }

}

void Cat::Draw() {
    if (see_cat) {
        al_draw_scaled_rotated_bitmap((*cat_see_cat[breed])[number2/frequency2], al_get_bitmap_width((*cat_see_cat[breed])[number2/frequency2])/2,
                                      al_get_bitmap_height((*cat_see_cat[breed])[number2/frequency2])/2, window_width/2, window_height/2-150  , 0.1, 0.1, 0, 0);
        if (number2 == index_j*frequency2-1) number2 = 0;
        else number2++;
    }
    else if (already_put) {
//        cout << "already put" << endl;
        al_draw_scaled_rotated_bitmap((*cat_breeds[breed])[number/frequency], al_get_bitmap_width((*cat_breeds[breed])[number/frequency])/2, al_get_bitmap_height((*cat_breeds[breed])[number/frequency])/2, circle->x, circle->y, 0.3, 0.3, 0, 0);
        if (number == gif_count*frequency-1) number = 0;
        else number++;
    }
    else {
        cout << "putting " << endl;
        al_draw_scaled_rotated_bitmap((*cat_breeds[breed])[0], al_get_bitmap_width((*cat_breeds[breed])[0])/2, al_get_bitmap_height((*cat_breeds[breed])[0])/2, circle->x, circle->y, 0.3, 0.3, 0, 0);
    }

    return;
}
