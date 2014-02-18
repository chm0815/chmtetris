#include "grafic.h"

void drawStat(BITMAP *dest,int x,int y)
{
     int color = makecol(230, 100, 50);
     
     textprintf_ex(dest, font, x, y, color,
                    -1, "Score: %d", score);
     
     textprintf_ex(dest, font, x, y+25, color,
                    -1, "Level: %d", level);
     textprintf_ex(dest, font, x, y+50, color,
                    -1, "Lines: %d", lines);
}

void drawNextBlock(BITMAP *dest,int offsetX,int offsetY)
{
   const int colors[BLOCKS+1] =
   {
    makecol(0,0,0),
    makecol(255,0,0),
    makecol(0,255,0),
    makecol(0,0,255),
    makecol(255,255,0),
    makecol(0,255,255),
    makecol(255,0,255),
    makecol(0,255,133)
   };
   
   int x,y;
   
   int w = 20;
   int h = 20;
   int border = 2;
   
   for(x=0;x<BLOCK_WIDTH;x++)
      for(y=0;y<BLOCK_HEIGHT;y++)
      {
         rectfill(dest,x*w+offsetX,y*h+offsetY,x*w+offsetX+w,y*h+offsetY+h,makecol(20,20,20));
         rectfill(dest,x*w+offsetX+border,y*h+offsetY+border,x*w+offsetX+w-border,y*h+offsetY+h-border,colors[block[nextBlock][y*BLOCK_WIDTH+x]]);
      }
}

void drawField(BITMAP* dest,int offsetX,int offsetY)
{    
   const int colors[BLOCKS+1] =
   {
    makecol(100,100,130),
    makecol(255,0,0),
    makecol(0,255,0),
    makecol(0,0,255),
    makecol(255,255,0),
    makecol(0,255,255),
    makecol(255,0,255),
    makecol(0,255,133)
   };
  
   const int w = 20;
   const int h = 20;
   
   int x,y,i;
   int border = 1;
   
   for(y=0;y<FIELD_HEIGHT;y++)
   {
       for(x=0;x<FIELD_WIDTH;x++)
       {
           i = *(field+y*FIELD_WIDTH+x);   
           rectfill(dest,x*w+offsetX,y*h+offsetY,x*w+offsetX+w,y*h+offsetY+h,makecol(10,20,20));              
           //rectfill(dest,x*w+offsetX,y*h+offsetY,x*w+offsetX+w,y*h+offsetY+h,colors[i]);
           rectfill(dest,x*w+offsetX+border,y*h+offsetY+border,x*w+offsetX+w-border,y*h+offsetY+h-border,colors[i]);
       }
   }
}

void welcomeScreen(BITMAP *dest)
{
    textprintf_ex(dest, font, 300, 100, makecol(200,20,20),
                    -1, "Tetris");
    readkey();
}

void gameOverScreen(BITMAP *dest,int offsetX,int offsetY)
{
     const int colors[BLOCKS+1] =
   {
    makecol(100,34,130),
    makecol(34,100,0),
    makecol(200,0,0),
    makecol(200,250,20),
    makecol(0,30,0),
    makecol(100,255,20),
    makecol(50,0,255),
    makecol(0,0,133)
   };
  
   const int w = 20;
   const int h = 20;
   
   int x,y,i;
   int border = 1;
   int restTime = 30;
   
   for(y=FIELD_HEIGHT-1;y>=0;y--)
   {
       for(x=0;x<FIELD_WIDTH;x++)
       {
           i = *(field+y*FIELD_WIDTH+x);   
           rectfill(dest,x*w+offsetX,y*h+offsetY,x*w+offsetX+w,y*h+offsetY+h,makecol(10,20,20));              
           rectfill(dest,x*w+offsetX+border,y*h+offsetY+border,x*w+offsetX+w-border,y*h+offsetY+h-border,colors[i]);
           rest(restTime);
           if(key[KEY_ESC]) restTime = 0;
       }
   }
}

void drawFooter(BITMAP *dest,int x,int y)
{
     textprintf_ex(dest, font, x, y, makecol(200,20,20),
                    -1, "developed by Maurer C.");
}

void drawHeader(BITMAP *dest,int x,int y)
{
     textprintf_ex(dest, font, x, y, makecol(200,20,20),
                    -1, "Tetris %s",T_VERSION);
}
