// AUTHOR: Jyri Määttä
// DESCRIPTION: GameStation project for Arduino Uno R3 with a 2x16 LCD screen
// and some basic electronic components. GameStation is a gaming device that
// allows the user play different games on a single device. Goals for this
// project is to learn more about programming microcontrollers and getting
// more familiar of using basic electronic components such as LCD, LEDs,
// resistors, potentiometer and piezo.
//
//  Games programmed so far:
//
//    - Space asteroid game
//    - Stack tower game
//    - Reaction game
//
//  Circuit description:
//
// Circuit has one push button which is for navigating through games and
// playing them. Green LED is for blinking every time the player makes
// another point. With the potentiometer the player can dim the LED or turn
// it off completely if he/she wants to do so. Piezo is for making a "Game
// Over" sound whenever the player looses the game. You can view the circuit
// design from the AUTODESK Tinkercad from the following link:
// https://www.tinkercad.com/things/2UjaoKeHYQ5
//

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