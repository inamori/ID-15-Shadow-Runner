#ifndef RUNNER_H
#define RUNNER_H

#include <Arduino.h>
#include "globals.h"

int runnerX = -127;
int runnerY = 0;
byte runnerframe = 0;
bool jumping = false;
bool ducking = false;
byte leap[] = {19, 13, 8, 6, 8, 13, 19};

void runner_draw()
{
  if (arduboy.everyXFrames(4))
  {
    runnerframe++;
  }
  if (jumping)
  {
    ducking = false;
    runnerY = leap[runnerframe - RUNNER_JUMPING];
    if (runnerframe > 14)
    {
      runnerY = 28;
      jumping = false;
      runnerframe = RUNNER_RUNNING;
    }
    arduboy.drawBitmap(runnerX + 14, runnerY + 6, eyesmask_bitmap, 8, 2, 1);
    arduboy.drawBitmap(runnerX, runnerY, runner_bitmap09, 32, 24, 0);
  }
  else if (ducking)
  {
    jumping = false;
    runnerY = 36;
    if (runnerframe > 14)
    {
      runnerY = 28;
      ducking = false;
      runnerframe = RUNNER_RUNNING;
    }
    arduboy.drawBitmap(runnerX + 12, runnerY + 7, eyesmask_bitmap, 8, 2, 1);
    arduboy.drawBitmap(runnerX, runnerY, runner_bitmap10, 32, 24, 0);
  }
  else {
    if (runnerframe > 7)runnerframe = RUNNER_RUNNING;
    switch (runnerframe)
    {
      case 0:
        arduboy.drawBitmap(runnerX + 16, runnerY + 7, eyesmask_bitmap, 8, 2, 1);
        arduboy.drawBitmap(runnerX, runnerY, runner_bitmap01, 32, 24, 0);
        break;
      case 1:
        arduboy.drawBitmap(runnerX + 16, runnerY + 8, eyesmask_bitmap, 8, 2, 1);
        arduboy.drawBitmap(runnerX, runnerY, runner_bitmap02, 32, 24, 0);
        break;
      case 2:
        arduboy.drawBitmap(runnerX + 16, runnerY + 9, eyesmask_bitmap, 8, 2, 1);
        arduboy.drawBitmap(runnerX, runnerY, runner_bitmap03, 32, 24, 0);
        break;
      case 3:
        arduboy.drawBitmap(runnerX + 16, runnerY + 8, eyesmask_bitmap, 8, 2, 1);
        arduboy.drawBitmap(runnerX, runnerY, runner_bitmap04, 32, 24, 0);
        break;
      case 4:
        arduboy.drawBitmap(runnerX + 17, runnerY + 7, eyesmask_bitmap, 8, 2, 1);
        arduboy.drawBitmap(runnerX, runnerY, runner_bitmap05, 32, 24, 0);
        break;
      case 5:
        arduboy.drawBitmap(runnerX + 17, runnerY + 8, eyesmask_bitmap, 8, 2, 1);
        arduboy.drawBitmap(runnerX, runnerY, runner_bitmap06, 32, 24, 0);
        break;
      case 6:
        arduboy.drawBitmap(runnerX + 22, runnerY + 9, eyesmask_bitmap, 8, 2, 1);
        arduboy.drawBitmap(runnerX, runnerY, runner_bitmap07, 32, 24, 0);
        break;
      case 7:
        arduboy.drawBitmap(runnerX + 20, runnerY + 8, eyesmask_bitmap, 8, 2, 1);
        arduboy.drawBitmap(runnerX, runnerY, runner_bitmap08, 32, 24, 0);
        break;
    }
  }
}

#endif
