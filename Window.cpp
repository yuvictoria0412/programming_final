#include "Window.h"
#include <stdio.h>

int Window::game_run() {
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

//    game_destroy();
    exit(9);
}
