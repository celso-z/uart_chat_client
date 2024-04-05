#include "./curses.h"
#include <stdlib.h>


display_canvas *init_screen(){
    display_canvas *ds = malloc(sizeof(display_canvas));
    if(ds == NULL) return NULL;
    initscr();
    raw();
    attroff(A_BLINK);
    curs_set(0);
    if(has_colors() == TRUE){
        start_color();
        init_pair(1, COLOR_GREEN, COLOR_BLACK);
        attron(COLOR_PAIR(1));
    }
    refresh();
    ds->message_canvas = newwin((LINES/3) * 2, COLS, 0, 0);
    ds->typing_canvas = newwin(((LINES/3) * 1), COLS, ((LINES/3) * 2), 0);
    wborder(ds->message_canvas, '|', '|', '-', '-', '+', '+', '+', '+'); 
    wborder(ds->typing_canvas, '|', '|', '-', '-', '+', '+', '+', '+'); 
    wrefresh(ds->message_canvas);
    wrefresh(ds->typing_canvas);
    return ds;
}

int display_message(package_t *pkg, display_canvas *display){
    wmove(display->message_canvas, 1, 1);
    wprintw("%s\n", pkg->msg);
    return 0;
}

char *await_message(display_canvas *display){
    curs_set(1);
    wmove(display->typing_canvas, 1, 1); 
    char *str = malloc(sizeof(char) * 49);
    for(int i = 0; i < 49; i++){
        //TODO: Handle backspaces
        char ch = wgetch(display->typing_canvas);
        if(i == 48 || ch == '\n'){
            str[i] = '\0';
            break;
        }
        str[i] = ch;
    }
    curs_set(0);
    wrefresh(display->typing_canvas);
    return str;
}

int end_screen(display_canvas *display){
    delwin(display->message_canvas);
    delwin(display->typing_canvas);
    free(display);
    endwin();
    return 0;
}
/*
int main(){
    display_canvas *t = init_screen();
    char *str = await_message(t);
    free(str);
    end_screen(t);
    return 0;
}*/
