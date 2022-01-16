#include "Status.h"


const int ThumbWidth = 50;
const int ThumbHeight = 50;
const int gapX = 40, gapY = 30;
const int offsetX = 80, offsetY = 150;
const int Initial_Coin = 1000;
const int Initial_Score = 100;

Status::Status(){
    if( usermode ){
        Coin = -1;
        Score = 0;
        Food = -1;
    }
    else{
        Coin = Initial_Coin;
        Score = Initial_Score;
        Food = 0;
    }


    heart = al_load_bitmap("./Status/love.png");

    statusFont = al_load_ttf_font("./font/Cute Letters.ttf",28,0);
}
Status::~Status(){
    al_destroy_bitmap(heart);
    al_destroy_font(statusFont);
}
void Status::Reset(){
    if( usermode ){
        Coin = -1;
        Score = -1;
        Food = -1;
    }
    else{
        Coin = Initial_Coin;
        Score = Initial_Score;
        Food = 0;
    }
}

void Status::Draw(){
    char buffer[50];
    al_draw_scaled_rotated_bitmap( heart, al_get_bitmap_width(heart)/2, al_get_bitmap_height(heart)/2, 30, 15, 1.5, 1.5, 0, 0);

    sprintf(buffer, "S C O R E : %d", Score);
    al_draw_text(statusFont, BLACK, 30 + 2*al_get_bitmap_width(heart), 5, 0, buffer);

    if( usermode) sprintf(buffer, "C O I N : *** ");
    else sprintf(buffer, "C O I N : %d", Coin);
    al_draw_text(statusFont, BLACK,  80 +2*al_get_bitmap_width(heart) + offsetX*2, 5, 0, buffer);

    if( usermode) sprintf(buffer, "F O O D : ***");
    else sprintf(buffer, "F O O D : %d", Food);
    al_draw_text(statusFont, BLACK, 110 +2*al_get_bitmap_width(heart) + offsetX*4, 5, 0, buffer);
}


void Status::Gain_Score(int scoreWorth){
    Score += scoreWorth;
}

bool Status::Enough_Food(int cost){
    if ( usermode ) return true;
    else return(Food - cost >= 0);
//    return(Food - cost >= 0);
}
