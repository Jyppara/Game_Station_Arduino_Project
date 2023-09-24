// This header file is used to store the functions
// that are used in multiple games. The functions
// are stored in this file to make sure that the
// functions are not duplicated in multiple files.

#ifndef GAME_STATION_H
#define GAME_STATION_H
#include <Arduino.h>
#include <LiquidCrystal.h>

extern LiquidCrystal lcd;
extern const String availableGames[];

void stackTowerGameplay();
void introScreen();
void readButtonPress();
void chooseGame();

#endif