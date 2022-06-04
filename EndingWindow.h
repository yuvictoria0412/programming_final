#ifndef ENDINGWINDOW_H_INCLUDED
#define ENDINGWINDOE_H_INCLUDED
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_video.h>
#include <allegro5/allegro_acodec.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "algif5/src/algif.h"
#include "Window.h"
#include <stdio.h>
#include <math.h>

const int ThumbWidth = 50;
const int ThumbHeight = 50;

class EndingWindow : protected Window {
public:
    EndingWindow();
    ~EndingWindow();
    void game_init();
    bool game_play();
    void game_begin();
    void game_reset();
    int game_update();
    void game_destroy();
    void draw_running_map();
    int process_event();
    bool clicked(int, int, int, int,  int, int);
    bool isInRange(int, int, int);
    int play_video();
private:
    ALLEGRO_BITMAP *gift;
    ALLEGRO_BITMAP *poop;
    ALLEGRO_VIDEO *good_video;
    ALLEGRO_VIDEO *bad_video;
    char *good_message;
    char *bad_message;
    int mouse_x;
    int mouse_y;
    bool press_next;
    ALLEGRO_SAMPLE *sample;
    ALLEGRO_SAMPLE_INSTANCE *startSound;
//    bool correct_return;
};

#endif // ENDINGWINDOW_H_INCLUDED
