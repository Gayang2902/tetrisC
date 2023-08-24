#ifndef SHAPE_H
#define SHAPE_H

typedef struct block * Block;

// 원본 블럭을 복사
Block copyBlock(Block block);

// 블럭 삭제
Block deleteBlock(Block block);

// 위치 확인
int checkPosition(Block block);

// 랜덤한 블럭 생성
Block getNewBlock(void);

// 블럭 회전
void rotateBlock(Block block);

#endif
