#include <ncurses.h>


void
main(void)
{
    initscr();

    printw("hello world!");

    getch();
    endwin();
}