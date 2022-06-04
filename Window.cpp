#include "Window.h"
#include <stdio.h>

Window::Window(){
    srand( time(NULL) ); //for randon
}
int Window::game_run() {
//    printf("game_run\n");
    int error = GAME_CONTINUE;

    if (!al_is_event_queue_empty(event_queue)) {
        error = process_event();
    }
    return error;
}

void Window::show_err_msg(int msg) {
    if(msg == GAME_TERMINATE)
        fprintf(stderr, "Game Terminated...");
    else
        fprintf(stderr, "unexpected msg: %d", msg);

    game_destroy();
//    exit(9);
}
