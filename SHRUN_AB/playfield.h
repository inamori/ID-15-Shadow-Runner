#ifndef PLAYFIELD_H
#define PLAYFIELD_H

#include <Arduino.h>
#include "globals.h"
#include "runner.h"
#include "items.h"

int background1step = 0;
int background2step = 128;
byte background1id = 0;
byte background2id = 1;
int fence1step = 0;
int fence2step = 128;
byte fence1id = 0;
byte fence2id = 1;
int forgroundstep = 128;
byte forgroundid = 0;

boolean collide(int y1, int y2, int xx1, int yy1, int xx2, int yy2)
{
  if (35 <= xx1) return false;
  else if (23 >= xx2) return false;
  else if (y2 <= yy1) return false;
  else if (y1 >= yy2) return false;
  else return true;
}



void score_draw(int scoreX, int scoreY)
{
  arduboy.drawBitmap(scoreX, scoreY, score_bitmap, 32, 8, 1);
  char buf[8];
  ltoa(score, buf, 10); // Numerical base used to represent the value as a string, between 2 and 36, where 10 means decimal base
  char charLen = strlen(buf);
  char pad = 8 - charLen;

  //draw 0 padding
  for (byte i = 0; i < pad; i++)
  {
    sprites.drawSelfMasked(scoreX + 30 + (5 * i), scoreY, numbers, 0);
  }

  for (byte i = 0; i < charLen; i++)
  {
    char digit = buf[i];
    byte j;
    if (digit <= 48)
    {
      digit = 0;
    }
    else {
      digit -= 48;
      if (digit > 9) digit = 0;
    }

    for (byte z = 0; z < 10; z++)
    {
      if (digit == z) j = z;
    }
    sprites.drawSelfMasked(scoreX + 30 + (pad * 5) + (5 * i), scoreY, numbers, digit);
  }
}

