#ifndef GAME_H
#define GAME_H

#include <Arduino.h>
#include "globals.h"
#include "items.h"
#include "playfield.h"

void stateGameInitLevel()
{
  runnerX = 0;
  runnerY = 28;
  score = 0;
  previousScore = 1000;
  life = 128;
  level = 0;
  showitems = B00000000;
  gameState = STATE_GAME_PLAYING ;
};



void stateGamePlaying()
{
  theGame();
  if (arduboy.justPressed(UP_BUTTON | DOWN_BUTTON | RIGHT_BUTTON)) gameState = STATE_GAME_PAUSE;
};

void stateGamePause()
{
  sprites.drawSelfMasked(35, 4, pause, 0);
  candle_draw(56, 8);
  if (arduboy.justPressed(UP_BUTTON | DOWN_BUTTON | RIGHT_BUTTON)) gameState = STATE_GAME_PLAYING ;
};

void stateGameOver()
{
  sprites.drawSelfMasked(31, 16, gameOver, 0);
  score_draw(28, 42);
  if (arduboy.justPressed(A_BUTTON | B_BUTTON)) gameState = STATE_MENU_MAIN;
};


#endif
