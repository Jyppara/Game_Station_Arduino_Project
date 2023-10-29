#ifndef TEMPERATURE_GAME_H
#define TEMPERATURE_GAME_H
#include <Arduino.h>
#include <LiquidCrystal.h>

int readTemperature();
void temperatureIntroScreen();
int mapPotentiometerTemperature(float minIndex, float maxIndex);
void temperatureGameplay();
#endif