#ifndef RUNNER_H
#define RUNNER_H

#include <Arduino.h>
#include "globals.h"

//define runner states
#define RUNNER_RUNNING               0
#define RUNNER_JUMPING               8
#define RUNNER_DUCKING               9

int runnerX = -127;
int runnerY = 0;
byte runnerframe = 0;
bool jumping = false;
bool ducking = false;
byte leap[] = {19, 13, 8, 6, 8, 13, 19};

byte eyeX[] = {14, 14, 14, 14, 16, 16, 20, 18, 12, 10};
byte eyeY[] = {7, 8, 9, 8, 7, 8, 9, 8, 6, 5};
byte eyeFrame[] = {0, 0, 0, 0, 1, 1, 2, 2, 1, 1};

void drawRunner()
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
    sprites.drawErase(runnerX, runnerY, shadowRunner, 8);
    sprites.drawSelfMasked(runnerX + eyeX[8], runnerY + eyeY[8], shadowRunnerEyes, eyeFrame[8]);
  }

  else if (ducking)
  {
    jumping = false;
    runnerY = 38;
    if (runnerframe > 14)
    {
      runnerY = 28;
      ducking = false;
      runnerframe = RUNNER_RUNNING;
    }
    sprites.drawErase(runnerX, runnerY, shadowRunner, 9);
    sprites.drawSelfMasked(runnerX + eyeX[9], runnerY + eyeY[9], shadowRunnerEyes, eyeFrame[9]);
  }

  else {
    if (runnerframe > 7)runnerframe = RUNNER_RUNNING;

    sprites.drawErase(runnerX, runnerY, shadowRunner, runnerframe);
    sprites.drawSelfMasked(runnerX + eyeX[runnerframe], runnerY + eyeY[runnerframe], shadowRunnerEyes, eyeFrame[runnerframe]);
  }
}

void checkRunner()
{
  if (lifePlayer < 0)
  {
    gameState = STATE_GAME_OVER;
    delay(1000L);
  }
}

#endif
