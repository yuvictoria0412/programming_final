#include "MenuWindow.h"
#include "GameWindow.h"

std::string username;
ALLEGRO_USTR *username2;
bool usermode;
bool usersound;

int main(int argc, char *argv[])
{

//    MenuWindow *Menu= new MenuWindow();
//    Menu->game_play();
    usermode = false;
    GameWindow *Meow_Game = new GameWindow();

    Meow_Game->game_play();

    delete Meow_Game;
//    delete Menu;
//
//    delete TowerGame;
    return 0;
}
