#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

#include <vector>
#include <list>
#include <time.h>
#include "global.h"

#define GAME_INIT -1
#define GAME_SETTING 0
#define GAME_SELECT 1
#define GAME_BEGIN 2
#define GAME_CONTINUE 3
#define GAME_FAIL 4
#define GAME_TERMINATE 5
#define GAME_NEXT_LEVEL 6
#define GAME_EXIT 7

// clock rate
const float FPS = 60;

class Window {
public:
    // constructor
    Window() {}
    ~Window() {}
    virtual void game_init() = 0;
    virtual void game_reset() = 0;
    virtual void game_play() = 0;
    virtual void game_begin() = 0;

    int game_run();
    virtual int game_update() = 0;

    void show_err_msg(int msg);
    virtual void game_destroy()= 0;
    virtual void draw_running_map() = 0;
    virtual int process_event() = 0;

protected:
//    ALLEGRO_BITMAP *icon;
    ALLEGRO_DISPLAY* display = NULL;
    ALLEGRO_FONT *font = NULL;
    ALLEGRO_FONT *Medium_font = NULL;
    ALLEGRO_FONT *Large_font = NULL;

    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_EVENT event;
    ALLEGRO_TIMER *timer = NULL;

    bool redraw = false;
    bool mute = false;
};
#endif // WINDOW_H_INCLUDED
