#ifndef CURSES_H_
#define CURSES_H_

#include "./protocol.h"
#include <ncurses.h>

typedef struct{
    WINDOW *message_canvas;
    WINDOW *typing_canvas;
} display_canvas;

display_canvas *init_screen();
int display_message(package_t *pkg, display_canvas *display);
char *await_message(display_canvas *display);
int end_screen(display_canvas *display);

#endif
