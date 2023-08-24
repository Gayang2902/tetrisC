#include <ncurses.h>

#include "table.h"
#include "shape.h"

// 블럭을 게임화면에 그리기
void writeToTable(void)
{
    for (int i = 0; i < current.width; i++) {
        for (int j = 0; j < current.width; j++) {
            if (current.shape[i][j]) {
                table[current.row + i][current.col + j] = current.shape[i][j];
            }
        }
    }
}

// 줄이 채워졌는지 확인
void checkLine(void)
{
    int sum = 0;
    int count = 0;
    int i, j, k, l;

    for (i = 0; i < ROW; i++) {
        sum = 0;
        for (j = 0; j < COL; j++) {
            sum += table[i][j];
        }
        // 한 줄을 다 채웠다면
        if (sum == COL) {
            count++;
            
            // 테이블을 한 칸 내리기
            for (k = i; k >= 1; k--) {
                for (int l = 0; l < COL; l++) {
                    table[k][l] = table[k - 1][l];
                }
            }
            // 기존의 줄은 다시 원상복구
            for (l = 0; l < COL; l++) {
                table[k][l] = 0;
            }
        }
    }
    // timer -= 1000;

    // 한 번에 많은 줄을 채웠다면 점수가 배수로 증가
    score += 100 * count;
}

// 게임화면 출력
void printTable(void)
{
    char buffer[ROW][COL] = {0, };
    
    for (int i = 0; i < current.width; i++) {
        for (int j = 0; j < current.width; j++) {
            if (current.shape[i][j]) {
                buffer[current.row + i][current.col + j] = current.shape[i][j];
            }
        }
    }

    clear();

    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            printw("%c ", (table[i][j] + buffer[i][j]) ? '0' : '.');
        }
        printw("\n");
    }
    printw("\nScore: %d\n", score);
}