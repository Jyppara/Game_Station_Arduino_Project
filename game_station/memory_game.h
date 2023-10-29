#ifndef MEMORY_GAME_H
#define MEMORY_GAME_H
#include <Arduino.h>
#include <LiquidCrystal.h>

// This header file is used to store the functions
// that are used in the memory game only.

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

const byte cursorChar[] = {
	B00000,
	B00000,
	B00000,
	B00100,
	B00000,
	B00000,
	B00000,
	B00000};

void memoryGameInterruptHandler();
void memoryGameplay();
void memoryGameIntroScreen();
void printAllCards(int numberOfCards, int potentioMeterIndex);
void startAnimation(int numberOfCards, int potentioMeterIndex);
void revealCards(int numberOfCards, int flippedCard, int potentioMeterIndex);
bool checkIfCardsMatch(int firstSelectedCardIndex, int secondSelectedCardIndex);
bool checkIfAllCardsAreRemoved();
void resetMemoryGameVariables();
void memoryGameEndScreen(int memoryGameTime);
void shuffleCards();
#endif