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

void stackTowerGameplay()
{
    // Print the first half of the tower to the middle of the LCD screen.
    printSpecialChar(1, 7, lowerHalfTowerChar, 3);
    delay(200);
    while (!game_over)
    {
        while (digitalRead(2) == LOW)
        {
            // for debugging purposes
            Serial.print("movingTowerYLocation: ");
            Serial.println(movingTowerYLocation);
            Serial.print("towerLowerHalfMoving: ");
            Serial.println(String(towerLowerHalfMoving));
            Serial.print("index: ");
            Serial.println(String(index));

            lcd.clear();
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
                    delay(150);
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
                    delay(150);
                }
                else
                {
                    towerDirectionToRight = true;
                }
            }
        }

        if (movingTowerXLocation == 7)
        {
            game_points++;
            index++;
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
        }
        else
        {
            game_over = true;
        }
        delay(1000);
    }
    printGameOverScreen(game_points);
    game_over = false;
    game_points = 0;
    index = 1;
    movingTowerXLocation = 6;
    movingTowerYLocation = 1;
    towerLowerHalfMoving = false;
}