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
double start_time = 0, now_time= 0;
int mouse_x = 0, mouse_y = 0;
struct GIF{
    double start_time = 0;
    ALGIF_ANIMATION *gif = NULL;
    double get_time( double time ){
        if( start_time == 0) start_time = time;
        return time - start_time;
    }
}obj;
ALLEGRO_VIDEO *video1;
ALLEGRO_VIDEO *video2;
ALLEGRO_BITMAP *food;

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

    object_position[SKIP_AD][0] = window_width/2 -page_w/2;
    object_position[SKIP_AD][1] = window_height/2-page_h/2;
    object_size[SKIP_AD][0] = 30;
    object_size[SKIP_AD][1] = 30;
    food = al_load_bitmap("./Shop/food.png");
    al_init_video_addon();
    al_install_audio( );
    al_init_image_addon(); // initialize the image addon
    al_init_acodec_addon(); // initialize acodec addon

//    obj.gif = algif_load_animation("./Shop/video/cat1.gif");
//    ALGIF_ANIMATION *gif = algif_load_animation("./Shop/video/cat1.gif");


//    video1 = al_open_video("./Shop/video/5.ogv");
//    video2 = al_open_video("./Shop/video/6.ogv");

}
Shop::~Shop(){
    al_destroy_bitmap(Shop_icon);
    al_destroy_bitmap(food);
    al_destroy_font(shopFont);
}
void Shop::Reset(){
    shop_window_open = false;
}
void Shop::play_gif( int gif_index, ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE *gif_event_queue ){
    ALLEGRO_EVENT gif_event;
    ALLEGRO_BITMAP *frame = algif_get_bitmap( obj.gif, obj.get_time( al_get_time()));
    int count_gif = 0;
    while( frame && ++count_gif <1){
        al_wait_for_event(gif_event_queue, &gif_event);
        if(gif_event.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch(gif_event.keyboard.keycode) {
            case ALLEGRO_KEY_ESCAPE:
                count_gif = 1001;
                break;
            }
        }
        else{
            frame = algif_get_bitmap( obj.gif, obj.get_time( al_get_time()));
            al_draw_scaled_bitmap(frame, 0, 0, al_get_bitmap_width(frame), al_get_bitmap_height(frame),0, 0, al_get_display_width(display),al_get_display_height(display), 0);
            al_flip_display();
        }
    }
//    al_destroy_display(video_display);
}
void Shop::video_flip_display( ALLEGRO_VIDEO *video_local, ALLEGRO_DISPLAY* video_display_local,ALLEGRO_BITMAP *frame) {
    frame = al_get_video_frame(video_local);

    char buffer[50];
    if ( !frame ){
//        std::cout << "find bug bitmap\n";
        return;
    }
//    else std::cout << "normal\n";
    if ( !video_local ){
//        std::cout << "find bug video\n";
        return;
    }
    al_draw_scaled_bitmap(frame, 0, 0,al_get_bitmap_width(frame),
                          al_get_bitmap_height(frame),
                          // the position of result image
                          0, 0,
                          // the width and height of result image
                          al_get_display_width(video_display_local),
                          al_get_display_height(video_display_local), 0);
    now_time = al_get_time();
    int count_down = 5 - (now_time - start_time);

    if( count_down > 0){
        al_draw_filled_rectangle(window_width/2 -page_w/2-30, window_height/2-page_h/2,
                              window_width/2 -page_w/2+200, window_height/2-page_h/2 + 50, WHITE);
        al_draw_rectangle(window_width/2 -page_w/2-30, window_height/2-page_h/2,
                                  window_width/2 -page_w/2+200, window_height/2-page_h/2 + 50, BLACK, 2);
        sprintf(buffer, "S K I P   I N  %d", count_down);
//        sprintf(buffer, "P R E S S   E S C");
        al_draw_text(shopFont, BLACK, window_width/2 -page_w/2+80, window_height/2-page_h/2+10, ALLEGRO_ALIGN_CENTRE, buffer);

    }
    else{ //exit button
        al_draw_filled_circle(object_position[SKIP_AD][0], object_position[SKIP_AD][1], object_size[SKIP_AD][0], RED);
        al_draw_circle(object_position[SKIP_AD][0], object_position[SKIP_AD][1],object_size[SKIP_AD][0]+1, BLACK, 3);//outline
        al_draw_line(window_width/2 -page_w/2 - 10, window_height/2-page_h/2+10, window_width/2 -page_w/2 + 10,  window_height/2-page_h/2-10,BLACK, 3);
        al_draw_line(window_width/2 -page_w/2 - 10, window_height/2-page_h/2-10, window_width/2 -page_w/2 + 10,  window_height/2-page_h/2+10,BLACK, 3);
    }
    al_flip_display();

}

