// This header file is used to store the functions
// that are used in multiple games. The functions
// are stored in this file to make sure that the
// functions are not duplicated in multiple files.

#ifndef GAME_STATION_H
#define GAME_STATION_H
#include <Arduino.h>
#include <LiquidCrystal.h>

extern LiquidCrystal lcd;
extern String available_games[];

void stack_tower_gameplay();
void intro_screen();
void read_button_press();
void choose_game();

#endif