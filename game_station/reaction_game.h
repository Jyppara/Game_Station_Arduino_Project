#ifndef REACTION_GAME_H
#define REACTION_GAME_H
#include <Arduino.h>
#include <LiquidCrystal.h>

// This header file is used to store the functions
// that are used in the REACTION game only.

void reactionGamePlay();
void randomDelay(int lowerBound, int upperBound);
unsigned long oneCycle(String waitingMessage);
void calculateScores(unsigned long firstTry, unsigned long secondTry, unsigned long thirdTry, unsigned long &averageReactionTime, unsigned long &bestReactionTime);
void printScores(unsigned long averageReactionTime, unsigned long bestReactionTime);


#endif