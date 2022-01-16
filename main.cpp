#include "MenuWindow.h"
#include "GameWindow.h"
#include <iostream>
std::string username;
ALLEGRO_USTR *username2;
bool usermode;
bool usersound;

int main(int argc, char *argv[])
{
    MenuWindow *Menu= new MenuWindow();
    if (Menu->game_play()) {
        std::cout << "MEOW" << std::endl;
        std::cout << username << std::endl;
        std::cout << al_cstr(username2) << std::endl;
        std::cout << usermode << std::endl;
        std::cout << usersound << std::endl;
        GameWindow *Meow_Game = new GameWindow();
        Meow_Game->game_play();
        delete Meow_Game;
    }
    delete Menu;

    return 0;
}
