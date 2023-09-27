// AUTHOR: Jyri Määttä
// DESCRIPTION: Game station project for Arduino Uno.
// Goals for this project is to create a gaming station that can be used to play
// different games. The first game that will be created is a space game where the
// player will have to avoid asteroids by moving the spaceship up and down.

#include <LiquidCrystal.h>
#include <Arduino.h>
#include "space_asteroid_game.h"
#include "game_station.h"
#include "stack_tower_game.h"

void setup()
{
  lcd.begin(16, 2);
  pinMode(BUTTON_PIN, INPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(MELODY_PIN, OUTPUT);
  introScreen();
  Serial.begin(9600);
}

void loop()
{
  chooseGame();
}