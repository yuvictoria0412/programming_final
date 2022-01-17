#include "MenuWindow.h"
#include "GameWindow.h"
#include "EndingWindow.h"
#include <iostream>
std::string username;
ALLEGRO_USTR *username2;
bool usermode;
bool usersound;
bool users_performance;
int final_score;
int main(int argc, char *argv[])
{



    MenuWindow *Menu= new MenuWindow();

    if (Menu->game_play()) {
        std::cout << "MEOW" << std::endl;
        std::cout << username << std::endl;
        std::cout << al_cstr(username2) << std::endl;
        std::cout << usermode << std::endl;
        std::cout << usersound << std::endl;
        std::cout << users_performance<< std::endl;
        usermode = true;
        GameWindow *Meow_Game = new GameWindow();
        Meow_Game->game_play();

        EndingWindow *Ending = new EndingWindow();
        Ending->game_play();


    }
    std::cout << "game over"<< std::endl;
    al_rest(20);
    delete Menu;
//    delete Meow_Game;

    return 0;
}
