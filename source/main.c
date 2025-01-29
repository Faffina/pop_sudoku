#include "term_handle.h"
#include <ncurses.h>
#include <stdio.h>

int main(){
    init_app();
    enum state s = menu(); 
    switch(s) {
        case PLAY:printw("play \n"); break; 
        case QUIT:printw("quit \n"); break; 
        case SOLVE:printw("solve \n"); break; 
    }
    getch();
    end_app();
}
