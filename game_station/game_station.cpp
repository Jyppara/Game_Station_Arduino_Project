#include "game_station.h"
#include "space_asteroid_game.h"
#include "stack_tower_game.h"
#include "reaction_game.h"
#include "memory_game.h"
#include <avr/sleep.h>
#define NOTE_GS3 208
#define NOTE_A3 220
#define NOTE_AS3 233
#define NOTE_B3 247
#define NOTE_DS4 311
#define NOTE_GS4 415

// This file includes the implementation of the functions
// that are used in multiple games.

const String availableGames[] = {
    "1.Memory Game",
    "2.Stack Tower",
    "3.Space Asteroid",
    "4.Reaction Speed",
};
const int numberOfGames = sizeof(availableGames) / sizeof(availableGames[0]);
int rehreshIndex = 0;
int rehreshRate = 150;
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
    lcd.print("Press to go back");
    while (digitalRead(BUTTON_PIN) == LOW)
    {
        delay(150);
        lcd.scrollDisplayLeft();
    }
    resetAsteroidGameVariables();
    // This while loop is used to make sure that the player has released the button
    while (digitalRead(BUTTON_PIN) == HIGH)
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
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("--GameStation--");
    lcd.setCursor(0, 1);
    lcd.print("Press to start");
    while (digitalRead(BUTTON_PIN) == LOW)
        ;
    while (digitalRead(BUTTON_PIN) == HIGH)
        ;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Use the knob");
    lcd.setCursor(0, 1);
    lcd.print("to browse games");
    while (digitalRead(BUTTON_PIN) == LOW)
        ;
    while (digitalRead(BUTTON_PIN) == HIGH)
        ;
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
    while (digitalRead(BUTTON_PIN) == HIGH)
    {
        // This while loop is used to make sure that the player
        // has released the button before the game starts.
    }
    int potentiometerIndex = mapPotentiometerValue(numberOfGames);
    while (digitalRead(BUTTON_PIN) == LOW)
    {
        potentiometerIndex = mapPotentiometerValue(numberOfGames);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Choose a game:");
        lcd.setCursor(0, 1);
        lcd.print(availableGames[potentiometerIndex]);
        int compareIndex = mapPotentiometerValue(numberOfGames);
        while (compareIndex == potentiometerIndex && digitalRead(BUTTON_PIN) == LOW)
        {
            // This while loop is used to make sure that the screen
            // is refreshed only when the potentiometer value has changed.
            compareIndex = mapPotentiometerValue(numberOfGames);
        }
        delay(50);
    }
    while (digitalRead(BUTTON_PIN) == HIGH)
    {
        // This while loop is used to make sure that the player
        // has released the button before the game starts.
    }
    switch (potentiometerIndex)
    {
    case 0:
        memoryGameplay();
        break;
    case 1:
        stackTowerGameplay();
        break;
    case 2:
        spaceAsteroidGameplay();
        break;
    case 3:
        reactionGamePlay();
        break;
    }
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
    // This function is used to make the green LED stay on
    // for a given amount of time and then turn off.
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

int mapPotentiometerValue(int index)
{
    // This function is used to read the potentiometer value
    // and map it to the number of cards.
    int potentiometerValue = analogRead(A0);
    int potentioMeterIndex = map(potentiometerValue, 0, 1022, 0, index - 1);
    return potentioMeterIndex;
}