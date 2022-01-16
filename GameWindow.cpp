#include "GameWindow.h"
#include <iostream>
#include <time.h>
using namespace std;
#define WHITE al_map_rgb(255, 255, 255)
#define BLACK al_map_rgb(0, 0, 0)
#define min(a, b) ((a) < (b)? (a) : (b))
#define max(a, b) ((a) > (b)? (a) : (b))
const int ThumbWidth = 5;
const int ThumbHeight = 5;
ALLEGRO_BITMAP *pop_cat_open = NULL;
ALLEGRO_BITMAP *pop_cat_close = NULL;
GameWindow::GameWindow() {
    if (!al_init())
        show_err_msg(-1);

    printf("Game Initializing...\n");

    display = al_create_display(window_width, window_height);
    event_queue = al_create_event_queue();

    timer = al_create_timer(1.0 / FPS);

    if(timer == NULL)
        show_err_msg(-1);

    if (display == NULL || event_queue == NULL)
        show_err_msg(-1);

    al_init_primitives_addon();
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon(); // initialize the ttf (True Type Font) addon
    al_init_image_addon(); // initialize the image addon
    al_init_acodec_addon(); // initialize acodec addon

    al_install_keyboard(); // install keyboard event
    al_install_mouse();    // install mouse event
    al_install_audio();    // install audio event

    font = al_load_ttf_font("./font/Cute Letters.ttf",36,0); // load small font
    Medium_font = al_load_ttf_font("./font/Cute Letters.ttf", 24, 0); //load medium font
    Large_font = al_load_ttf_font("./font/Cute Letters.ttf", 60, 0); //load large font

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    pop_cat_open = al_load_bitmap("./popcat/open.jpg");
    pop_cat_close = al_load_bitmap("./popcat/close.jpg");
    game_init();
}
void GameWindow::game_init() {
    al_set_window_position(display, 0, 0);
    status = new Status();
    shop = new Shop();
}

void GameWindow::game_reset() {
    al_stop_timer(timer);
    status->Reset();
}
bool GameWindow::game_play() {
    int msg;

    srand(time(NULL));

    msg = -1;
    game_reset();
    game_begin();

    while(msg != GAME_EXIT)
    {
        msg = game_run();
    }

    show_err_msg(msg);
    return true;
}

void GameWindow::game_begin() {
    draw_running_map();
    al_start_timer(timer);
}


int GameWindow::game_update() {
    return GAME_CONTINUE;
}


