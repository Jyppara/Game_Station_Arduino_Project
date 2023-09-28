#include "game_station.h"
#include "space_asteroid_game.h"
#include "stack_tower_game.h"
#include "reaction_game.h"
#define NOTE_GS3 208
#define NOTE_A3 220
#define NOTE_AS3 233
#define NOTE_B3 247
#define NOTE_DS4 311
#define NOTE_GS4 415

// This file includes the implementation of the functions
// that are used in multiple games.

const String availableGames[] = {"Stack Tower", "Space Asteroid", "Reaction Speed"};
int rehreshIndex = 0;
int rehreshRate = 150;
int gameIndex = 0;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 200;
int gameOverMelody[] = {
    NOTE_GS4, NOTE_DS4, NOTE_B3,
    NOTE_AS3, NOTE_A3, NOTE_GS3};
int gameOverTempo[] = {
    10, 10, 10,
    10, 10, 10};

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
    resetAsteroidGameVariables();
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
            if (gameIndex > 2)
            {
                gameIndex = 0;
            }
        }
        rehreshIndex++;
    }
    if (gameIndex == 0)
    {
        stackTowerGameplay();
    }
    else if (gameIndex == 1)
    {
        spaceAsteroidGameplay();
    }
    else if (gameIndex == 2)
    {
        reactionGamePlay();
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

void greenLedOn(int delayTime)
{
    // This function is used to make the green LED blink when the player
    // has pressed the button.
    digitalWrite(GREEN_LED_PIN, HIGH);
    delay(delayTime);
    digitalWrite(GREEN_LED_PIN, LOW);
}

void gameOverMusic()
{
    // This function is used to play the game over melody when the game is over.
    delay(300);
    for (int i = 0; i < sizeof(gameOverMelody) / sizeof(gameOverMelody[0]); i++)
    {
        int noteDuration = 2000 / gameOverTempo[i];
        tone(MELODY_PIN, gameOverMelody[i], noteDuration);
        delay(noteDuration + 20);
        noTone(MELODY_PIN);
    }
}