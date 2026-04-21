#define GRID_SIZE 2

#include <curses.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
    char nodeName[20];
    int load; //0-100
    int status; // 0 - OK, 1 - Warning, 2 - Danger
} PowerStations;

void updateGrids(PowerStations grids[], int size);
void drawGrids(PowerStations grids[], int size, int startX, int startY);
void initializeGrids(PowerStations grids[]);

int main() {
    PowerStations grids[GRID_SIZE];
    initscr();
    noecho();
    curs_set(0);
    timeout(500);

    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);//Danger
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);//Warning
    init_pair(3, COLOR_GREEN, COLOR_BLACK);//Ok

    initializeGrids(grids);
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

        mvprintw(5, startX, "|Node|---------------|Load|-----|Status|");
        mvprintw(6, startX, "----------------------------------------");

        mvprintw(maxY-3, 2, "CONTROLS: [1-%d] Balance Load | [R] Reset Grid | [Q] Shutdown", GRID_SIZE);

        updateGrids(grids, 2);
        drawGrids(grids, 2, startX - 3, 7);

        mvprintw(7 + GRID_SIZE, startX, "----------------------------------------");

        refresh();

        int c = getch();
        if(c == 'q' || c == 'Q'){ break; }
        if(c == KEY_RESIZE){ resize_term(0,0); }
    }
    endwin();

    return 0;
}

void updateGrids(PowerStations grids[], int size){
    for(int i = 0; i < size; i++){
        if (grids[i].load < 0) {grids[i].load = 0;}
        if (grids[i].load > 100) {grids[i].load = 100;}

        if(grids[i].load >= 95) {grids[i].status = 2;}
        else if (grids[i].load >= 80) {grids[i].status = 1;}
        else {grids[i].status = 0;}
    }
}

void drawGrids(PowerStations grids[], int size, int startX, int startY){
    for(int i = 0; i < size; i++){
        mvprintw((startY + i), startX, "%d. [%-12s]      [%3d%%]      ", (i + 1) ,grids[i].nodeName, grids[i].load);

        if(grids[i].status == 2) {attron(COLOR_PAIR(1)); printw("DANGER"); attroff(COLOR_PAIR(1));}
        else if (grids[i].status == 1){attron(COLOR_PAIR(2)); printw("WARNING"); attroff(COLOR_PAIR(2));}
        else {attron(COLOR_PAIR(3)); printw("OK"); attroff(COLOR_PAIR(3));}
    }
}

void initializeGrids(PowerStations grids[]){
    strcpy(grids[0].nodeName, "MasTec HQ");
    grids[0].load = 45;
    grids[0].status = 0;

    strcpy(grids[1].nodeName, "Google HQ");
    grids[1].load = 65;
    grids[1].status = 0;
}