// This header file is used to store the functions
// that are used in multiple games. The functions
// are stored in this file to make sure that the
// functions are not duplicated in multiple files.

#ifndef GAME_STATION_H
#define GAME_STATION_H
#define BUTTON_PIN 2
#define GREEN_LED_PIN 12
#define MELODY_PIN 13
#include <Arduino.h>
#include <LiquidCrystal.h>

extern LiquidCrystal lcd;
extern const String availableGames[];
extern boolean isAsleep;

void printSpecialChar(int yAxis, int xAxis, const byte charToPrint[], int byteIndex);
void stackTowerGameplay();
void introScreen();
void readButtonPress();
void chooseGame();
void printGamePoints(int playersGamePoints, int yAxis);
void printGameOverScreen(int playersGamePoints);
void greenLedOn(int delayTime);
void gameOverMusic();

#endif