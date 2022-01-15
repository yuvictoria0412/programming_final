#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include <allegro5/allegro_font.h>
#include <string>

#define font_size 12
#define grid_width 40
#define grid_height 40

#define window_width 800
#define window_height 600
#define field_width 600
#define field_height 600


std::string username;
ALLEGRO_USTR *username2;
bool usermode;
bool usersound;

#endif // GLOBAL_H_INCLUDED

