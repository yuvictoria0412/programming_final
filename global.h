#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include <allegro5/allegro_font.h>
#include <string>

#define font_size 12
#define grid_width 40
#define grid_height 40

#define window_width 800
#define window_height 800
//#define field_width 00
//#define field_height 1000

extern std::string username;
extern ALLEGRO_USTR *username2;
extern bool usermode;
extern bool usersound;


#endif // GLOBAL_H_INCLUDED

