//#define USE_CONSOLE
#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include "game.h"
#include "grafic.h"

volatile int timer = 0;
//volatile unsigned long ticks = 0;
BITMAP *doubleBuffer = NULL;

float moveCounter = 0.0f;

int init(int w,int h);
void cleanUp(void);
void timer_handler(void);
void processInput(void);

int main(int argc, char *argv[])
{
    init(640,480);
     
    initGame();
    timer = 0;

    int delLines = 0;
    curBlock = rand()%BLOCKS;
    calcBlockInfo(block[curBlock],&bi);

    posX = FIELD_WIDTH/2-bi.w;
    posY = -BLOCK_HEIGHT+(BLOCK_HEIGHT-bi.h-1);

    nextBlock = rand()%BLOCKS; 
    
    //welcomeScreen(screen);
        
    while(!key[KEY_ESC])
    {        
        if(timer>0)
        {
           timer--;
           moveCounter += 2.5f/60.0f + level/200.0f;
           if(moveCounter>=1.0)
           {
              moveCounter = 0.0f;
              int moved;
              if(moved = moveDown(block[curBlock]))
              {           
                   delLines = removeFullLines();
                   score += delLines*delLines*(level+10)+level;
                   lines += delLines;
                   level = (int)(lines/10);

                   if(height()==FIELD_HEIGHT)
                   {
                       gameOverScreen(screen,100,50);
                       char buf[300];
                       sprintf(buf,"Game Over!\nScore: %d\nLines: %d",score,lines);                 
                       allegro_message(buf);
                       break;
                   } 
                   
                   curBlock = nextBlock;
                   nextBlock = rand()%BLOCKS;
                   calcBlockInfo(block[curBlock],&bi);
                   posX = (FIELD_WIDTH)/2-bi.w;
                   posY = -BLOCK_HEIGHT+(BLOCK_HEIGHT-bi.h-1);
                   
              }
           }
        }   
        processInput(); 
        clear(doubleBuffer);
        drawField(doubleBuffer,100,50);
        drawNextBlock(doubleBuffer,400,100);
        drawStat(doubleBuffer,400,220);
        drawFooter(doubleBuffer,50,460);
        drawHeader(doubleBuffer,200,20);
        blit(doubleBuffer, screen, 0, 0, 0, 0, doubleBuffer->w, doubleBuffer->h);
        rest(5);
    }
    
    cleanUp();
  
  return 0;
}
END_OF_MAIN()

int init(int w,int h)
{
    srand(time(NULL));
    allegro_init();
    install_timer();
    install_keyboard();
    LOCK_VARIABLE(timer)
    LOCK_FUNCTION(timer_handler)   
    set_gfx_mode(GFX_AUTODETECT_WINDOWED,w,h,0,0);
    
    doubleBuffer = create_bitmap(w,h);
    
    install_int_ex(timer_handler,BPS_TO_TIMER(60));
    
    return 0;
}

void cleanUp(void)
{
     if(doubleBuffer != NULL)
       destroy_bitmap(doubleBuffer);
}

void processInput(void)
{
     static int right,left,down,up,enter,space;

     if(right && !key[KEY_RIGHT])
     {
         right = 0;
         //printf("moveRight\n");
         moveRight(block[curBlock]);
     }
     else if(key[KEY_RIGHT])
     right = 1;
     
     if(left && !key[KEY_LEFT])
     {
         left = 0;
         //printf("moveLeft\n");
         moveLeft(block[curBlock]);
     }
     else if(key[KEY_LEFT])
     left = 1;
     
     if(up && !key[KEY_UP])
     {
         up = 0;
         //printf("rotateRight\n");
         rotateRight(block[curBlock]);
     }
     else if(key[KEY_UP])
     up = 1;
     
     if(down && !key[KEY_DOWN])
     {
         down = 0;
         //printf("moveDown\n");
         //moveDown(block[curBlock]);
         moveCounter = 1.0f;
     }
     else if(key[KEY_DOWN])
     down = 1;
     
     if(enter && !key[KEY_ENTER])
     {
         enter = 0;
         
         while(!moveDown(block[curBlock]));
         moveCounter = 1.0f;     
     }
     else if(key[KEY_ENTER])
     enter = 1;
     
     if(space && !key[KEY_SPACE])
     {
         space = 0;
         
         while(!moveDown(block[curBlock]));
         moveCounter = 1.0f;     
     }
     else if(key[KEY_SPACE])
     space = 1;
     
     
}

void timer_handler(void)
{
     timer++;
     //ticks++;
}
END_OF_FUNCTION(timer_handler)
