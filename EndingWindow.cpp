#include "EndingWindow.h"
#include "global.h"
#include <string>

#include <iostream>
using namespace std;
// color
#define WHITE al_map_rgb(255, 255, 255)
#define BLACK al_map_rgb(0, 0, 0)

#define H window_height
#define W window_width

#include <cstring>
// basic algo
#define min(a, b) ((a) < (b)? (a) : (b))
#define max(a, b) ((a) > (b)? (a) : (b))

int click_x = 0, click_y = 0;
EndingWindow::EndingWindow() {
//    correct_return = 1;
    if (!al_init())
        show_err_msg(-1);

    printf("Ending Game...\n");

    display = al_create_display(W, H);
    al_set_window_position(display, 0, 0);
    event_queue = al_create_event_queue();
    timer = al_create_timer(1.0 / FPS);

    if(timer == NULL || display == NULL || event_queue == NULL)
        show_err_msg(-1);

    al_init_primitives_addon();
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon(); // initialize the ttf (True Type Font) addon
    al_init_image_addon(); // initialize the image addon
    al_init_acodec_addon(); // initialize acodec addon
    al_install_keyboard(); // install keyboard event
    al_install_mouse();    // install mouse event
    al_install_audio();    // install audio event

    font = al_load_ttf_font("./font/Cute Letters.ttf", 12, 0); // load small font
    Medium_font = al_load_ttf_font("./font/Cute Letters.ttf", 24, 0); //load medium font
    Large_font = al_load_ttf_font("./font/Cute Letters.ttf", 60, 0); //load large font

    al_init_video_addon();
    al_install_audio( );
    al_init_image_addon(); // initialize the image addon
    al_init_acodec_addon(); // initialize acodec addon

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    good_video = al_open_video("./ending/good_video.ogv");
    bad_video = al_open_video("./ending/bad.ogv");
    gift = al_load_bitmap("./ending/gift.jpg");
    poop = al_load_bitmap("./ending/poop.jpg");
    press_next = false;

    sample = al_load_sample("bgm.wav");
    startSound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(startSound, ALLEGRO_PLAYMODE_LOOP);
    al_reserve_samples(1);

    al_attach_sample_instance_to_mixer(startSound, al_get_default_mixer());
    if(!usersound) al_play_sample_instance(startSound);

    game_init();
}
EndingWindow::~EndingWindow(){
}
void EndingWindow::game_init() {
    cout << "Game_init" << endl;
    al_set_window_position(display, 0, 0);
    al_clear_to_color(WHITE);
    al_flip_display();
    return;
}

bool EndingWindow::game_play() {
    int msg = -1;

    game_reset();
    game_begin();

    while (msg != GAME_EXIT) {
        msg = game_run();
        if (msg == GAME_EXIT)
            cout << "game_exit" << endl;
    }
    show_err_msg(msg);
    return msg;
}

void EndingWindow::game_begin() {
    al_start_timer(timer);
}


void EndingWindow::game_destroy() {
    cout << "destroy\n";
    al_stop_sample_instance(startSound);
    al_stop_samples();

    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_font(font);
    al_destroy_font(Medium_font);
    al_destroy_font(Large_font);
    al_destroy_timer(timer);

    al_destroy_bitmap(gift);
    al_destroy_bitmap(poop);
}

// each drawing scene function
void EndingWindow::draw_running_map() {
    static float gift_angle = 0;
    static float add_angle = 3.14159/180.0;
    if( gift_angle <= 3.14159/180.0*(-30)) add_angle *= -1;
    else if ( gift_angle >= 3.14159/180.0*(30) ) add_angle *= -1;


    al_set_window_position(display, 0, 0);
    al_clear_to_color(WHITE);
    int h = 110, gap = 80;
    char buffer[50];

    sprintf(buffer, "S C O R E : %d", final_score);

    al_draw_text(Large_font, BLACK, window_width/2, h, ALLEGRO_ALIGN_CENTRE, buffer);
    h += gap;
    al_draw_text(Large_font, BLACK, window_width/2, h, ALLEGRO_ALIGN_CENTRE, username.c_str());
    h+= gap;
    if( users_performance ){
        al_draw_text(Large_font, BLACK, window_width/2, h, ALLEGRO_ALIGN_CENTRE, "I S   A   N I C E   H U M A N");
        h += gap;
        al_draw_text(Large_font, BLACK, window_width/2, h, ALLEGRO_ALIGN_CENTRE, "G I F T   F O R   Y O U");
        if( !gift ) cout << "empty file\n";
        h+= 250;
        click_x =  window_width/2;
        click_y =  h;
        al_draw_scaled_rotated_bitmap(gift, al_get_bitmap_width(gift)/2, al_get_bitmap_height(gift)/2, click_x, click_y, 0.4,0.4,gift_angle, 0);
    }
    else{
        al_draw_text(Large_font, BLACK, window_width/2, h, ALLEGRO_ALIGN_CENTRE, "I S   A   B A D   H U M A N");
        h += gap;
        al_draw_text(Large_font, BLACK, window_width/2, h, ALLEGRO_ALIGN_CENTRE, "P O O P   F O R   Y O U");
        h+= 250;
        click_x =  window_width/2;
        click_y =  h;

        al_draw_scaled_rotated_bitmap(poop, al_get_bitmap_width(poop)/2, al_get_bitmap_height(poop)/2+50, click_x, click_y, 0.3,0.3,gift_angle, 0);
    }
    gift_angle+= add_angle;
    al_flip_display();
}




