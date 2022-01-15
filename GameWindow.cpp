#include "GameWindow.h"
#include <iostream>

#define WHITE al_map_rgb(255, 255, 255)
#define BLACK al_map_rgb(0, 0, 0)
#define min(a, b) ((a) < (b)? (a) : (b))
#define max(a, b) ((a) > (b)? (a) : (b))
//#define window_width 1000
//#define window_height 1000
//#define field_height 1000
//#define field_width 1000

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

    font = al_load_ttf_font("./font/Beauty Dream.ttf",12,0); // load small font
//    Medium_font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",24,0); //load medium font
//    Large_font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",36,0); //load large font

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_register_event_source(event_queue, al_get_timer_event_source(timer));
//    //video addonm
//    al_init_video_addon();
//    al_install_audio( );
//    ALLEGRO_VIDEO *video = al_open_video("./Shop/video/3.ogg");
//    ALLEGRO_EVENT_QUEUE *vid_event_queue = al_create_event_queue();
//    ALLEGRO_EVENT_SOURCE *tryysee = al_get_video_event_source(video);
//    al_register_event_source( event_queue,  al_get_video_event_source(video));
//    al_reserve_samples(1);
//    al_start_video(video, al_get_default_mixer());
    game_init();
}
void GameWindow::game_init() {
    status = new Status();
    shop = new Shop();
}

void GameWindow::game_reset() {
    al_stop_timer(timer);
    status->Reset();
}
void GameWindow::game_play() {
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

// each drawing scene function
void GameWindow::draw_running_map() {
    al_clear_to_color( WHITE );
    if( !shop->shop_status() ){
        status->Draw();
        shop->Draw();
    }
    else{
        status->Draw();
        shop->Draw();
    }
    al_flip_display();
}

// process of updated event
int GameWindow::process_event() {
    int instruction = GAME_CONTINUE;
    al_wait_for_event(event_queue, &event);
    redraw = false;
    if(event.type == ALLEGRO_EVENT_TIMER) {
        if(event.timer.source == timer) {
            redraw = true;

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
                    if ( buy_item == WATCH_AD ){
                        status->Change_Coin( shop->costCoin(buy_item));
                    }
                    else{
//                        std::cout << "cost "<<shop->costCoin(buy_item)<< std::endl;
                        if( shop->Enough_Coin( status->getCoin(), buy_item)){
                            status->Change_Coin( shop->costCoin(buy_item));
                            if( buy_item == BUY_FOOD ) status->Change_Food( ADD_FOOD );
                        }
                    }
//                    std::cout << "clicked mouse "<<status->getCoin()<< std::endl;
                }

            }
            else{
                shop->shop_clicked( mouse_x, mouse_y, SHOP_ICON);
            }
        }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_AXES){
        mouse_x = event.mouse.x;
        mouse_y = event.mouse.y;
//        std::cout << "mouse "<< mouse_x << " " << mouse_y << std::endl;
        shop->MouseIn(mouse_x, mouse_y);

    }

    if(redraw) {
        // update each object in game
        instruction = game_update();

        // Re-draw map
        draw_running_map();
        redraw = false;
    }
    return instruction;
}
