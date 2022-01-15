#include "Shop.h"
#include <iostream>
using namespace std;

#define offsetX 80
#define offsetY 50
#define page_w 700
#define page_h 700
const int ThumbWidth = 5;
const int ThumbHeight = 5;
const int gapX = 40, gapY = 30;
const int box_w = (page_w - 3*gapX)/2, box_h = 300; // size of the shop opened screen

Shop::Shop(){
    shop_window_open = false;
    Shop_icon = al_load_bitmap("./Shop/shop.png");
    shopFont = al_load_ttf_font("./font/msjhl.ttc",36,0);

    //set object position and its size (maybe better way to do so
    object_position[SHOP_ICON][0] = window_width - offsetX + al_get_bitmap_width(Shop_icon)/2;
    object_position[SHOP_ICON][1] = window_height - offsetY + al_get_bitmap_width(Shop_icon)/2;
//    object_position[SHOP_ICON] = [window_width - offsetX, window_height - offsetY] ;
    object_size[SHOP_ICON][0] = al_get_bitmap_width(Shop_icon);
    object_size[SHOP_ICON][1] = al_get_bitmap_width(Shop_icon);
    object_position[SHOP_EXIT][0] = window_width/2 +page_w/2;
    object_position[SHOP_EXIT][1] = window_height/2-page_h/2;
    object_size[SHOP_EXIT][0] = 30;
    object_size[SHOP_EXIT][1] = 30;
    object_position[GET_CAT][0] = gapX + window_width/2 -page_w/2 +box_w/2;
    object_position[GET_CAT][1] = window_height/2-page_h/2+gapY+box_h/2;
    object_size[GET_CAT][0] = object_size[BUY_FOOD][0] = box_w;
    object_size[GET_CAT][1] = object_size[BUY_FOOD][1] = box_h;
    object_position[BUY_FOOD][0] = object_position[GET_CAT][0] + object_size[GET_CAT][0] + gapX;
    object_position[BUY_FOOD][1] = object_position[GET_CAT][1];


    object_position[WATCH_AD][0] = window_width/2;
    object_position[WATCH_AD][1] = window_height/2 + 150;
    object_size[WATCH_AD][0] = box_w;
    object_size[WATCH_AD][1] = box_h/3;


}
Shop::~Shop(){
    al_destroy_bitmap(Shop_icon);
    al_destroy_font(shopFont);
}
void Shop::Reset(){
    shop_window_open = false;
}

void Shop::Draw(){
    char buffer[50];




//
//    sprintf(buffer, "Score: %d", Score);
//    al_draw_bitmap(heart, 30, 10, 0);
//    al_draw_text(statusFont, BLACK, 30 + 2*al_get_bitmap_width(heart), 5, 0, buffer);
    if( !shop_window_open){
        shop_X = window_width - offsetX;
        shop_Y = window_height - offsetY;
        al_draw_scaled_rotated_bitmap( Shop_icon, al_get_bitmap_width(Shop_icon)/2, al_get_bitmap_height(Shop_icon)/2,
                                       shop_X, shop_Y, 0.3, 0.3, 0, 0);
    }
    else{
//        cout << "draw shop\n";
        //page rectangle
        al_draw_rectangle(window_width/2 -page_w/2, window_height/2-page_h/2, window_width/2 +page_w/2, window_height/2 + page_h/2, BLACK, 2);
        //exit button
        al_draw_filled_circle(window_width/2 +page_w/2, window_height/2-page_h/2, 30, RED);
        al_draw_circle(window_width/2 +page_w/2, window_height/2-page_h/2, 31, BLACK, 3);//outline
        al_draw_line(window_width/2 +page_w/2 - 10, window_height/2-page_h/2+10, window_width/2 +page_w/2 + 10,  window_height/2-page_h/2-10,BLACK, 3);
        al_draw_line(window_width/2 +page_w/2 - 10, window_height/2-page_h/2-10, window_width/2 +page_w/2 + 10,  window_height/2-page_h/2+10,BLACK, 3);

        for( int box = GET_CAT; box <= WATCH_AD; box++ ){
            al_draw_rectangle(object_position[box][0]-object_size[box][0]/2, object_position[box][1]-object_size[box][1]/2,
                              object_position[box][0]+ object_size[box][0]/2, object_position[box][1]+object_size[box][0]/2, BLACK, 2);
        }
        sprintf(buffer, "GET CAT");
        al_draw_text(shopFont, BLACK,  object_position[GET_CAT][0] - object_size[GET_CAT][0]/2 + gapX + 40, object_position[GET_CAT][1]+gapY+5, 0, buffer);
        sprintf(buffer, "BUY FOOD");
        al_draw_text(shopFont, BLACK,  object_position[BUY_FOOD][0] - object_size[BUY_FOOD][0]/2 + gapX + 10, object_position[BUY_FOOD][1]+gapY+5, 0, buffer);
        sprintf(buffer, "WATCH AD");
        al_draw_text(shopFont, BLACK,  object_position[WATCH_AD][0] - object_size[WATCH_AD][0]/2 + gapX + 10, object_position[WATCH_AD][1]+gapY-5, 0, buffer);

    }
}
int Shop::MouseIn(int mouse_x, int mouse_y){}

// static function that detect if one point is on a line
// This function is just used to simplify "MouseIn"
bool Shop::isInRange(int point, int startPos, int length){
    if(point >= startPos - length && point <= startPos + length)
        return true;
    return false;
}
bool Shop::shop_clicked(int mouse_x, int mouse_y, int object){
//    cout << "shop is opened\n";
    if( isInRange( mouse_x, object_position[object][0], ThumbWidth + object_size[object][0]/2) &&
       isInRange( mouse_y, object_position[object][1], ThumbHeight+object_size[object][1]/2)){
        cout << "clciked "<< object<<"\n";
        if( object == SHOP_ICON) shop_window_open = true;
        else if( object == SHOP_EXIT) shop_window_open = false;
        return true;
    }
    else{
//        if( object == SHOP_ICON) shop_window_open = false;
        return false;
    }
}
// Check if current coin is not less than needed coin
bool Shop::Enough_Coin(int current_coin, int type){
    if(type < 2 || type >= Num_ITEM)
        return false;

    return (current_coin + need_coin[type] >= 0);
}
