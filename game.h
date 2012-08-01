#ifndef __GAME_H__
#define __GAME_H__

#include <stdlib.h>
#include <stdio.h>

#define T_VERSION "V 0.90"

#define FIELD_WIDTH 11
#define FIELD_HEIGHT 19
#define BLOCKS 7
#define BLOCK_WIDTH 4
#define BLOCK_HEIGHT 4

typedef struct 
{
        int ox,oy;
        int w,h;
}BlockInfo;

int field[FIELD_WIDTH*FIELD_HEIGHT];
int* block[BLOCKS];

int score;
int level;
int lines;

int posX,posY;
BlockInfo bi;
int curBlock,nextBlock;

int removeFullLines(void);
void calcBlockInfo(const int* block,BlockInfo* bi);
void insertBlock(int *block);
void deleteBlock(int *block);
int moveRight(int *block);
int moveLeft(int *block);
int moveDown(int *block);
int rotateRight(int *block);
void initGame(void);
int height(void);


#endif
