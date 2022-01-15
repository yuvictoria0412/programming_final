#include "MenuWindow.h"
#include <iostream>
using namespace std;
// color
#define WHITE al_map_rgb(255, 255, 255)
#define BLACK al_map_rgb(0, 0, 0)

// basic algo
#define min(a, b) ((a) < (b)? (a) : (b))
#define max(a, b) ((a) > (b)? (a) : (b))

MenuWindow::MenuWindow() {

    if (!al_init())
        show_err_msg(-1);

    printf("Game Initializing...\n");

    display = al_create_display(window_width, window_height);
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

    font = al_load_ttf_font("./font/Beauty Dream.ttf", 12, 0); // load small font
    Medium_font = al_load_ttf_font("./font/Beauty Dream.ttf", 24, 0); //load medium font
    Large_font = al_load_ttf_font("./font/Beauty Dream.ttf", 36, 0); //load large font

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    game_init();
}

void MenuWindow::game_init() {
    cout << "game_init" << endl;
    al_set_window_position(display, 100, 100);
    al_clear_to_color(WHITE);
    al_flip_display();
}

void MenuWindow::game_reset() {

}
void MenuWindow::game_play() {}

void MenuWindow::game_begin() {
}


int MenuWindow::game_update() {
    return 0;
}


void MenuWindow::game_destroy() {
}

// each drawing scene function
void MenuWindow::draw_running_map() {
}

// process of updated event
int MenuWindow::process_event() {
    return 0;
}

