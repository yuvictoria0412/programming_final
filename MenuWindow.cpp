#include "MenuWindow.h"
#include "global.h"
#include <string>
extern std::string username;
extern ALLEGRO_USTR *username2;
extern bool usermode;
extern bool usersound;

#include <iostream>
using namespace std;
// color
#define WHITE al_map_rgb(255, 255, 255)
#define BLACK al_map_rgb(0, 0, 0)

#define H window_height
#define W window_width


// basic algo
#define min(a, b) ((a) < (b)? (a) : (b))
#define max(a, b) ((a) > (b)? (a) : (b))

const int rec_x1 = 250;
const int rec_y1 = 200;
const int rec_h1 = 50;
const int rec_y2 = 300;
const int rec_h2 = 50;
const int rec_y3 = 400;
const int rec_h3 = 50;

//enum {NOTHING = 0, ENTERNAME, CHOOSEMODE, SETSOUND};

MenuWindow::MenuWindow() {

    if (!al_init())
        show_err_msg(-1);

    printf("Game Initializing...\n");

    display = al_create_display(W, H);
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

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));


    game_init();
}

void MenuWindow::game_init() {
    cout << "Game_init" << endl;
    al_set_window_position(display, 0, 0);
    al_clear_to_color(WHITE);

    al_draw_text(Large_font, BLACK, W/2, 80, ALLEGRO_ALIGN_CENTRE, "C A T S  A R E  C U T E");
    al_draw_rectangle(rec_x1, rec_y1, W-rec_x1, rec_y1 + rec_h1, BLACK, 2);
    al_draw_text(Medium_font, BLACK, W/2, rec_y1 + rec_h1/2 - 12, ALLEGRO_ALIGN_CENTRE, "O W N E R ' S    N A M E");
    al_draw_rectangle(rec_x1, rec_y2, W-rec_x1, rec_y2 + rec_h2, BLACK, 2);
    al_draw_text(Medium_font, BLACK, W/2, rec_y2 + rec_h2/2 - 12, ALLEGRO_ALIGN_CENTRE, "P L A Y E R  M O D E");
    al_draw_rectangle(rec_x1, rec_y3, W-rec_x1, rec_y3 + rec_h3, BLACK, 2);
    al_draw_text(Medium_font, BLACK, W/2, rec_y3 + rec_h3/2 - 12, ALLEGRO_ALIGN_CENTRE, "S O U N D  O N");
//    al_draw_bitmap(playbutton, W-40, H-40, 0);
    al_flip_display();
    // might need to delete
    al_rest(5);
    return;
}

void MenuWindow::game_reset() {

}

void MenuWindow::game_play() {
    int msg = -1;

    srand(time(NULL));
    game_reset();
    game_begin();

    while (msg != GAME_EXIT) {
        msg = game_run();
        if (msg == GAME_EXIT)
            cout << "game_exit" << endl;
    }
    show_err_msg(msg);
}

void MenuWindow::game_begin() {
    usermode = 0;
    usersound = 0;
    username2 = al_ustr_new("");
    al_start_timer(timer);
    playbutton = al_load_bitmap("./pictures/start.jpg");
}


int MenuWindow::game_update() {
    return 0;
}


void MenuWindow::game_destroy() {
}

// each drawing scene function
void MenuWindow::draw_running_map() {
}