void theGame()
{
  //draw the background
  //------------------
  if (arduboy.everyXFrames(3))
  {
    background1step -= 1;
    background2step -= 1;
  }
  if (background1step < -127)
  {
    background1step = 128;
    background1id = random(0, 2);
  }
  if (background2step < -127)
  {
    background2step = 128;
    background2id = random(1, 5);
  }
  arduboy.drawBitmap(background1step, 0, background_bitmaps[background1id], 128, 52, 1);
  arduboy.drawBitmap(background2step, 0, background_bitmaps[background2id], 128, 52, 1);

  // draw the fence
  //---------------
  if (arduboy.everyXFrames(1))
  {
    fence1step -= 1;
    fence2step -= 1;
  }
  arduboy.drawBitmap(fence1step, 36, fence_bitmaps[fence1id], 128, 16, 0);
  arduboy.drawBitmap(fence2step, 36, fence_bitmaps[fence2id], 128, 16, 0);
  if (fence1step < -127)
  {
    fence1step = 128;
    fence1id = random(0, 3);
  }
  if (fence2step < -127)
  {
    fence2step = 128;
    fence2id = random(2, 5);
  }


  // draw the items
  //---------------

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
    arduboy.drawBitmap(itemX[0], 36, stone_bitmap, 16, 16, 0);
    if (collide(runnerY, runnerY + 24, itemX[0] + 3, 38, itemX[0] + 13, 52) == true)
    {
      life -= 4;
      sound.tone(175, 100);
    }

  }

  if ((showitems & B00000010) == B00000010)
  {
    arduboy.drawBitmap(itemX[1], 36, stone_bitmap, 16, 16, 0);
    if (collide(runnerY, runnerY + 24, itemX[1] + 3, 38, itemX[1] + 13, 52) == true)
    {
      life -= 4;
      sound.tone(175, 100);
    }
  }

  if ((showitems & B00000100) == B00000100)
  {
    switch (birdframe)
    {
      case 0:
        arduboy.drawBitmap(itemX[2], 16, bird1_bitmap, 16, 16, 0);
        break;
      case 1:
        arduboy.drawBitmap(itemX[2], 21, bird2_bitmap, 16, 8, 0);
        break;
      case 2:
        arduboy.drawBitmap(itemX[2], 23, bird3_bitmap, 16, 8, 0);
        break;
      case 3:
        arduboy.drawBitmap(itemX[2], 23, bird4_bitmap, 16, 16, 0);
        break;
      case 4:
        arduboy.drawBitmap(itemX[2], 22, bird5_bitmap, 16, 16, 0);
        break;
      case 5:
        arduboy.drawBitmap(itemX[2], 23, bird6_bitmap, 16, 16, 0);
        break;
      case 6:
        arduboy.drawBitmap(itemX[2], 23, bird7_bitmap, 16, 8, 0);
        break;
      case 7:
        arduboy.drawBitmap(itemX[2], 18, bird8_bitmap, 16, 8, 0);
        break;
    }
    if (collide(runnerY, runnerY + 24, itemX[2] + 2, 16, itemX[2] + 16, 32) == true)
    {
      life -= 2;
      sound.tone(523, 50);
    }
  }

  if ((showitems & B00001000) == B00001000)
  {
    switch (birdframe)
    {
      case 0:
        arduboy.drawBitmap(itemX[3], 16, bird1_bitmap, 16, 16, 0);
        break;
      case 1:
        arduboy.drawBitmap(itemX[3], 21, bird2_bitmap, 16, 8, 0);
        break;
      case 2:
        arduboy.drawBitmap(itemX[3], 23, bird3_bitmap, 16, 8, 0);
        break;
      case 3:
        arduboy.drawBitmap(itemX[3], 23, bird4_bitmap, 16, 16, 0);
        break;
      case 4:
        arduboy.drawBitmap(itemX[3], 22, bird5_bitmap, 16, 16, 0);
        break;
      case 5:
        arduboy.drawBitmap(itemX[3], 23, bird6_bitmap, 16, 16, 0);
        break;
      case 6:
        arduboy.drawBitmap(itemX[3], 23, bird7_bitmap, 16, 8, 0);
        break;
      case 7:
        arduboy.drawBitmap(itemX[3], 18, bird8_bitmap, 16, 8, 0);
        break;
    }
    if (collide(runnerY, runnerY + 24, itemX[3] + 2, 4, itemX[3] + 16, 20) == true)
    {
      life -= 2;
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
    switch (heartframe)
    {
      case 0:
        arduboy.drawBitmap(itemX[4], 4, heart1_bitmap, 16, 16, 0);
        break;
      case 1:
        arduboy.drawBitmap(itemX[4], 4, heart2_bitmap, 16, 16, 0);
        break;
    }
    if (collide(runnerY, runnerY + 24, itemX[4] + 2, 4, itemX[4] + 12, 20) == true)
    {
      showitems ^= B00100000;
      itemX[4] = 128;
      life = 128;
      score += 500;
      sound.tone(750, 200);
    }
  }


  if (arduboy.everyXFrames(6))
  {
    birdframe++;
    heartframe = !heartframe;
  }
  if (birdframe > 7) birdframe = 0;

  //draw the runner
  //---------------
  runner_draw();

  //draw the forground trees
  //------------------------
  if (forgroundstep == 128) forgroundid = random(0, 3);
  arduboy.drawBitmap(forgroundstep, -4, forground_bitmaps[forgroundid], 56, 56, 0);

  if (arduboy.everyXFrames(2))
  {
    forgroundstep -= 4;
  }
  if (forgroundstep < -255) forgroundstep = 128;



  //draw score and lives on the screen
  if (arduboy.everyXFrames(16 - 2 * level))
  {
    life--;
  }
  arduboy.drawBitmap(2, 53, life_bitmap, 24, 6, 1);
  arduboy.fillRect(0, 60, 128, 66, 1);
  arduboy.fillRect(0, 61, life, 2, 0);
  if (life < 64)
  {
    showitems = showitems | B00100000;
  }
  score_draw(57, 54);

  //level_update();
  if (previousScore < score)
  {
    level += 1;
    previousScore += 1000;
    if (level > 7) level = 7;
  }
  score++;

  if (arduboy.justPressed(B_BUTTON))
  {
    if (!jumping)
    {
      jumping = true;
      runnerframe = RUNNER_JUMPING;
    }
  }
  if (arduboy.justPressed(A_BUTTON | LEFT_BUTTON))
  {
    if (!ducking && !jumping)
    {
      ducking = true;
      runnerframe = RUNNER_DUCKING;
    }
  }

  //check the runner's state
  if (life < 0)
  {
    gameState = STATE_GAME_OVER;
    delay(1000L);
  }
}

#endif
