#include <ncurses.h>
#include <stdlib.h>

#include "shape.h"
#include "table.h"

void controlBlock(int action)
{
    Block temp = copyBlock(current);

    switch (action) {
        case 's':
            temp.row++;
            if (checkPosition(temp)) { current.row++; }
            else {
                writeToTable();
                checkLine();
                getNewBlock(); // 블럭이 바닥에 닿으면 새로운 블럭 생성
            }
            break;
        
        case 'd':
            temp.col++;
            if (checkPosition(temp)) { current.col++; }
            break;

        case 'a':
            temp.col--;
            if (checkPosition(temp)) { current.col--; }
        
        case 'w':
            rotateBlock(temp);
            if (checkPosition(temp)) {rotateBlock(current); }
            break;
        case 'q':
            exit(EXIT_SUCCESS);
    }

    deleteBlock(temp);

    printTable();
}