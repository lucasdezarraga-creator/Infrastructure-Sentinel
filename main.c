#include <curses.h>
#include<time.h>
#include<stdlib.h>

typedef struct {
    char nodeName[20];
    int load; //0-100
    int status; // 0 - OK, 1 - Warning, 2 - Danger
} PowerStations;

int main() {
    initscr();
    noecho();
    curs_set(0);
    timeout(500);

    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);//Danger
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);//Warning
    init_pair(3, COLOR_GREEN, COLOR_BLACK);//Ok

    keypad(stdscr, TRUE);

    while(1){
        erase();
        int maxX, maxY;
        getmaxyx(stdscr, maxY, maxX);
        box(stdscr, 0, 0);

        int titleLenght = 41;
        int startX = (maxX - titleLenght) / 2;
        if(startX < 0){ startX = 0; }

        attron(A_BOLD);
        mvprintw(2, startX, "========================================");
        mvprintw(3, startX, "||      INFRASTRUCTURE SENTINEL       ||");
        mvprintw(4, startX, "========================================");
        attroff(A_BOLD);

        time_t now = time(NULL);
        char *currTime = ctime(&now);
        mvprintw(1, 2, "Time: %.19s", currTime);

        mvprintw(5, startX, "Node        Load        Status");
        mvprintw(6, startX, "----        ----        ------");

        mvprintw(maxY-3, 2, "CONTROLS: [1-2] Balance Load | [R] Reset Grid | [Q] Shutdown");
        refresh();

        int c = getch();
        if(c == 'q' || c == 'Q'){ break; }
        if(c == KEY_RESIZE){ resize_term(0,0); }
    }
    endwin();

    return 0;
}