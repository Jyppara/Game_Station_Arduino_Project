#ifndef MEMORY_GAME_H
#define MEMORY_GAME_H
#include <Arduino.h>
#include <LiquidCrystal.h>

const byte cardChar[] = {
	B11111,
	B10001,
	B10001,
	B10001,
	B10001,
	B10001,
	B10001,
	B11111};

const byte selectedCardChar[] = {
	B00000,
	B01110,
	B01110,
	B01110,
	B01110,
	B01110,
	B01110,
	B00000};

void memoryGameplay();
int mapPotentiometerValue(int numberOfCards);
void printAllCards(int numberOfCards, int potentioMeterIndex);
void startAnimation(int numberOfCards, int potentioMeterIndex);

#endif