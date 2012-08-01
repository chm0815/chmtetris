#include "game.h"

int block0[BLOCK_WIDTH*BLOCK_HEIGHT]=
     {0,0,0,0,
      0,1,1,0,
      0,1,1,0,
      0,0,0,0
     };

int block1[BLOCK_WIDTH*BLOCK_HEIGHT]=
     {0,0,2,0,
      0,0,2,0,
      0,0,2,0,
      0,0,2,0
     };

int block2[BLOCK_WIDTH*BLOCK_HEIGHT]=
     {0,0,0,0,
      0,0,3,3,
      0,3,3,0,
      0,0,0,0
     };
     
int block3[BLOCK_WIDTH*BLOCK_HEIGHT]=
     {0,0,0,0,
      4,4,0,0,
      0,4,4,0,
      0,0,0,0
     };

int block4[BLOCK_WIDTH*BLOCK_HEIGHT]=
     {0,0,5,0,
      0,0,5,0,
      0,5,5,0,
      0,0,0,0
     };

int block5[BLOCK_WIDTH*BLOCK_HEIGHT]=
     {0,6,0,0,
      0,6,0,0,
      0,6,6,0,
      0,0,0,0
     };
     
int block6[BLOCK_WIDTH*BLOCK_HEIGHT]=
     {0,0,0,0,
      0,7,0,0,
      7,7,7,0,
      0,0,0,0
     };


void initGame(void)
{
     memset(field,0,sizeof(field));

     score = 0;
     level = 0;
     lines = 0;
     block[0] = block0;
     block[1] = block1;
     block[2] = block2;
     block[3] = block3;
     block[4] = block4;
     block[5] = block5;
     block[6] = block6;
}

int removeFullLines(void)
{
    int x,y,y1,ret=0;
    for(y=FIELD_HEIGHT-1;y>0;y--)
    {
        for(x=0;x<FIELD_WIDTH;x++)
        {
            if(!*(field+y*FIELD_WIDTH+x))
               break;
        }
        if(x==FIELD_WIDTH)
        {
            ret++;
            for(y1=y;y1>0;y1--)
            {
                for(x=0;x<FIELD_WIDTH;x++)
                {
                    *(field+x+y1*FIELD_WIDTH) = *(field+x+(y1-1)*FIELD_WIDTH);
                }
            }
            y++;
        }
    }
    return ret;
}

void calcBlockInfo(const int* block,BlockInfo* bi)
{
     int x,y;
     
     bi->ox = BLOCK_WIDTH - 1;
     bi->oy = BLOCK_HEIGHT - 1;
     bi->w = 0;
     bi->h = 0;
     
     for(x=0;x<BLOCK_WIDTH;x++)
     {   
          for(y=0;y<BLOCK_HEIGHT;y++)
          {
               if(*(block+y*BLOCK_WIDTH+x)!=0)
               {
                    if(x<bi->ox)
                       bi->ox = x;
                    if(y<bi->oy)
                       bi->oy = y;
                    if(x>bi->w)
                       bi->w = x;
                    if(y>bi->h)
                       bi->h = y;
               }            
          } 
     }   
     printf("Blockinfo: ox=%d oy=%d w=%d h=%d\n",bi->ox,bi->oy,bi->w,bi->h);
}

void insertBlock(int *block)
{
     int x,y;
     for(x=bi.ox;x<=bi.w;x++)
     {
          for(y=bi.oy;y<=bi.h;y++)
          {
                if(*(block+x+y*BLOCK_WIDTH))
                {
                    if(y+posY>=0 &&(x+posX)>=0)
                       *(field+posX+x+(y+posY)*FIELD_WIDTH) = *(block+x+y*BLOCK_WIDTH);
                }
          }
     }
}

void deleteBlock(int *block)
{
     int x,y;
     for(x=bi.ox;x<=bi.w;x++)
     {
          for(y=bi.oy;y<=bi.h;y++)
          {
                if(*(block+y*BLOCK_WIDTH+x)!=0)
                {
                   if(posX+x>=0 && (y+posY)>=0)
                    *(field+posX+x+(y+posY)*FIELD_WIDTH) = 0;
                }
          }
     }
}

