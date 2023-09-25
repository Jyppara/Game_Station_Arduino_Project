#include "game_station.h"
#include "space_asteroid_game.h"
#include "stack_tower_game.h"

const String availableGames[] = {"Stack Tower", "Space Asteroid"};
int rehreshIndex = 0;
int rehreshRate = 150;
int gameIndex = 0;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 200;

void printSpecialChar(int yAxis, int xAxis, const byte charToPrint[], int byteIndex)
{
    // This function is used to print a special character on the LCD screen.
    lcd.createChar(byteIndex, charToPrint);
    lcd.setCursor(xAxis, yAxis);
    lcd.write(byte(byteIndex));
}

void printGameOverScreen(int playersGamePoints)
{
    // This function is used to print the game over screen on the LCD screen
    // when the game is over and reset the game variables.
    lcd.clear();
    lcd.setCursor(14, 0);
    lcd.print("Game over! Score:" + String(playersGamePoints));
    lcd.setCursor(14, 1);
    lcd.print("Press to restart");
    while (digitalRead(2) == LOW)
    {
        delay(150);
        lcd.scrollDisplayLeft();
    }
    resetGameVariables();
    // This while loop is used to make sure that the player has released the button
    while (digitalRead(2) == HIGH)
    {
        delay(150);
        lcd.scrollDisplayLeft();
    }
    lcd.clear();
}


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

void printGamePoints(int playersGamePoints, int yAxis)
{
    // This function is used to print the game points on the screen.
    // The function is used to make sure that the game points are always
    // in the proper location on the screen.
    if (playersGamePoints < 10)
    {
        lcd.setCursor(15, yAxis);
    }
    else if (playersGamePoints < 100)
    {
        lcd.setCursor(14, yAxis);
    }
    else
    {
        lcd.setCursor(13, yAxis);
    }
    lcd.print(playersGamePoints);
}