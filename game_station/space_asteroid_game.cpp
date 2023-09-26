#include "space_asteroid_game.h"
#include "game_station.h"
#include <LiquidCrystal.h>

#define BUTTON_PIN 2

LiquidCrystal lcd(11, 9, 6, 5, 4, 3); // RS, E, D4, D5, D6, D7
int spaceshipYLocation = 0;
int spaceshipXLocation = 0;
int asteroidYLocation = 1;
int asteroidXLocation = 16;
int dividerIndex = 0;
int asteroidSpeed = 4;
int playersGamePoints = 0;
bool gameOver = false;

void resetAsteroidGameVariables()
{
    // This function is used to reset the game variables when the game is over.
    spaceshipYLocation = 0;
    spaceshipXLocation = 0;
    asteroidYLocation = random(0, 2);
    asteroidXLocation = 16;
    dividerIndex = 0;
    asteroidSpeed = 4;
    playersGamePoints = 0;
    gameOver = false;
}

void refreshAsteroidLocation()
{
    // This function is used to refresh the asteroid location on the screen.
    // The function is used to make sure that the asteroid is moving at the
    // correct speed and that the asteroid is not moving too fast.
    dividerIndex++;
    // This variable is used to make sure that the asteroid is moving at the correct speed.
    if (dividerIndex == asteroidSpeed)
    {
        asteroidXLocation--;
        dividerIndex = 0;
    }
    if (asteroidXLocation < 0)
    {
        asteroidXLocation = 15;           // Asteroid is moved to the right side of the screen.
        asteroidYLocation = random(0, 2); // Asteroid is moved to a random row.
        // The following if statements are used to make the game more difficult
        // as the player progresses.
        if (playersGamePoints < 10)
        {
            asteroidSpeed = random(3, 4);
        }
        else if (playersGamePoints < 40)
        {
            asteroidSpeed = random(2, 4);
        }
        else if (playersGamePoints < 100)
        {
            asteroidSpeed = random(2, 3);
        }
        else
        {
            asteroidSpeed = random(1, 2);
        }
        playersGamePoints++;
    }
    // The following if statement makes the asteroid move to the other row
    // randomly to make the game more difficult and unpredictable.
    else if (asteroidXLocation == 8 && playersGamePoints > 5)
    {
        asteroidYLocation = random(0, 2);
    }
}

void checkForCollision()
{
    // This function is used to check if the spaceship and the asteroid
    // are in the same location. If they are, the game is over. Finally
    // the function is used to create a blinking effect on the screen
    if (spaceshipYLocation == asteroidYLocation && spaceshipXLocation == asteroidXLocation)
    {
        gameOver = true;
        for (int i = 0; i < 5; i++)
        {
            lcd.clear();
            printSpecialChar(spaceshipYLocation, spaceshipXLocation, spaceShipChar, 0);
            printSpecialChar(asteroidYLocation, asteroidXLocation, asteroidChar, 1);
            if (playersGamePoints < 10)
            {
                lcd.setCursor(15, 0);
            }
            else if (playersGamePoints < 100)
            {
                lcd.setCursor(14, 0);
            }
            else
            {
                lcd.setCursor(13, 0);
            }
            lcd.print(playersGamePoints);
            delay(100);
            lcd.clear();
            delay(100);
        }
    }
}

void spaceAsteroidGameplay()
{
    // This function is used to run the game.
    while (!gameOver)
    {
        readButtonPress();
        refreshAsteroidLocation();
        lcd.clear();
        printSpecialChar(spaceshipYLocation, spaceshipXLocation, spaceShipChar, 0);
        printSpecialChar(asteroidYLocation, asteroidXLocation, asteroidChar, 1);
        printGamePoints(playersGamePoints, 0);
        checkForCollision();
        delay(50); // This delay is used to manipulate the speed of the game.
    }
    printGameOverScreen(playersGamePoints);
}