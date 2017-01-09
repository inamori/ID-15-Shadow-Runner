#ifndef MENU_H
#define MENU_H

#include <Arduino.h>
#include "globals.h"
#include "runner.h"

byte flameid = 0;
boolean showRunner = false;

void drawCandle (byte x, byte y)
{
  sprites.drawSelfMasked(x, y + 25, pen, 0);

}

const float ryth4 = 150;
const float ryth3 = 150;
const float ryth2 = 300;
const float rythm = 250;
const uint16_t song1[] PROGMEM = {
  587,ryth2, 523,ryth4, 587,ryth4, 
  698,ryth2, 587,ryth4, 698,ryth4, 0,ryth4,
  
  698,ryth3, 587,ryth3, 698,ryth3, 
  784,ryth3, 784,ryth3, 659,ryth3, 784,ryth3, 
  
  880,rythm, 0,50, 880,rythm, 0,50, 660,300, 784,200, 0,100,
  880,rythm, 0,50, 880,rythm, 0,50, 660,300, 784,200, 0,100,
  880,rythm, 0,50, 880,rythm, 0,50, 660,300, 784,200, 0,100,
  0,150, 880,200, 0,100, 880,150, 880,300,
  TONES_END };
  
void stateMenuIntro()
{
    sound.tones(song1);
    globalCounter = 0;
    gameState = STATE_MENU_MAIN;
};

void stateMenuMain()
{
  runnerY = 0;
  if (arduboy.everyXFrames(4)) runnerX += 4;
  if (runnerX > 127)
  {
    runnerX = -127;
    showRunner = !showRunner;
  }
  sprites.drawSelfMasked(16, 0, menuTitle, 0);
  sprites.drawSelfMasked(49, 26, menuItems, 0);
  drawCandle(10, (menuSelection - 2) * 15);
//  for (byte i = 2; i < 5; i++)
//  {
//    if (menuSelection != i) {
//      sprites.drawErase(49, (i * 8) + 10, menuShade, 0);
//      sprites.drawErase(82, (i * 8) + 10, menuShade, 0);
//    }
//  }
  if (showRunner)
  {
    sprites.drawSelfMasked(runnerX, -2, spotLight, 0);
    drawRunner();
  }
  if (arduboy.justPressed(UP_BUTTON) && (menuSelection > 2)) menuSelection--;
  else if (arduboy.justPressed(DOWN_BUTTON) && (menuSelection < 3)) menuSelection++;
  else if (arduboy.justPressed(A_BUTTON | B_BUTTON))
  {
    gameState = menuSelection;
  }

}

void stateMenuHelp()
{
  sprites.drawSelfMasked(32, 0, qrcode, 0);
  if (arduboy.justPressed(A_BUTTON | B_BUTTON)) gameState = STATE_MENU_MAIN;
}

void stateMenuInfo()
{
  sprites.drawSelfMasked(16, 0, menuTitle,0);
  sprites.drawSelfMasked(0, 25, menuInfo, 0);
  if (arduboy.justPressed(A_BUTTON | B_BUTTON)) gameState = STATE_MENU_MAIN;
}

void stateMenuSoundfx()
{
  // placeHolder
}


void stateMenuPlay()
{
  gameState = STATE_GAME_INIT_LEVEL;
}


#endif
