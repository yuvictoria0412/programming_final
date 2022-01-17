#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include "Circle.h"

class Object {
public:
    Object() {}
    ~Object() {}

    // pure function for drawing object
    virtual void Draw() = 0;

    int getX() { return circle->x; }
    int getY() { return circle->y; }
    int getRadius() { return circle->r; }
    void changeXY(int a,int b) {circle->x += a, circle->y += b;}
    Circle* getCircle() const { return circle; }

protected:
    Circle *circle;

};

#endif // OBJECT_H_INCLUDED
