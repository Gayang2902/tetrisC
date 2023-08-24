#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <sys/time.h>

#include "table.h"
#include "shape.h"
#include "player.h"

extern int score;

// 해야할 작업
// main 함수에 current 변수를 두고 다른 함수 호출 시 인자로 전달하는 방식으로 코드 변경

int main(void)
{
    srand(time(NULL));
    initscr();
    struct timeval before, after;
    gettimeofday(&before, NULL);
    nodelay(stdscr, true);

    int key;   
    score = 0;
    double timer = 500000;

    Block current = getNewBlock();
    printTable();

    while (gameOn) {
        if ((key = getch()) != ERR) {
            controlBlock(key, current);
        }
        gettimeofday(&after, NULL);
        if (((double)after.tv_sec*1000000 + (double)after.tv_usec)-((double)before.tv_sec*1000000 + (double)before.tv_usec) > timer){ //time difference in microsec accuracy
            before = after;
            controlBlock('s', current);
        }
    }

    printw("\nGame Over\n");
    deleteBlock(current);

    return 0;
}