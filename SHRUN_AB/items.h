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

byte birdframe = 0;
boolean heartframe = 0;

int itemX[6] = { -64, 96, 48, 128, 128};


#endif
