#ifndef ITEMS_H
#define ITEMS_H

#include <Arduino.h>
#include "globals.h"

byte showitems =  B00000000;        // this byte holds all the items the player runs into during the game
//                   | ||||
//                   | |||└->  stone1
//                   | ||└-->  stone2
//                   | |└--->  bird1
//                   | └---->  bird2
//                   |
//                   └------>  extra life

byte birdFrame = 0;
boolean heartFrame = 0;

int itemX[6] = { -64, 96, 48, 128, 128};

boolean collide(int y1, int y2, int xx1, int yy1, int xx2, int yy2)
{
  if (35 <= xx1) return false;
  else if (23 >= xx2) return false;
  else if (y2 <= yy1) return false;
  else if (y1 >= yy2) return false;
  else return true;
}


void drawItems()
{

  if (arduboy.everyXFrames(1))
  {
    itemX[0] -= 2;
    if (itemX[0] < -127)
    {
      switch (random(0, 2))  //stone 1
      {
        case 0:
          showitems ^= B00000001;
          break;
        case 1:
          showitems |= B00000001;
          break;
      }
      itemX[0] = 128;
    }

    itemX[1] -= 2;
    if (itemX[1] < -127)
    {
      switch (random(0, 2))  //stone 2
      {
        case 0:
          showitems ^= B00000010;
          break;
        case 1:
          showitems |= B00000010;
          break;
      }
      itemX[1] = 128;
    }

    itemX[2] -= 2;
    if (itemX[2] < -127)
    {
      switch (random(0, 2))  //bird1
      {
        case 0:
          showitems ^= B00000100;
          break;
        case 1:
          showitems |= B00000100;
          break;
      }
      itemX[2] = 128;
    }

    itemX[3] -= 2;
    if (itemX[3] < -127)
    {
      switch (random(0, 2))  //bird2
      {
        case 0:
          showitems ^= B00001000;
          break;
        case 1:
          showitems |= B00001000;
          break;
      }
      if ((showitems & B00000010) == B00000010)
      {
        if ((showitems & B00001000) == B00001000) showitems ^= B00001000; // if stone2 no Bird2
      }
      itemX[3] = 128;
    }
  }


  if ((showitems & B00000001) == B00000001)
  {
    sprites.drawPlusMask(itemX[0], 36, stone_plus_mask, 0);
    if (collide(runnerY, runnerY + 24, itemX[0] + 3, 38, itemX[0] + 13, 52) == true)
    {
      lifePlayer -= 4;
      sound.tone(175, 100);
    }

  }

  if ((showitems & B00000010) == B00000010)
  {
    sprites.drawPlusMask(itemX[1], 36, stone_plus_mask, 0);
    if (collide(runnerY, runnerY + 24, itemX[1] + 3, 38, itemX[1] + 13, 52) == true)
    {
      lifePlayer -= 4;
      sound.tone(175, 100);
    }
  }

  if ((showitems & B00000100) == B00000100)
  {
    sprites.drawErase(itemX[2], 16, bird, birdFrame);

    if (collide(runnerY, runnerY + 24, itemX[2] + 2, 16, itemX[2] + 16, 32) == true)
    {
      lifePlayer -= 2;
      sound.tone(523, 50);
    }
  }

  if ((showitems & B00001000) == B00001000)
  {
    sprites.drawErase(itemX[3], 16, bird, birdFrame);

    if (collide(runnerY, runnerY + 24, itemX[3] + 2, 4, itemX[3] + 16, 20) == true)
    {
      lifePlayer -= 2;
      sound.tone(523, 50);
    }
  }

  if ((showitems & B00100000) == B00100000)
  {
    if (arduboy.everyXFrames(1))
    {
      itemX[4] -= 2;
      if (itemX[4] < -24)
      {
        if ((showitems & B00100000) == B00100000) showitems ^= B00100000;
        itemX[4] = 128;
      }
    }
    sprites.drawErase(itemX[4], 4, heart, heartFrame);

    if (collide(runnerY, runnerY + 24, itemX[4] + 2, 4, itemX[4] + 12, 20) == true)
    {
      showitems ^= B00100000;
      itemX[4] = 128;
      lifePlayer = 128;
      scorePlayer += 500;
      sound.tone(750, 200);
    }
  }


  if (arduboy.everyXFrames(6))
  {
    birdFrame++;
    heartFrame = !heartFrame;
  }
  if (birdFrame > 7) birdFrame = 0;
}


#endif
