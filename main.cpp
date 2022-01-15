#include "GameWindow.h"
#include <string>
using namespace std;
int main(int argc, char *argv[])
{
    string user_name = "NN";
    GameWindow *Meow= new GameWindow();
//
    Meow->game_play();
//
    delete Meow;
    return 0;
}
