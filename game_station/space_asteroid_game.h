#ifndef SPACE_ASTEROID_GAME_H
#define SPACE_ASTEROID_GAME_H
#define BUTTON_PIN 2

#include <Arduino.h>
#include <LiquidCrystal.h>

extern LiquidCrystal lcd;
extern int spaceship_Y_location;
extern int spaceship_X_location;
extern int asteroid_Y_location;
extern int asteroid_X_location;
extern int divider_index;
extern int asteroid_speed;
extern int players_game_points;
extern bool game_over;
extern unsigned long lastDebounceTime;
extern unsigned long debounceDelay;

static byte space_ship_char[] = {
    B11000,
    B01000,
    B01100,
    B00111,
    B00111,
    B01100,
    B01000,
    B11000};

static byte asteroid_char[] = {
    B00000,
    B01100,
    B01110,
    B11111,
    B11111,
    B01110,
    B00110,
    B00000};

void print_spaceship(int y_axis);
void print_asteroid(int y_axis, int x_axis);
void intro_screen();
void print_game_over_screen();
void refresh_asteroid_location();
void print_game_points();
void check_for_collision();
void read_button_press();
void space_asteroid_gameplay();
void reset_game_variables();

#endif