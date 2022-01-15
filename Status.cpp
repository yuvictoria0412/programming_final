#include "Status.h"


const int ThumbWidth = 50;
const int ThumbHeight = 50;
const int gapX = 40, gapY = 30;
const int offsetX = 80, offsetY = 150;
const int Initial_Coin = 1000;
const int Initial_Score = 100;

Status::Status(){
    Coin = Initial_Coin;
    Score = Initial_Score;

    heart = al_load_bitmap("./Status/love.png");

    statusFont = al_load_ttf_font("./font/msjhl.ttc",20,0);
}
Status::~Status(){
    al_destroy_bitmap(heart);
    al_destroy_font(statusFont);
}
void Status::Reset(){
    Coin = Initial_Coin;
    Score = Initial_Score;
}

void Status::Draw(){
    char buffer[50];

    sprintf(buffer, "Coin: %d", Coin);
    al_draw_text(statusFont, BLACK,  30 +2*al_get_bitmap_width(heart) + offsetX*2, 5, 0, buffer);

    sprintf(buffer, "Score: %d", Score);
    al_draw_bitmap(heart, 30, 10, 0);
    al_draw_text(statusFont, BLACK, 30 + 2*al_get_bitmap_width(heart), 5, 0, buffer);

    sprintf(buffer, "Food: %d", Food);
//    al_draw_bitmap(heart, 30, 10, 0);
    al_draw_text(statusFont, BLACK, 30 +2*al_get_bitmap_width(heart) + offsetX*4, 5, 0, buffer);
}


void Status::Gain_Score(int scoreWorth){
    Score += scoreWorth;
}
