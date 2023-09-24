#include "game_station.h"
#include "space_asteroid_game.h"

const String availableGames[] = {"Stack Tower", "Space Asteroid"};
int rehreshIndex = 0;
int rehreshRate = 200;
int gameIndex = 0;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 200;

void introScreen()
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

void readButtonPress()
{
    // This function is used to read the button press and make sure that
    // the button press is not registered multiple times in a row.
    if (digitalRead(BUTTON_PIN) == HIGH && millis() - lastDebounceTime > debounceDelay)
    {
        spaceshipYLocation = !spaceshipYLocation;
        lastDebounceTime = millis();
    }
}

void chooseGame()
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
        lcd.print(String(gameIndex + 1) + "." + availableGames[gameIndex]);
        if (rehreshIndex > rehreshRate)
        {
            lcd.clear();
            rehreshIndex = 0;
            gameIndex++;
            if (gameIndex > 1)
            {
                gameIndex = 0;
            }
        }
        rehreshIndex++;
    }
    lcd.clear();
    if (gameIndex == 0)
    {
        stackTowerGameplay();
    }
    else if (gameIndex == 1)
    {
        spaceAsteroidGameplay();
    }
    gameIndex = 0;
    rehreshIndex = 0;
}