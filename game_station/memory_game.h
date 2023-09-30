#ifndef MEMORY_GAME_H
#define MEMORY_GAME_H
#include <Arduino.h>
#include <LiquidCrystal.h>

const byte cardChar[] = {
    B11111,
	B11011,
	B10101,
	B11111,
	B11111,
	B10101,
	B11011,
	B11111};

void memoryGameplay();

#endif