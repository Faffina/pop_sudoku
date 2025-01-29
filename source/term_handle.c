#include "term_handle.h"
#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>

void init_app()
{
    struct sigaction a;
    memset(&a, 0, sizeof(a));
    a.sa_handler = end_app_whit_sig;
    int signal_to_handle[] = {SIGINT, SIGTERM, SIGHUP, SIGABRT, SIGFPE, SIGSEGV, SIGBUS, SIGPOLL};
    int n = sizeof(signal_to_handle) / sizeof(signal_to_handle[0]);
    for(int i = 0; i < n; i++)
        if(sigaction(signal_to_handle[i], &a, NULL) == -1)
            exit(EXIT_FAILURE);
    initscr();
    raw();
    noecho();
    keypad(stdscr, true);
}

void end_app_whit_sig(int sig)
{
    endwin();
    if(sig == -1)
        exit(EXIT_SUCCESS);
    else
        exit(EXIT_FAILURE);
}

#define print_move_center(str) mvaddstr(y++, (w - sizeof(str)) / 2, str);

enum state menu()
{
    int y = 1, h, w;
    getmaxyx(stdscr, h, w);
    move(0, 0);
    print_move_center("hi, this is a simple sudoku game.");
    y++;
    print_move_center("1. play");
    print_move_center("2. solve");
    print_move_center("3. exit");
    int return_list[] = {PLAY, SOLVE, QUIT};
    int c;
    int n_selected = 11;
    int prev_selected = 1;
    y = 3;
    while(1)
    {
        c = getch();
        switch(c)
        {
            case '1': case '2': case '3':
                n_selected = c - '0';
                break;
            case KEY_UP: case 'k': 
                n_selected--;
                break;
            case KEY_DOWN: case 'j':
                n_selected++;
                break;
            case 10:
                return return_list[n_selected];
        }
        if(n_selected < 0)
            n_selected = 2;
        if(n_selected > 2)
            n_selected = 0;
        move(y+prev_selected, 0);
        chgat(-1, A_NORMAL, 1, NULL);
        move(y+n_selected, 0);
        chgat(-1, A_REVERSE, 1, NULL);
        refresh();
        prev_selected = n_selected;

    }
    return QUIT;
}
