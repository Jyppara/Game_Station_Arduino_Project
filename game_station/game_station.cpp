#include "game_station.h"
#include "space_asteroid_game.h"

String available_games[] = {"Stack Tower", "Space Asteroid"};
int rehresh_index = 0;
int rehresh_rate = 200;
int game_index = 0;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 200;

void intro_screen()
{
    // This function is used to print the intro screen on the LCD screen
    // and wait for the player to press the button to start the game.
    while (digitalRead(2) == LOW)
    {
        lcd.setCursor(0, 0);
        lcd.print("--GameStation--");
        lcd.setCursor(0, 1);
        lcd.print("Press to start");
    }
    lcd.clear();
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

void choose_game()
{
    // This function is used to print the available games on the LCD screen
    // and wait for the player to choose a game and then starts the game.
    while (digitalRead(2) == HIGH)
    {
        delay(50);
    }
    lcd.clear();
    while (digitalRead(2) == LOW)
    {
        lcd.setCursor(0, 0);
        lcd.print("Choose a game:");
        lcd.setCursor(0, 1);
        lcd.print(String(game_index + 1) + "." + available_games[game_index]);
        if (rehresh_index > rehresh_rate)
        {
            lcd.clear();
            rehresh_index = 0;
            game_index++;
            if (game_index > 1)
            {
                game_index = 0;
            }
        }
        rehresh_index++;
    }
    lcd.clear();
    if (game_index == 0)
    {
        stack_tower_gameplay();
    }
    else if (game_index == 1)
    {
        space_asteroid_gameplay();
    }
    game_index = 0;
    rehresh_index = 0;
}