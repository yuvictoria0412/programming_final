#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include <allegro5/allegro_font.h>
#include <string>

#define font_size 12
#define grid_width 40
#define grid_height 40

#define window_width 800
#define window_height 800
#define max_score 500
#define min_score -100
#define super_user_score 0
extern std::string username;
extern ALLEGRO_USTR *username2;
extern bool usermode;
extern bool usersound;
//from game window
extern bool users_performance;
extern int final_score;


#endif // GLOBAL_H_INCLUDED

