#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "shape.h"
#include "table.h"

struct block {
	char** shape;
	int width;
	int row;
	int col;
};

// 테트리스 블럭 설정 (모양과 너비만 정의하고 위치는 나중에 정의)
// 모양을 포인터 배열로 캐스팅 후 각각의 포인터에 모양을 배열로 캐스팅하여 형태로 삽입
const struct block  blockFrames[7] = {
    {(char *[]) { (char []){0, 1, 1}, (char []){1, 1, 0}, (char[]){0, 0, 0} }, 3}, // S 모양 블럭
    {(char *[]) { (char []){1, 1, 0}, (char []){0, 1, 1}, (char[]){0, 0, 0} }, 3}, // Z 모양 블럭
    {(char *[]) { (char []){0, 1, 0}, (char []){1, 1, 1}, (char[]){0, 0, 0} }, 3}, // T 모양 블럭
    {(char *[]) { (char []){0, 0, 1}, (char []){1, 1, 1}, (char[]){0, 0, 0} }, 3}, // L 모양 블럭
    {(char *[]) { (char []){1, 0, 0}, (char []){1, 1, 1}, (char[]){0, 0, 0} }, 3}, // ㄱ 모양 블럭
    {(char *[]) { (char []){1, 1}, (char []){1, 1}}, 2},                          // 네모 블럭
    {(char *[]) { (char []){0, 0, 0, 0}, (char []){1, 1, 1, 1}, (char[]){0, 0, 0, 0}, (char []){0, 0, 0, 0} }, 4} // 작대기 블럭
};


Block copyBlock(Block block)
{
    Block newBlock = block;

    // 인자로 전달받은 블럭의 형태 복사
    char** copyShape = block.shape;
    newBlock.shape = (char**)malloc(newBlock.width * sizeof(char*));
    
    // 원본 배열(형태)로부터 복사하여 새로 생성된 블럭의 공간으로 복사
    for (int i = 0; i < newBlock.width; i++) {
        newBlock.shape[i] = (char*)malloc(newBlock.width * sizeof(char));

        for (int j = 0; j < newBlock.width; j++) {
            newBlock.shape[i][j] = copyShape[i][j];
        }
    }

    return newBlock;
}

void deleteBlock(Block block)
{
    for (int i = 0; i < block.width; i++) {
        free(block.shape[i]);
    }
    free(block.shape);
}

int checkPosition(Block block)
{
    char **shape = block.shape;
    
    for (int i = 0; i < block.width; i++) {
        for (int j = 0; j < block.width; j++) {
            // 블럭이 테이블 밖으로 나가지 않도록 처리
            if ((block.col + j < 0 || block.col + j >= COL || block.row + i >= ROW)) {
                if (shape[i][j]) { return false; }
            } else if (table[block.row + i][block.col + j] && shape[i][j]) { return false; }
        }
    }

    return true;
}

Block getNewBlock(void)
{
    srand(time(NULL));
    // 랜덤한 블럭 모양을 가져옴
    Block newShape = copyBlock(blockFrames[rand() % 7]);

    // 가져온 블럭 모양의 초기 위치 지정 (제일 위에서 생성, 가로 위치는 랜덤)
    newShape.col = rand() % (COL - newShape.width + 1);
    newShape.row = 0;

    // 기존에 생성했던 블럭을 삭제하고 대체
    deleteBlock(current);

    // 테이블 내에 블럭이 있을 자리가 없으면 게임 종료
    if (!checkPosition(current)) {
        gameOn = false;
    }

    return newShape;
}

void rotateBlock(Block block)
{
    Block temp = copyBlock(block);
    int width = block.width;

    for (int i = 0; i < width; i++) {
        for (int j = 0, k = width - 1; j < width; j++, k--) {
            block.shape[i][j] = block.shape[k][i];
        }
    }
    deleteBlock(temp);
}