// process of updated event
int EndingWindow::process_event() {
    int instruction = GAME_CONTINUE;
//    if( press_next) return GAME_EXIT;
    al_wait_for_event(event_queue, &event);
    redraw = true;
//
    if (event.type == ALLEGRO_EVENT_TIMER) {
        redraw = true;
    }
    else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
//        correct_return = 0;
        return GAME_EXIT;
    }
//    else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
//        switch(event.keyboard.keycode) {
//            case ALLEGRO_KEY_ESCAPE:
//                cout << "key_input" << endl;
//                correct_return = 0;
//                if (al_get_timer_started(timer))
//                    al_stop_timer(timer);
//                instruction = GAME_EXIT;
//                break;
//        }
//    }
    else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
        if (event.mouse.button == 1) {
            press_next = clicked( mouse_x, mouse_y, click_x, click_y, al_get_bitmap_width(gift), al_get_bitmap_height(gift));
            if(press_next){
                cout << "pressed\n";
                if(!usersound) al_stop_sample_instance(startSound);
            }

        }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_AXES){
//        std::cout << "find bug\n";
        mouse_x = event.mouse.x;
        mouse_y = event.mouse.y;
//        std::cout << "mouse "<< mouse_x << " " << mouse_y << std::endl;

    }
    if (redraw) {
        if(!press_next)draw_running_map();
        else{
            instruction = play_video();
        }
    }
    return instruction;
}
int EndingWindow::play_video(){
    ALLEGRO_VIDEO *video;
    ALLEGRO_BITMAP *frame;
    int instruction = GAME_CONTINUE;
    if( users_performance) video = good_video;
    else video = bad_video;
    al_register_event_source( event_queue,  al_get_video_event_source(video));
    al_reserve_samples(1);
    al_start_video(video, al_get_default_mixer());
    int state = 1;
    while( state ){
        al_wait_for_event(event_queue, &event);
        if( event.type == ALLEGRO_EVENT_TIMER ) {
            frame = al_get_video_frame(video);
            if ( !frame ){
                std::cout << "find bug bitmap\n";
//                return instruction;
            }
            else{
                al_draw_scaled_bitmap(frame, 0, 0,al_get_bitmap_width(frame),
                                  al_get_bitmap_height(frame),
                                  // the position of result image
                                  0, 0,
                                  // the width and height of result image
                                  al_get_display_width(display),
                                  al_get_display_height(display), 0);
                al_flip_display();
            }
        //    else std::cout << "normal\n";
            if ( !video ){
        //        std::cout << "find bug video\n";
                return instruction;
            }

        }
        else if(event.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch(event.keyboard.keycode) {
            case ALLEGRO_KEY_ESCAPE:
                state = 0;
                instruction = GAME_EXIT;
                break;
            }
        }
        else if( event.type == ALLEGRO_EVENT_VIDEO_FINISHED ) {
//            cout << "video fini\n";
            instruction = GAME_EXIT;
            break;
        }
    }
    al_close_video(video);
//    al_destroy_bitmap(frame);
    return instruction;
}
void EndingWindow::game_reset() {
    al_set_window_position(display, 0, 0);
    return;
}
int EndingWindow::game_update() {
    return 0;
}

bool EndingWindow::isInRange(int point, int startPos, int length){
    if(point >= startPos - length && point <= startPos + length)
        return true;
    return false;
}
bool EndingWindow::clicked(int mouse_x, int mouse_y, int x, int y, int w, int h){
//    cout << "shop is opened\n";
    if( isInRange( mouse_x, x, ThumbWidth + w/2) &&
       isInRange( mouse_y, y, ThumbHeight+ h/2)){
        return true;
    }
    else{
        return false;
    }
}