int moveRight(int *block)
{
     int x,y;
     
     // prüfen ob ein rechtsschieben möglich ist
     // auf Feldrand
     if((posX+bi.w+1)>=FIELD_WIDTH)
        return 1;

     // auf Nachbarstein
     for(y=bi.oy;y<=bi.h;y++)
          for(x=bi.w;x>=0;x--)
          {
              if(posY+y>=0)
              if(*(block+y*BLOCK_WIDTH+x)!=0)
                   if(*(field+(posY+y)*FIELD_WIDTH+x+posX+1)!=0)
                     return 1;
                 else break;
           } 
    
     // rechtsschieben
     deleteBlock(block);
     posX++;
     insertBlock(block);
    
    return 0;
}

int moveLeft(int *block)
{
    int x,y;
    // prüfen ob ein linksschieben möglich ist
     if(posX<=-bi.ox)
        return 1;

     
     for(y=bi.oy;y<=bi.h;y++)
          for(x=bi.ox;x<=bi.w;x++) 
          {
              if(*(block+y*BLOCK_WIDTH+x)!=0)
              {
                   if(posY+y>=0)
                   if(*(field+(posY+y)*FIELD_WIDTH+x+posX-1)!=0)
                     return 1;
                    else break;
               }
           } 
    
     // linksschieben 
     deleteBlock(block);
     posX--;
     insertBlock(block);
    
    return 0;
}

int moveDown(int *block)
{
     int x,y;
     
     // prüfen ob ein hinunterschieben möglich ist
     // Feldrand
     if((posY+bi.h+1)>=FIELD_HEIGHT)
        return 1;

     // Stein darunter?
     for(x=bi.ox;x<=bi.w;x++)
     {
          for(y=bi.h;y>=bi.oy;y--)
          {
              if(posY+y+1>=0)
              {
                 if(*(block+y*BLOCK_WIDTH+x)!=0)
                 {
                    if(*(field+(posY+y+1)*FIELD_WIDTH+x+posX)!=0)
                    {
                        return 2;
                    }
                    else break;
                  }
              }
          }
     }     
    
     // hinunterschieben 
     deleteBlock(block);
     posY++;
     insertBlock(block);
     printf("posX=%d posY=%d\n",posX,posY);
     return 0;
}



int rotateRight(int *block)
{
     int tempBlock[BLOCK_HEIGHT*BLOCK_WIDTH];
     
     int x,y,newx,newy;
     for(x=0;x<BLOCK_WIDTH;x++)
     {   
         newy = x;
         for(y=0;y<BLOCK_HEIGHT;y++)
         {
              newx = BLOCK_WIDTH-1-y;

              *(tempBlock+newx+newy*BLOCK_WIDTH) = *(block+x+y*BLOCK_WIDTH);
         }
     }
     
     for(x=0;x<BLOCK_WIDTH;x++)
         for(y=0;y<BLOCK_HEIGHT;y++)
         {
              if(*(tempBlock+x+y*BLOCK_WIDTH) && !*(block+x+y*BLOCK_WIDTH))
                 if(*(field+x+posX+(posY+y)*FIELD_WIDTH))
                    return 1;
         }
     
     BlockInfo tempBlockInfo;
     calcBlockInfo(tempBlock,&tempBlockInfo);
     if(posX+tempBlockInfo.w>=FIELD_WIDTH)
          return 2;
     if(posY+tempBlockInfo.h>=FIELD_HEIGHT)
         return 3;   
     if(posX+tempBlockInfo.ox-bi.ox+1<0)
         return 4;
     
     deleteBlock(block);
     memcpy(block,tempBlock,sizeof(int)*BLOCK_HEIGHT*BLOCK_WIDTH);
     calcBlockInfo(block,&bi);
     insertBlock(block);
     
     return 0;
}

int height(void)
{
    int x,y;
    for(y=0;y<FIELD_HEIGHT;y++)
        for(x=0;x<FIELD_WIDTH;x++)
        {
            if(*(field+y*FIELD_WIDTH+x))
               return FIELD_HEIGHT - y;             
        } 
}
