#ifndef TERM_HANDLE_H
#define TERM_HANDLE_H
#include<stddef.h>

enum state {QUIT, MENU, SOLVE, PLAY};
void init_app();
#define end_app() end_app_whit_sig(-1)
void end_app_whit_sig(int sig);
enum state menu();

#endif
