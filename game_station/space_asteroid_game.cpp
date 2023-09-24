#include "space_asteroid_game.h"
#include <LiquidCrystal.h>

#define BUTTON_PIN 2

LiquidCrystal lcd(11, 9, 6, 5, 4, 3); // RS, E, D4, D5, D6, D7
int spaceship_Y_location = 0;
int spaceship_X_location = 0;
int asteroid_Y_location = 1;
int asteroid_X_location = 16;
int divider_index = 0;
int asteroid_speed = 4;
int players_game_points = 0;
int display_row = 0;
bool game_over = false;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 200;

void print_spaceship(int y_axis)
{
    // This function is used to print the spaceship on the LCD screen.
    lcd.createChar(0, space_ship_char);
    lcd.setCursor(0, y_axis);
    lcd.write(byte(0));
}

void print_asteroid(int y_axis, int x_axis)
{
    // This function is used to print the asteroid on the LCD screen.
    lcd.createChar(1, asteroid_char);
    lcd.setCursor(x_axis, y_axis);
    lcd.write(byte(1));
}

void intro_screen()
{
    // This function is used to print the intro screen on the LCD screen
    // and wait for the player to press the button to start the game.
    while (digitalRead(2) == LOW)
    {
        lcd.setCursor(0, 0);
        lcd.print("Welcome to Space");
        lcd.setCursor(0, 1);
        lcd.print("Press to start!");
    }
    lcd.clear();
}

void reset_game_variables()
{
    // This function is used to reset the game variables when the game is over.
    spaceship_Y_location = 0;
    spaceship_X_location = 0;
    asteroid_Y_location = random(0, 2);
    asteroid_X_location = 16;
    divider_index = 0;
    asteroid_speed = 4;
    players_game_points = 0;
    game_over = false;
}

void print_game_over_screen()
{
    // This function is used to print the game over screen on the LCD screen
    // when the game is over and reset the game variables.
    lcd.clear();
    lcd.setCursor(14, 0);
    lcd.print("Game over! Score:" + String(players_game_points));
    lcd.setCursor(14, 1);
    lcd.print("Press to restart");
    while (digitalRead(2) == LOW)
    {
        delay(150);
        lcd.scrollDisplayLeft();
    }
    lcd.clear();
    reset_game_variables();
}

void refresh_asteroid_location()
{
    // This function is used to refresh the asteroid location on the screen.
    // The function is used to make sure that the asteroid is moving at the
    // correct speed and that the asteroid is not moving too fast.
    divider_index++;
    // This variable is used to make sure that the asteroid is moving at the correct speed.
    if (divider_index == asteroid_speed)
    {
        asteroid_X_location--;
        divider_index = 0;
    }
    if (asteroid_X_location < 0)
    {
        asteroid_X_location = 15;           // Asteroid is moved to the right side of the screen.
        asteroid_Y_location = random(0, 2); // Asteroid is moved to a random row.
        // The following if statements are used to make the game more difficult
        // as the player progresses.
        if (players_game_points < 10)
        {
            asteroid_speed = random(3, 4);
        }
        else if (players_game_points < 40)
        {
            asteroid_speed = random(2, 4);
        }
        else if (players_game_points < 100)
        {
            asteroid_speed = random(2, 3);
        }
        else
        {
            asteroid_speed = random(1, 2);
        }
        players_game_points++;
    }
    // The following if statement makes the asteroid move to the other row
    // randomly to make the game more difficult and unpredictable.
    else if (asteroid_X_location == 8 && players_game_points > 5)
    {
        asteroid_Y_location = random(0, 2);
    }
}

void print_game_points()
{
    // This function is used to print the game points on the screen.
    // The function is used to make sure that the game points are always
    // in the proper location on the screen.
    if (players_game_points < 10)
    {
        lcd.setCursor(15, 0);
    }
    else if (players_game_points < 100)
    {
        lcd.setCursor(14, 0);
    }
    else
    {
        lcd.setCursor(13, 0);
    }
    lcd.print(players_game_points);
}

void check_for_collision()
{
    // This function is used to check if the spaceship and the asteroid
    // are in the same location. If they are, the game is over. Finally
    // the function is used to create a blinking effect on the screen
    if (spaceship_Y_location == asteroid_Y_location && spaceship_X_location == asteroid_X_location)
    {
        game_over = true;
        for (int i = 0; i < 5; i++)
        {
            lcd.clear();
            print_spaceship(spaceship_Y_location);
            print_asteroid(asteroid_Y_location, asteroid_X_location);
            if (players_game_points < 10)
            {
                lcd.setCursor(15, 0);
            }
            else if (players_game_points < 100)
            {
                lcd.setCursor(14, 0);
            }
            else
            {
                lcd.setCursor(13, 0);
            }
            lcd.print(players_game_points);
            delay(100);
            lcd.clear();
            delay(100);
        }
    }
}

void read_button_press()
{
    // This function is used to read the button press and make sure that
    // the button press is not registered multiple times in a row.
    if (digitalRead(BUTTON_PIN) == HIGH && millis() - lastDebounceTime > debounceDelay)
    {
        spaceship_Y_location = !spaceship_Y_location;
        lastDebounceTime = millis();
    }
}

void space_asteroid_gameplay()
{
    // This function is used to run the game.
    while (!game_over)
    {
        read_button_press();
        refresh_asteroid_location();
        lcd.clear();
        print_spaceship(spaceship_Y_location);
        print_asteroid(asteroid_Y_location, asteroid_X_location);
        print_game_points();
        check_for_collision();
        delay(50); // This delay is used to manipulate the speed of the game.
    }
    print_game_over_screen();
}