void MenuWindow::draw_menu() {

    al_set_window_position(display, 0, 0);
    al_clear_to_color(WHITE);

    al_draw_text(Large_font, BLACK, W/2, 80, ALLEGRO_ALIGN_CENTRE, "C A T S  A R E  C U T E");

    // USER NAME
    al_draw_rectangle(rec_x1, rec_y1, W-rec_x1, rec_y1 + rec_h1, BLACK, 2);
    if (!al_ustr_length(username2))
        al_draw_text(Medium_font, BLACK, W/2, rec_y1 + rec_h1/2 - 12, ALLEGRO_ALIGN_CENTRE, "O W N E R ' S    N A M E");
    else
        al_draw_textf(Medium_font, BLACK, W/2, rec_y1 + rec_h1/2 - 12, ALLEGRO_ALIGN_CENTRE, "%s", al_cstr(username2));

    // USER MODE
    al_draw_rectangle(rec_x1, rec_y2, W-rec_x1, rec_y2 + rec_h2, BLACK, 2);
    if (usermode == 0)
        al_draw_text(Medium_font, BLACK, W/2, rec_y2 + rec_h2/2 - 12, ALLEGRO_ALIGN_CENTRE, "P L A Y E R  M O D E");
    else
        al_draw_text(Medium_font, BLACK, W/2, rec_y2 + rec_h2/2 - 12, ALLEGRO_ALIGN_CENTRE, "S U P E R C A T  M O D E");
    // USER SOUND
    al_draw_rectangle(rec_x1, rec_y3, W-rec_x1, rec_y3 + rec_h3, BLACK, 2);
    if (usersound == 0)
        al_draw_text(Medium_font, BLACK, W/2, rec_y3 + rec_h3/2 - 12, ALLEGRO_ALIGN_CENTRE, "S O U N D  O N");
    else
        al_draw_text(Medium_font, BLACK, W/2, rec_y3 + rec_h3/2 - 12, ALLEGRO_ALIGN_CENTRE, "B E  Q U I E T >:(");
    // PLAY BUTTON
    al_draw_bitmap(playbutton, W-40, H-40, 0);

    // OUTPUT DISPLAY
    al_flip_display();

    return;
}

bool MenuWindow::entering_name() {
    cout << "entering name" << endl;
//    ALLEGRO_USTR *input = al_ustr_new("");
    while (1) {
        redraw = false;
        al_wait_for_event(event_queue, &event);

        if (event.type == ALLEGRO_EVENT_KEY_CHAR) {
                cout << "input: "  << event.keyboard.keycode << endl;
            if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                cout << "input enter" << endl;
                username.assign(al_cstr(username2));
                cout << username << endl;
                draw_menu();
                return 1;
            }
            else if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                cout << "input escape" << endl;
                return 0;
            }
            else if (event.keyboard.keycode == ALLEGRO_KEY_BACKSPACE) {
                cout << "input backspace" << endl;
                if (al_ustr_length(username2))
                    al_ustr_remove_chr(username2, al_ustr_length(username2) - 1);
//                if (!username.empty())
//                    username.pop_back();

                redraw = true;
            }
            else {
                al_ustr_append_chr(username2, event.keyboard.unichar);
                redraw = true;
            }
        }
        if (redraw) {
            draw_menu();
        }
    }

}

// process of updated event
int MenuWindow::process_event() {
    int instruction = GAME_CONTINUE;
    int draw_condition = 0;

    al_wait_for_event(event_queue, &event);
    redraw = false;

    if (event.type == ALLEGRO_EVENT_TIMER) {
        redraw = true;
    }
    else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
        switch(event.keyboard.keycode) {
            case ALLEGRO_KEY_ESCAPE:
                cout << "key_input" << endl;
                if (al_get_timer_started(timer))
                    al_stop_timer(timer);
                instruction = GAME_EXIT;
                break;
        }
    }
    else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
        if (event.mouse.button == 1) {
            if (event.mouse.x >= rec_x1 && event.mouse.x <= W-rec_x1) {
                if (event.mouse.y >= rec_y1 && event.mouse.y <= rec_y1 + rec_h1) {
                    cout << "click name" << endl;
                    if (!entering_name())
                        instruction = GAME_EXIT;

                }
                else if (event.mouse.y >= rec_y2 && event.mouse.y <= rec_y2 + rec_h2) {
                    cout << "click mode" << endl;
                    if (usermode == 0) usermode = 1;
                    else usermode = 0;
                    redraw = 1;
                }
                else if (event.mouse.y >= rec_y3 && event.mouse.y <= rec_y3 + rec_h3) {
                    cout << "click sound" << endl;
                    if (usersound == 0) usersound = 1;
                    else usersound = 0;
                    redraw = 1;
                }
            }
        }
    }
    if (redraw) {
        draw_menu();
    }
    return instruction;
}


