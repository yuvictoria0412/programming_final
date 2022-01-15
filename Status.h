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

class Status : public Object
{
public:
    Status();
    virtual ~Status();

    void Reset();
    void Draw();

    // Detect if cursor hovers over any of tower on menu
    // If so, return its type
    // Otherwise, return -1
//    int MouseIn(int, int);

    // static function that detect if one point is on a line
    // This function is just used to simplify "MouseIn"
//    static bool isInRange(int, int, int);

    // Check if current coin is not less than needed coin
    bool Enough_Food(int cost){return(Food - cost >= 0);}
    void Change_Coin(int change) { Coin += change; }
    void Change_Food(int change) { Food += change; }
//    bool add_score(int add_score = 1);
    void Gain_Score(int);

//    int getTowerCoin(int type) { return need_coin[type]; }
    int getScore() { return Score; }
    int getCoin() { return Coin; }
    int getFood() { return Food; }
//    int getKilled() { return killedMonster; }

private:
//    std::vector<ALLEGRO_BITMAP*> menu_tower;
    ALLEGRO_BITMAP *heart = NULL;
    ALLEGRO_FONT *statusFont;
//    int HealthPoint = 10;
//    int killedMonster = 0;
    int Score = 0;
    int Coin = 0;
    int Food = 0;
//    int selectedTower = -1;
//    int need_coin[Num_TowerType] = {-5, -10, -20, -40, -70};
};

#endif // STATUS_H_INCLUDED
