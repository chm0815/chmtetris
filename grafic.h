#ifndef __GRAFIC_H__
#define __GRAFIC_H__

#include "game.h"
#include <allegro.h>

void drawNextBlock(BITMAP *dest,int offsetX,int offsetY);
void drawField(BITMAP *dest,int offsetX,int offsetY);
void drawStat(BITMAP *dest,int x,int y);
void welcomeScreen(BITMAP *dest);
void gameOverScreen(BITMAP *dest,int offsetX,int offsetY);
void drawFooter(BITMAP *dest,int x,int y);
void drawHeader(BITMAP *dest,int x,int y);

#endif
