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

static char const *filename_1;
static char const *filename_2;
static char const *filename_3;
static char const *filename_4;
static char const *filename_5;
static char const *filename_6;
ALLEGRO_VIDEO *video;
ALLEGRO_EVENT video_event;
ALLEGRO_TIMER *video_timer;
ALLEGRO_DISPLAY* video_display = NULL;
ALLEGRO_EVENT_QUEUE *video_event_queue;
Shop::Shop(){
    shop_window_open = false;
    Shop_icon = al_load_bitmap("./Shop/shop.png");
    shopFont = al_load_ttf_font("./font/Cute Letters.ttf",36,0);

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

    al_init_video_addon();
    al_install_audio( );
//    al_init_image_addon(); // initialize the image addon
    al_init_acodec_addon(); // initialize acodec addon


}
Shop::~Shop(){
    al_destroy_bitmap(Shop_icon);
    al_destroy_font(shopFont);
}
void Shop::Reset(){
    shop_window_open = false;
}
void video_init( int index ){
    //video addonm

    video_display = al_create_display(window_width, window_height);
    video_event_queue = al_create_event_queue();
    video_timer = al_create_timer(1.0 / FPS);
    al_set_window_position(video_display, 0, 0);

    al_start_timer(video_timer);
    filename_1 = "./Shop/video/1.ogv";
    filename_2 = "./Shop/video/2.ogv";
    filename_3 = "./Shop/video/3.ogv";
    filename_4 = "./Shop/video/4.ogv";
    filename_5 = "./Shop/video/5.ogv";
    filename_6 = "./Shop/video/6.ogv";
    const char *open_file;
    switch(index){
    case 1:
        open_file = filename_1;
        break;
    case 2:
        open_file = filename_2;
        break;
    case 3:
        open_file = filename_3;
        break;
    case 4:
        open_file = filename_4;
        break;
    case 5:
        open_file = filename_5;
        break;
    case 6:
        open_file = filename_6;
        break;
    }
    video = al_open_video(open_file);
    if( video )
        printf("read video succeed\n");
    else
        printf("read video fail!!!!\n");

    al_register_event_source(video_event_queue, al_get_display_event_source(video_display));
    al_register_event_source(video_event_queue, al_get_keyboard_event_source());
    al_register_event_source(video_event_queue, al_get_mouse_event_source());
    al_register_event_source( video_event_queue,  al_get_video_event_source(video));
    al_register_event_source(video_event_queue, al_get_timer_event_source(video_timer));
}
void video_begin(){
    al_reserve_samples(1);
    al_start_video(video, al_get_default_mixer());
    al_start_timer(video_timer);
}
void destroy_video(){
    al_destroy_display(video_display);
    al_destroy_event_queue(video_event_queue);
//    video_display = NULL;
//    video_event_queue = NULL;
//    video_event = NULL;
//    video_timer = NULL;
}
void video_flip_display() {
    ALLEGRO_BITMAP *frame = al_get_video_frame(video);
    // check if we get the frame successfully
    // Note the this code is necessary
    if ( !frame )
        return;
    // Display the frame.
    // rescale the frame into the size of screen
    al_draw_scaled_bitmap(frame,
                          // the rescale position of the frame
                          0, 0,
                          // the width and height you want to rescale
                          al_get_bitmap_width(frame),
                          al_get_bitmap_height(frame),
                          // the position of result image
                          0, 0,
                          // the width and height of result image
                          al_get_display_width(video_display),
                          al_get_display_height(video_display), 0);
    al_flip_display();
}

void Shop::play_video( int index ){
    video_init(index);
    video_begin();
    while( 1 ){
        al_wait_for_event(video_event_queue, &video_event);
        if( video_event.type == ALLEGRO_EVENT_TIMER ) {
            video_flip_display();
        } else if( video_event.type == ALLEGRO_EVENT_DISPLAY_CLOSE ) {
            video_flip_display();
            break;
        } else if( video_event.type == ALLEGRO_EVENT_VIDEO_FINISHED ) {
            break;
        }
    }
    destroy_video();
}
void Shop::Draw(){
    char buffer[50];
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
        sprintf(buffer, "G E T   C A T");
        al_draw_text(shopFont, BLACK,  object_position[GET_CAT][0], object_position[GET_CAT][1] + gapY*2, ALLEGRO_ALIGN_CENTRE, buffer);
        sprintf(buffer, "B U Y   F O O D");
        al_draw_text(shopFont, BLACK,  object_position[BUY_FOOD][0], object_position[BUY_FOOD][1] + gapY*2, ALLEGRO_ALIGN_CENTRE, buffer);
        sprintf(buffer, "W A T C H   A D");
        al_draw_text(shopFont, BLACK,  object_position[WATCH_AD][0], object_position[WATCH_AD][1] + gapY, ALLEGRO_ALIGN_CENTRE, buffer);

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
//        if( object == SHOP_ICON) shop_window_open = true;
//        else if( object == SHOP_EXIT) shop_window_open = false;
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
    if( usermode ) return true;
    else return (current_coin + need_coin[type] >= 0);
}
