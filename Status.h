#ifndef STATUS_H_INCLUDED
#define STATUS_H_INCLUDED

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "Object.h"
#include "Circle.h"
#include "global.h"

#define WHITE al_map_rgb(255, 255, 255)
#define BLACK al_map_rgb(0, 0, 0)
#define super_user_score 0
class Status : public Object
{
public:
    Status();
    virtual ~Status();

    void Reset();
    void Draw();

    // Check if current coin is not less than needed coin
    bool Enough_Food(int cost);
    void Change_Coin(int change) { Coin += change; }
    void Change_Food(int change) { Food += change; }
//    bool add_score(int add_score = 1);
    void Gain_Score(int);

    int getScore() { return Score; }
    int getCoin() { return Coin; }
    int getFood() { return Food; }

private:
    ALLEGRO_BITMAP *heart = NULL;
    ALLEGRO_FONT *statusFont;
    int Score = 0;
    int Coin = 0;
    int Food = 0;

};

#endif // STATUS_H_INCLUDED
