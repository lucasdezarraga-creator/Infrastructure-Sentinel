#include <curses.h>

int main() {
    initscr();
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);

    // DRAW THE FRAME
    attron(A_BOLD);
    mvprintw(1, 2, "========================================");
    mvprintw(2, 2, "||      INFRASTRUCTURE SENTINEL       ||");
    mvprintw(3, 2, "========================================");
    attroff(A_BOLD);

    // STATUS SECTION
    mvprintw(5, 5, "GRID STATUS: ");
    attron(COLOR_PAIR(1));
    printw("OPERATIONAL");
    attroff(COLOR_PAIR(1));

    mvprintw(7, 5, "STATION 01 [TAMIAMI]: ");
    attron(COLOR_PAIR(1));
    printw("OK");
    attroff(COLOR_PAIR(1));

    mvprintw(8, 5, "STATION 02 [FIU MAIN]: ");
    attron(COLOR_PAIR(2));
    printw("OVERLOAD WARNING");
    attroff(COLOR_PAIR(2));

    mvprintw(12, 2, "Press any key to initiate shutdown...");
    
    refresh();
    getch();
    endwin();
    return 0;
}