#include <stdbool.h>

#ifndef TABLE_H
#define TABLE_H

#define ROW (20)
#define COL (20)

bool gameOn = true;
int score = 0;
char table[ROW][COL] = {0, };

// 블럭을 게임화면 그리기
void writeToTable(void);

// 줄이 채워졌는지 확인
void checkLine(void);

// 게임화면 출력
void printTable(void);

#endif