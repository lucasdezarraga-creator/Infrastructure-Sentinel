#define GRID_SIZE 5
#define COOLDOWN 4
#define REST_COOLDOWN 10

#include <curses.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
    char nodeName[20];
    int load; //0-100
    int status; // 0 - OK, 1 - Warning, 2 - Danger
    time_t coolDown; 
} PowerStations;

void updateGrids(PowerStations grids[], int size);
void drawGrids(PowerStations grids[], int size, int startX, int startY);
void initializeGrids(PowerStations grids[]);

int main() {
    PowerStations grids[GRID_SIZE];
    time_t lastRestCooldown = 0;

    initscr();
    noecho();
    curs_set(0);
    timeout(500);

    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);//Danger
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);//Warning
    init_pair(3, COLOR_GREEN, COLOR_BLACK);//Ok
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);

    initializeGrids(grids);
    keypad(stdscr, TRUE);

    while(1){
        time_t cd = time(NULL);

        srand(time(NULL));
        erase();
        int maxX, maxY;
        getmaxyx(stdscr, maxY, maxX);
        box(stdscr, 0, 0);

        int titleLenght = 41;
        int startX = (maxX - titleLenght) / 2;
        if(startX < 0){ startX = 0; }

        attron(A_BOLD);
        attron(COLOR_PAIR(5));
        mvprintw(2, startX, "========================================");
        mvprintw(3, startX, "||      INFRASTRUCTURE SENTINEL       ||");
        mvprintw(4, startX, "========================================");
        attroff(COLOR_PAIR(5));
        attroff(A_BOLD);

        time_t now = time(NULL);
        char *currTime = ctime(&now);
        mvprintw(1, 2, "Time: %.19s", currTime);

        attron(COLOR_PAIR(5));
        mvprintw(5, startX, "|Node|---------------|Load|-----|Status|");
        mvprintw(6, startX, "----------------------------------------");
        attroff(COLOR_PAIR(5));

        
        if(difftime(cd, lastRestCooldown) < REST_COOLDOWN){
            attron(COLOR_PAIR(2));
            mvprintw(maxY-3, 2, "WARNING: Reboot on cooldown.");
            attroff(COLOR_PAIR(2));
        } else {
            mvprintw(maxY-3, 2, "CONTROLS: [1-%d] Balance Load | [R] Reset Grid | [Q] Shutdown", GRID_SIZE);
        }
        

        updateGrids(grids, GRID_SIZE);
        drawGrids(grids, GRID_SIZE, startX - 3, 7);

        attron(COLOR_PAIR(5));
        mvprintw(7 + GRID_SIZE, startX, "----------------------------------------");
        attroff(COLOR_PAIR(5));

        refresh();

        int c = getch();

        char targetNode = c - '1';
        if(targetNode <= '0' && targetNode < GRID_SIZE){
            if(difftime(cd, grids[targetNode].coolDown) >= COOLDOWN){
                grids[targetNode].load -= 15;
                grids[targetNode].coolDown = cd;
            }
        }

        if (c == 'r' || c == 'R'){
            time_t cd = time(NULL);
            if(difftime(cd, lastRestCooldown) >= REST_COOLDOWN){
                initializeGrids(grids);
                lastRestCooldown = cd;
            }
        }
        
        int failure = 0;
        for(int i = 0; i < GRID_SIZE; i++){
            if(grids[i].load == 100){
                failure = 1;
                break;
            }
        }
        if (failure) {break;}

        if (c == 'q' || c == 'Q'){ break; }
        if(c == KEY_RESIZE){ resize_term(0,0); }
    }
    endwin();

    return 0;
}

void updateGrids(PowerStations grids[], int size){
    for(int i = 0; i < size; i++){
        int jitter = (rand() % 5) - 2;
        if(grids[i].load >= 80){ jitter++;}
        if((rand() % 100) == 0){ jitter += 20; }
        grids[i].load += jitter;

        if (grids[i].load < 0) {grids[i].load = 0;}
        if (grids[i].load > 100) {grids[i].load = 100;}

        if(grids[i].load >= 95) {grids[i].status = 2;}
        else if (grids[i].load >= 80) {grids[i].status = 1;}
        else {grids[i].status = 0;}
    }
}

void drawGrids(PowerStations grids[], int size, int startX, int startY){
    for(int i = 0; i < size; i++){
        attron(COLOR_PAIR(4));
        mvprintw((startY + i), startX, "%d. [%-12s]      [%3d%%]      ", (i + 1) ,grids[i].nodeName, grids[i].load);
        attroff(COLOR_PAIR(4));

        if(grids[i].status == 2) {attron(COLOR_PAIR(1)); printw("DANGER"); attroff(COLOR_PAIR(1));}
        else if (grids[i].status == 1){attron(COLOR_PAIR(2)); printw("WARNING"); attroff(COLOR_PAIR(2));}
        else {attron(COLOR_PAIR(3)); printw("OK"); attroff(COLOR_PAIR(3));}
    }
}

void initializeGrids(PowerStations grids[]){
    int loads[GRID_SIZE] = {45, 55, 65, 55, 45};
    char nodes[GRID_SIZE][10] = {"MasTec HQ", "Google HQ", "Intel HQ", "Apple HQ", "HP HQ"};
    for(int i = 0; i < GRID_SIZE; i++){
        strcpy(grids[i].nodeName, nodes[i]);
        grids[i].load = loads[i];
        grids[i].status = 0;
    }
}