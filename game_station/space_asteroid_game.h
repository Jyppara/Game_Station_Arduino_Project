// This header file is used to store the functions
// that are used in the space asteroid game only.

#ifndef SPACE_ASTEROID_GAME_H
#define SPACE_ASTEROID_GAME_H
#define BUTTON_PIN 2

#include <Arduino.h>
#include <LiquidCrystal.h>

extern LiquidCrystal lcd;
extern int spaceshipYLocation;
extern int spaceshipXLocation;
extern int asteroidYLocation;
extern int asteroidXLocation;
extern int dividerIndex;
extern int asteroidSpeed;
extern int playersGamePoints;
extern bool asteroidGameOver;

const byte spaceShipChar[] = {
    B11000,
    B01000,
    B01100,
    B00111,
    B00111,
    B01100,
    B01000,
    B11000};

const byte asteroidChar[] = {
    B00000,
    B01100,
    B01110,
    B11111,
    B11111,
    B01110,
    B00110,
    B00000};
    
void refreshAsteroidLocation();
void checkForCollision();
void spaceAsteroidGameplay();
void resetAsteroidGameVariables();
void checkIfAsteroidPassed(int asteroidXLocation);

#endif