void Shop::play_video( int index,  ALLEGRO_DISPLAY* video_display  ){
    ALLEGRO_VIDEO *video;
    ALLEGRO_EVENT video_event;
    ALLEGRO_TIMER *video_timer;
    ALLEGRO_BITMAP *frame = NULL;
    ALLEGRO_EVENT_QUEUE *video_event_queue;

    video_event_queue = al_create_event_queue();
    video_timer = al_create_timer(1.0 / FPS);

    al_start_timer(video_timer);
    switch(index){
    case 1:
        video = al_open_video("./Shop/video/1.ogv");
        break;
    case 2:
        video = al_open_video("./Shop/video/2.ogv");
        break;
    case 3:
        video = al_open_video("./Shop/video/3.ogv");
        break;
    case 4:
        video = al_open_video("./Shop/video/4.ogv");
        break;
    case 5:
        video = al_open_video("./Shop/video/5.ogv");
        break;
    case 6:
        video = al_open_video("./Shop/video/6.ogv");
        break;
    }
    if( video )
        printf("read video succeed\n");
    else
        printf("read video fail!!!!\n");
    ALLEGRO_EVENT_SOURCE *temp = al_get_video_event_source(video);
    al_register_event_source(video_event_queue, al_get_display_event_source(video_display));
    al_register_event_source(video_event_queue, al_get_keyboard_event_source());
    al_register_event_source(video_event_queue, al_get_mouse_event_source());
    al_register_event_source( video_event_queue,  temp);
    al_register_event_source(video_event_queue, al_get_timer_event_source(video_timer));
    al_reserve_samples(1);
    al_start_video(video, al_get_default_mixer());
    int state = 1;
    start_time = al_get_time();
    now_time = start_time;
    while( state ){
        al_wait_for_event(video_event_queue, &video_event);
        if( video_event.type == ALLEGRO_EVENT_TIMER ) {
            video_flip_display(video, video_display, frame);
        }
        else if(video_event.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch(video_event.keyboard.keycode) {
            case ALLEGRO_KEY_ESCAPE:
                if( now_time - start_time >= 5 )state = 0;
                else if( usermode )state = 0;
                break;
            }
        }
        else if( video_event.type == ALLEGRO_EVENT_VIDEO_FINISHED ) {
            break;
        }
        else if(video_event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            if(video_event.mouse.button == 1) {
                if(shop_clicked(mouse_x, mouse_y, SKIP_AD))
                    state = 0;
            }
        }
        else if(video_event.type == ALLEGRO_EVENT_MOUSE_AXES){
            mouse_x = video_event.mouse.x;
            mouse_y = video_event.mouse.y;
        }
    }
    al_close_video(video);
    al_destroy_bitmap(frame);
    al_destroy_event_queue(video_event_queue);
    al_destroy_timer(video_timer);
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
        al_draw_filled_circle(object_position[SHOP_EXIT][0], object_position[SHOP_EXIT][1] , object_size[SHOP_EXIT][0], RED);
        al_draw_circle(object_position[SHOP_EXIT][0], object_position[SHOP_EXIT][1] , object_size[SHOP_EXIT][0]+1, BLACK, 3);//outline
        al_draw_line(window_width/2 +page_w/2 - 10, window_height/2-page_h/2+10, window_width/2 +page_w/2 + 10,  window_height/2-page_h/2-10,BLACK, 3);
        al_draw_line(window_width/2 +page_w/2 - 10, window_height/2-page_h/2-10, window_width/2 +page_w/2 + 10,  window_height/2-page_h/2+10,BLACK, 3);

        for( int box = GET_CAT; box <= WATCH_AD; box++ ){
            if( box == WATCH_AD) al_draw_filled_rectangle(object_position[box][0]-object_size[box][0]/2, object_position[box][1]-object_size[box][1]/2,
                              object_position[box][0]+ object_size[box][0]/2, object_position[box][1]+object_size[box][0]/2, YELLOW);
            al_draw_rectangle(object_position[box][0]-object_size[box][0]/2, object_position[box][1]-object_size[box][1]/2,
                              object_position[box][0]+ object_size[box][0]/2, object_position[box][1]+object_size[box][0]/2, BLACK, 2);

        }
        sprintf(buffer, "G E T   C A T");
        al_draw_text(shopFont, BLACK,  object_position[GET_CAT][0], object_position[GET_CAT][1] + gapY*2, ALLEGRO_ALIGN_CENTRE, buffer);
        sprintf(buffer, "B U Y   F O O D");
        al_draw_text(shopFont, BLACK,  object_position[BUY_FOOD][0], object_position[BUY_FOOD][1] + gapY*2, ALLEGRO_ALIGN_CENTRE, buffer);
        al_draw_scaled_rotated_bitmap( food, al_get_bitmap_width(food)/2, al_get_bitmap_height(food)/2,
                                       object_position[BUY_FOOD][0], object_position[BUY_FOOD][1]-20, 0.6, 0.6, 0, 0);
        sprintf(buffer, "W A T C H   A D");
        al_draw_text(shopFont, BLACK,  object_position[WATCH_AD][0], object_position[WATCH_AD][1] + gapY, ALLEGRO_ALIGN_CENTRE, buffer);

    }
}
int Shop::MouseIn(int mouse_x, int mouse_y){return 0;}

// static function that detect if one point is on a line
// This function is just used to simplify "MouseIn"
bool Shop::isInRange(int point, int startPos, int length){
    if(point >= startPos - length && point <= startPos + length)
        return true;
    return false;
}
bool Shop::shop_clicked(int mouse_x, int mouse_y, int object){
    // cout << "shop is opened\n";
    if (object == SHOP_ICON) {
        if (mouse_x >= shop_X - 0.3 * al_get_bitmap_width(Shop_icon)/2 && mouse_x <= shop_X + 0.3 * al_get_bitmap_width(Shop_icon)/2) {
            if (mouse_y >= shop_Y - 0.3 * al_get_bitmap_height(Shop_icon)/2 && mouse_y <= shop_Y + 0.3 * al_get_bitmap_height(Shop_icon)/2) {
                return true;
            }
        }
        return false;
    }
    else if( isInRange( mouse_x, object_position[object][0], ThumbWidth + object_size[object][0]/2) &&
       isInRange( mouse_y, object_position[object][1], ThumbHeight+object_size[object][1]/2)){
        cout << "clciked "<< object<<"\n";
        return true;
    }
    else return false;
}
// Check if current coin is not less than needed coin
bool Shop::Enough_Coin(int current_coin, int type){
    if(type < 2 || type >= Num_ITEM)
        return false;
    if( usermode ) return true;
    else return (current_coin + need_coin[type] >= 0);
}

