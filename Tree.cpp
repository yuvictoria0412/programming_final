#include "Tree.h"

#include <iostream>
#define GETW al_get_bitmap_width
#define GETH al_get_bitmap_height
using namespace std;
std::vector<ALLEGRO_BITMAP*> trees;

bool init2 = 0;

Tree::Tree(int a, int b) {
    circle = new Circle(0, 0, 10);
    circle->x = a;
    circle->y = b;
//    cout << "fffffffffffffffffffff" << endl;
    breed = rand() % tree_size;
//    cout << "vvvvvvvvvvvvvvvvvvvvv" << endl;
    if (!init2) {
//        cout << "init2" << endl;
        trees.reserve(tree_size);
        for (int i = 1; i <= tree_size; i++) {
            char pic_name[20];
            sprintf(pic_name, "./tree/%d.png", i);
            trees[i-1] = al_load_bitmap(pic_name);
        }
        init2 = 1;
    }
}

void Tree::Draw() {
    al_draw_scaled_rotated_bitmap(trees[breed], GETW(trees[breed]), GETH(trees[breed]), circle->x, circle->y, 0.2, 0.2, 0, 0);
}
