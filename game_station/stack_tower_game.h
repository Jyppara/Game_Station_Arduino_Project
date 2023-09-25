#ifndef STACK_TOWER_GAME_H
#define STACK_TOWER_GAME_H
#include <Arduino.h>
#include <LiquidCrystal.h>

const byte lowerHalfTowerChar[] = {
    B00000,
    B00000,
    B00000,
    B00000,
    B11111,
    B11111,
    B11111,
    B11111};

const byte upperHalfTowerChar[] = {
    B11111,
    B11111,
    B11111,
    B11111,
    B00000,
    B00000,
    B00000,
    B00000};

const byte fullTowerChar[] = {
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111};

void stackTowerGameplay();

#endif