void GameWindow::game_destroy() {
    game_reset();
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_font(font);
    al_destroy_font(Medium_font);
    al_destroy_font(Large_font);

    al_destroy_timer(timer);

    delete status;
    delete shop;
}
void GameWindow::see_cat(int cat_index){
    cout<<"see me\n";
    double start_time = al_get_time(), now_time = start_time;
    static int number = 0;
    int state = 1;
//    cout << "time "<< start_time << " "<< now_time<<endl;
    while( state && (now_time - start_time)<5.0){
        now_time = al_get_time();
//        cout << "now time "<< now_time<<endl;
        al_wait_for_event(event_queue, &event);
        if(event.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch(event.keyboard.keycode) {
            case ALLEGRO_KEY_ESCAPE:
                if(usermode) state = 0;
                break;
            }
        }
        else{//draw
            al_clear_to_color( WHITE );
            al_draw_rectangle(window_width/2 - 125 , window_height/2 - 50, window_width/2 +125, window_height/2 +80, BLACK, 2);
            al_draw_text(font, BLACK,  window_width/2 , window_height/2-20, ALLEGRO_ALIGN_CENTRE, "W A T C H   M E");
            int count_down = 5 - (now_time - start_time);
            char tmp[1];
            tmp[0] = count_down + '0';
            al_draw_text(font, BLACK,  window_width/2 , window_height/2+20, ALLEGRO_ALIGN_CENTRE, tmp);

            //cat
            int frequency = cats[cat_index]->cat_freq();

            switch (cats[cat_index]->cat_breed()) {
            case 1:
                al_draw_scaled_bitmap(cats[cat_index]->cat_pic(number/frequency), 0, 0,al_get_bitmap_width(cats[cat_index]->cat_pic(number/frequency)),
                                      al_get_bitmap_width(cats[cat_index]->cat_pic(number/frequency)),
                                      window_width/2 - 70 , window_height/2-200, 150, 150, 0);

            break;
            case 2:
                al_draw_scaled_bitmap(cats[cat_index]->cat_pic(number/frequency), 0, 0,al_get_bitmap_width(cats[cat_index]->cat_pic(number/frequency)),
                                      al_get_bitmap_width(cats[cat_index]->cat_pic(number/frequency)),
                                      window_width/2 - 70 , window_height/2-200, 150, 150, 0);
            break;
            }
            if (number == 4*frequency-1) number = 0;
            else number++;
            al_flip_display();
        }
    }
    cats[cat_index]->change_cat_status(SEEME, 1);
    status->Gain_Score(cats[cat_index]->reward(SEEME));

    draw_running_map();
//    cout <<"fini\n";
}
bool GameWindow::isInRange(int point, int startPos, int length){
    if(point >= startPos - length && point <= startPos + length)
        return true;
    return false;
}
bool GameWindow::clicked(int mouse_x, int mouse_y, int x, int y, int w, int h){
//    cout << "shop is opened\n";
    if( isInRange( mouse_x, x, ThumbWidth + w/2) &&
       isInRange( mouse_y, y, ThumbHeight+ h/2)){
        return true;
    }
    else{
        return false;
    }
}
// each drawing scene function
void GameWindow::draw_running_map() {
//    cout << "in draw map0\n";
    if( !shop->shop_status() ){ // shop closed
        al_clear_to_color( WHITE );
//        cout << "in draw map1\n";
        status->Draw();
        shop->Draw();
//        cout << "in draw map\n";
        for (auto meow : cats) {
            meow->Draw();
            if (!meow->cat_queue_empty()) {
//                cout << "cat status "<<meow->cat_queue_top()<<endl;
                meow->draw_cat_status(meow->cat_queue_top());
            }
        }
    }
    else{ // shop opened
        al_clear_to_color( WHITE );
        status->Draw();
        shop->Draw();
    }
    al_flip_display();
}
void GameWindow::touch_me(int cur) {
    int i = 0;
    int a = 0;
    int b = 0;

    while (1) {
        al_clear_to_color(WHITE);
        a = al_get_bitmap_width(cats[cur]->touch_pic(i));
        b = al_get_bitmap_height(cats[cur]->touch_pic(i));
        al_draw_scaled_bitmap(cats[cur]->touch_pic(i), 0, 0, a, b, window_width/2-360, window_height/2-300, 800, 600, 0);
        al_flip_display();

        al_wait_for_event(event_queue, &event);
        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            if (event.mouse.button == 1) {
                if (event.mouse.x >= 100 && event.mouse.x <= window_width - 100) {
                    if (event.mouse.y >= 100 && event.mouse.y <= window_height - 100) {
                        cout << "touch me little game clicked" << endl;
                        if (++i == 5) break;
                    }
                }
            }
        }
        else if(event.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch(event.keyboard.keycode) {
            case ALLEGRO_KEY_ESCAPE:
                if( usermode){
                    status->Gain_Score(cats[cur]->reward(TOUCHME));
                    return;
                }
                break;
            }
        }
    }
    status->Gain_Score(cats[cur]->reward(TOUCHME));
}
void GameWindow::hungry_cat(int cat_index){
    int picture = 1;
    int feed_count = 0;
    if( status->Enough_Food(feed_food)){
        al_draw_scaled_bitmap(pop_cat_open,0,0,
                              al_get_bitmap_width(pop_cat_open), al_get_bitmap_height(pop_cat_open),
                                      0  , 0, window_width, window_height, 0);
        al_flip_display();
        while( feed_count <= feed_food){
            al_wait_for_event(event_queue, &event);
            if(event.type == ALLEGRO_EVENT_KEY_DOWN) {
                switch(event.keyboard.keycode) {
                case ALLEGRO_KEY_ESCAPE:
                    if(usermode) feed_count += 10;
                    break;
                }
            }
            else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                if(event.mouse.button == 1) {


                    al_draw_scaled_bitmap(pop_cat_close,0,0,al_get_bitmap_width(pop_cat_open), al_get_bitmap_height(pop_cat_open),
                              0, 0, window_width, window_height, 0);
                    al_draw_filled_rectangle(window_width/2 - 125 , window_height/2 +170, window_width/2 +125, window_height/2 +320, WHITE);
                    al_draw_text(Large_font, BLACK,  window_width/2 , window_height/2+180, ALLEGRO_ALIGN_CENTRE, "A T E");

                    char tmp[3];
                    if( feed_count >= 10){
                        tmp[0] = feed_count /10+ '0';
                        tmp[1] = feed_count %10+ '0';
                    }
                    else tmp[0] = feed_count + '0';
                    al_draw_text(Large_font, BLACK,  window_width/2 , window_height/2+240, ALLEGRO_ALIGN_CENTRE, tmp);
                    al_flip_display();
                    al_rest(0.3);
                    feed_count ++;
                    al_draw_scaled_bitmap(pop_cat_open,0,0,al_get_bitmap_width(pop_cat_open), al_get_bitmap_height(pop_cat_open),
                                      0, 0, window_width, window_height, 0);
                    al_draw_filled_rectangle(window_width/2 - 125 , window_height/2 +170, window_width/2 +125, window_height/2 +320, WHITE);
                    al_draw_text(Large_font, BLACK,  window_width/2 , window_height/2+180, ALLEGRO_ALIGN_CENTRE, "A T E");

//                    char tmp[2];
                    if( feed_count >= 10){
                        tmp[0] = feed_count /10+ '0';
                        tmp[1] = feed_count %10+ '0';
                    }
                    else tmp[0] = feed_count + '0';
                    if( feed_count<= feed_food) al_draw_text(Large_font, BLACK,  window_width/2 , window_height/2+240, ALLEGRO_ALIGN_CENTRE, tmp);
                }
            }
            al_flip_display();
        }
        status->Change_Food(feed_food);
        status->Gain_Score(cats[cat_index]->reward(HUNGRY));
    }
    else{
        al_draw_filled_rectangle(window_width/2 - 125 , window_height/2 - 10, window_width/2 +125, window_height/2 +50, BLACK);
        al_draw_text(font, WHITE,  window_width/2 , window_height/2, ALLEGRO_ALIGN_CENTRE, "B U Y   F O O D");
        al_flip_display();
        al_rest(1.5);
        shop->change_window_open(true);
    }
}
void GameWindow::rock_paper_scissors(int index){
    while( 1 ){
        al_wait_for_event(event_queue, &event);
        if(event.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch(event.keyboard.keycode) {
            case ALLEGRO_KEY_ESCAPE:
                if(usermode){
                  status->Gain_Score(cats[index]->reward(BORING));
                  return;
                }
                break;
            }
        }
        else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            if(event.mouse.button == 1) {


                al_draw_scaled_bitmap(pop_cat_close,0,0,al_get_bitmap_width(pop_cat_open), al_get_bitmap_height(pop_cat_open),
                          0, 0, window_width, window_height, 0);
                al_draw_filled_rectangle(window_width/2 - 125 , window_height/2 +170, window_width/2 +125, window_height/2 +320, WHITE);
                al_draw_text(Large_font, BLACK,  window_width/2 , window_height/2+180, ALLEGRO_ALIGN_CENTRE, "A T E");

                char tmp[3];
                if( feed_count >= 10){
                    tmp[0] = feed_count /10+ '0';
                    tmp[1] = feed_count %10+ '0';
                }
                else tmp[0] = feed_count + '0';
                al_draw_text(Large_font, BLACK,  window_width/2 , window_height/2+240, ALLEGRO_ALIGN_CENTRE, tmp);
                al_flip_display();
                al_rest(0.3);
                feed_count ++;
                al_draw_scaled_bitmap(pop_cat_open,0,0,al_get_bitmap_width(pop_cat_open), al_get_bitmap_height(pop_cat_open),
                                  0, 0, window_width, window_height, 0);
                al_draw_filled_rectangle(window_width/2 - 125 , window_height/2 +170, window_width/2 +125, window_height/2 +320, WHITE);
                al_draw_text(Large_font, BLACK,  window_width/2 , window_height/2+180, ALLEGRO_ALIGN_CENTRE, "A T E");

//                    char tmp[2];
                if( feed_count >= 10){
                    tmp[0] = feed_count /10+ '0';
                    tmp[1] = feed_count %10+ '0';
                }
                else tmp[0] = feed_count + '0';
                if( feed_count<= feed_food) al_draw_text(Large_font, BLACK,  window_width/2 , window_height/2+240, ALLEGRO_ALIGN_CENTRE, tmp);
            }
        }
        al_flip_display();
    }

    status->Gain_Score(cats[index]->reward(BORING));
}
// process of updated event
int GameWindow::process_event() {
    int instruction = GAME_CONTINUE;
    al_wait_for_event(event_queue, &event);
    redraw = false;

    if(event.type == ALLEGRO_EVENT_TIMER) {
        if(event.timer.source == timer) {
            redraw = true;
             for( int c = 0, s = cats.size(); c < s; c++ ){
                cats[c]->getting_dirty();
                cats[c]->getting_hungry();
//                cats[c]->getting_bored();
//                cats[c]->see_me();
                cats[c]->touch_me();
            }
        }
    }
    else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        return GAME_EXIT;
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
        if(event.mouse.button == 1) {
            if( shop->shop_status() ){
//                std::cout << "clicked mouse "<< std::endl;
                int buy_item = -1;
                for( int i = SHOP_EXIT; i <= WATCH_AD; i++){
                    if(shop->shop_clicked( mouse_x, mouse_y, i)){
                        buy_item = i;
//                        std::cout << buy_item<<"buy ";
                    }
                }
                if( buy_item != -1 ){
                    if( buy_item == SHOP_EXIT ){
                        shop->change_window_open(false);
                    }
                    else if ( buy_item == WATCH_AD ){
//                           (rand() % (max - min + 1) + min);
                        shop->play_video((rand() % (6 - 1 + 1) + 1), display); // 5and 6 good
                        if( !usermode ) status->Change_Coin( shop->costCoin(buy_item));
                    }
                    else if (buy_item == GET_CAT){
                        //create cat object and mouse drag cat to position
                        shop->change_window_open(false);
                        if (!put_a_cat())
                            instruction = GAME_EXIT;
                    }
                    else if(buy_item == BUY_FOOD){
//                        std::cout << "cost "<<shop->costCoin(buy_item)<< std::endl;
                        if( shop->Enough_Coin( status->getCoin(), buy_item)){
                            if( !usermode ) status->Change_Coin( shop->costCoin(buy_item));
                            if( buy_item == BUY_FOOD ) status->Change_Food( ADD_FOOD );
                        }
                    }
                }
//                    std::cout << "clicked mouse "<<status->getCoin()<< std::endl;
            }
            else{ // shop closed
                if( shop->shop_clicked( mouse_x, mouse_y, SHOP_ICON)) shop->change_window_open(true);
                else {
                    for( int i = 0, s = cats.size(); i < s; i++){
                        if(  cats[i]->cat_queue_empty() == 0 && clicked(mouse_x, mouse_y, cats[i]->cat_x(), cats[i]->cat_y(),
                                                                         status_image_size + 100, status_image_size + 100)){
                            switch (cats[i]->cat_queue_top()) {
                            case HUNGRY: cats[i]->change_cat_status(HUNGRY, 0);
                                hungry_cat(i);
                                break;
                            case DIRTY: cats[i]->change_cat_status(DIRTY, 0);
                                break;
                            case BORING: cats[i]->change_cat_status(BORING, 0);
                                break;
                            case TOUCHME: cats[i]->change_cat_status(TOUCHME, 0);
                                touch_me(i);
                                break;
                            case SEEME: cats[i]->change_cat_status(SEEME, 0);
                                see_cat(i);
                                break;
                            }
                            cats[i]->cat_queue_pop();
                        }
                    }
                }
//                cout << "out\n";
            }
        }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_AXES){
//        std::cout << "find bug\n";
        mouse_x = event.mouse.x;
        mouse_y = event.mouse.y;
//        std::cout << "mouse "<< mouse_x << " " << mouse_y << std::endl;
        shop->MouseIn(mouse_x, mouse_y);

    }

    if(redraw) {
        // update each object in game
        instruction = game_update();
//                std::cout << "find bug redraq\n";
        // Re-draw map
        draw_running_map();
        redraw = false;
    }
    return instruction;
}

bool GameWindow::put_a_cat() {

    Cat *new_cat = new Cat();
    cats.push_back(new_cat);
    int cnt = 0;
    while (1) {
        cnt++;
        redraw = false;
        al_wait_for_event(event_queue, &event);

        if (event.type == ALLEGRO_EVENT_MOUSE_AXES && cnt % 5 == 0) {
            cnt /= 5;
            new_cat->setXY(event.mouse.x, event.mouse.y, 0);
            redraw = true;
        }
        else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            new_cat->setXY(event.mouse.x, event.mouse.y, 1);
            redraw = true;
            draw_running_map();
            break;
        }
        if (redraw)
            draw_running_map();
    }
}
