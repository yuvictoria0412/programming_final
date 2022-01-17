#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

#include "Object.h"
#include "Window.h"
#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#define tree_size 2

class Tree : public Object {
public:
    Tree(int, int);
    void changeXY(int a, int b) {circle->x += a, circle->y += b;}
    void Draw();
private:
    int breed;
};

#endif // CAT_H_INCLUDED


