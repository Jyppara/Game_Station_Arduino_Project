#include "game_station.h"
#include "stack_tower_game.h"
#include <LiquidCrystal.h>

bool game_over = false;
int game_points = 0;
int movingTowerXLocation = 6;
int movingTowerYLocation = 1;
bool towerDirectionToRight = true;
bool towerLowerHalfMoving = false;
int index = 1;
int difficulty_delay = 150;

void stackTowerGameplay()
{
    // This function is used to the stack tower gameplay.
    while (digitalRead(2) == HIGH)
    {
        // This while loop is used to make sure that the player
        // has released the button before the game starts.
    }

    printSpecialChar(1, 7, lowerHalfTowerChar, 3);
    delay(200);
    while (!game_over)
    {
        while (digitalRead(2) == LOW)
        {
            lcd.clear();
            printStaticTower();
            printMovingTowerBlock();
        }
        checkIfGameOver();
    }
    printGameOverScreen(game_points);
    resetTowerGameVariables();
}

void printTowerAnimation()
{
    // This function is used to print the tower animation where the tower
    // is moving from top to bottom of the LCD screen.
    delay(300);
    lcd.clear();
    printSpecialChar(0, 7, lowerHalfTowerChar, 3);
    printSpecialChar(1, 7, fullTowerChar, 5);
    printGamePoints(game_points, movingTowerYLocation);
    delay(300);
    lcd.clear();
    printSpecialChar(1, 7, fullTowerChar, 5);
    printGamePoints(game_points, movingTowerYLocation);
    delay(300);
    lcd.clear();
    printSpecialChar(1, 7, lowerHalfTowerChar, 3);
    printGamePoints(game_points, movingTowerYLocation);
    delay(600);
}

void printStaticTower()
{
    // This function is used to print the not moving tower on the LCD screen.
    // It checks the location of the moving block and prints the correct tower.
    if (movingTowerYLocation == 1)
    {
        printSpecialChar(1, 7, lowerHalfTowerChar, 3);
    }
    else if (movingTowerYLocation == 0 && towerLowerHalfMoving)
    {
        printSpecialChar(1, 7, fullTowerChar, 5);
    }
    else if (movingTowerYLocation == 0 && !towerLowerHalfMoving)
    {
        printSpecialChar(1, 7, fullTowerChar, 5);
        printSpecialChar(0, 7, lowerHalfTowerChar, 3);
    }
}

void printMovingTowerBlock()
{
    // This function is used to move the block on the LCD screen.
    // It checks the location of the moving block and changes direction when the block
    // reaches the end of the LCD screen.
    if (towerDirectionToRight)
    {
        // This if statement is used to make sure that the tower is not moving outside of the LCD screen.
        if (movingTowerYLocation == 1)
        {
            printGamePoints(game_points, 0);
        }
        else
        {
            printGamePoints(game_points, 1);
        }
        if (movingTowerXLocation < 15)
        {
            movingTowerXLocation++;
            if (movingTowerXLocation == 7 && !towerLowerHalfMoving)
            {
                printSpecialChar(movingTowerYLocation, movingTowerXLocation, fullTowerChar, 5);
            }
            else
            {
                if (towerLowerHalfMoving && !movingTowerYLocation == 1)
                {
                    printSpecialChar(movingTowerYLocation, movingTowerXLocation, lowerHalfTowerChar, 3);
                }
                else
                {
                    printSpecialChar(movingTowerYLocation, movingTowerXLocation, upperHalfTowerChar, 4);
                }
            }
            delay(difficulty_delay);
        }
        else
        {
            towerDirectionToRight = false;
        }
    }
    else
    {
        // This if statement is used to make sure that the tower is not moving outside of the LCD screen.

        if (movingTowerYLocation == 1)
        {
            printGamePoints(game_points, 0);
        }
        else
        {
            printGamePoints(game_points, 1);
        }
        if (movingTowerXLocation > 0)
        {
            movingTowerXLocation--;
            if (movingTowerXLocation == 7 && !towerLowerHalfMoving)
            {
                printSpecialChar(movingTowerYLocation, movingTowerXLocation, fullTowerChar, 5);
            }
            else
            {
                if (towerLowerHalfMoving && !movingTowerYLocation == 1)
                {
                    printSpecialChar(movingTowerYLocation, movingTowerXLocation, lowerHalfTowerChar, 3);
                }
                else
                {
                    printSpecialChar(movingTowerYLocation, movingTowerXLocation, upperHalfTowerChar, 4);
                }
            }
            delay(difficulty_delay);
        }
        else
        {
            towerDirectionToRight = true;
        }
    }
}

void checkIfGameOver()
{
    // This function is used to check if the player has lost the game.
    // The function is used to check if the moving block is in the correct location
    // and if it is not, the game is over. If the player has not lost the game,
    // the function is used to increase the game points and make the game more difficult.
    if (movingTowerXLocation == 7)
    {
        game_points++;
        index++;
        difficulty_delay -= 4;
        if (movingTowerYLocation == 1)
        {
            towerLowerHalfMoving = true;
        }
        else if (!towerLowerHalfMoving && movingTowerYLocation == 0)
        {
            towerLowerHalfMoving = false;
        }

        else
        {
            towerLowerHalfMoving = !towerLowerHalfMoving;
        }
        if (index == 2 || (index == 1 && movingTowerYLocation == 1))
        {
            movingTowerYLocation = !movingTowerYLocation;
            index = 0;
        }
        movingTowerXLocation = random(0, 16);
        greenLedOn(400);
        if (game_points % 3 == 0)
        {
            printTowerAnimation();
        }
    }
    else
    {
        game_over = true;
        gameOverFlashing();
    }
}

void resetTowerGameVariables()
{
    // This function is used to reset the variables that are used in
    // the stack tower game when the game is over.
    game_over = false;
    game_points = 0;
    index = 1;
    movingTowerXLocation = 6;
    movingTowerYLocation = 1;
    towerLowerHalfMoving = false;
    difficulty_delay = 150;
}

void gameOverFlashing()
{
    // This function is used to flash the components on the LCD screen when the game is over.
    gameOverMusic();
    for (int i = 0; i < 5; i++)
    {
        lcd.clear();
        delay(200);
        if (movingTowerYLocation == 1)
        {
            printSpecialChar(1, 7, lowerHalfTowerChar, 3);
        }
        else if (movingTowerYLocation == 0 && towerLowerHalfMoving)
        {
            printSpecialChar(1, 7, fullTowerChar, 5);
        }
        else if (movingTowerYLocation == 0 && !towerLowerHalfMoving)
        {
            printSpecialChar(1, 7, fullTowerChar, 5);
            printSpecialChar(0, 7, lowerHalfTowerChar, 3);
        }
        if (towerLowerHalfMoving)
        {
            printSpecialChar(movingTowerYLocation, movingTowerXLocation, lowerHalfTowerChar, 3);
        }
        else
        {
            printSpecialChar(movingTowerYLocation, movingTowerXLocation, upperHalfTowerChar, 4);
        }

        printGamePoints(game_points, !movingTowerYLocation);
        delay(200);
    }
}