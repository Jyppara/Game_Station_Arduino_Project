#include "game_station.h"
#include "memory_game.h"
#include <LiquidCrystal.h>

void memoryGameplay()
{
    // This function is used to the memory gameplay.
    while (digitalRead(2) == HIGH)
    {
        // This while loop is used to make sure that the player
        // has released the button before the game starts.
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Memorize the");
    lcd.setCursor(0, 1);
    lcd.print("cards!");

    while (digitalRead(2) == LOW)
    {
        // Wait for the player to push the button.
    }
    while (digitalRead(2) == HIGH)
    {
        // Wait for the player to release the button.
    }
    lcd.clear();
    startAnimation(8, mapPotentiometerValue(8));
    while (digitalRead(2) == LOW)
    {
        printAllCards(8, mapPotentiometerValue(8));
        delay(50);
    }
    while (digitalRead(2) == HIGH)
    {
        // Wait for the player to release the button.
    }
}

int mapPotentiometerValue(int numberOfCards)
{
    // This function is used to read the potentiometer value and print the corresponding card on the screen.
    int potentiometerValue = analogRead(A0);
    int potentioMeterIndex = map(potentiometerValue, 0, 1023, 0, numberOfCards - 1);
    Serial.println(potentioMeterIndex); // for debugging
    return potentioMeterIndex;
}

void printAllCards(int numberOfCards, int potentioMeterIndex)
{
    // This function is used to print all the cards on the screen.
    int indent = (16 - (numberOfCards / 2)) / 2;
    for (int i = 0; i < numberOfCards; i++)
    {
        if (i < (numberOfCards / 2))
        {
            if(i == potentioMeterIndex)
            {
                printSpecialChar(0, indent + i, selectedCardChar, 1);
            }
            else
            {
                printSpecialChar(0, indent + i, cardChar, 0);
            }
        }
        else
        {
            if(i == potentioMeterIndex)
            {
                printSpecialChar(1, indent + i - (numberOfCards / 2), selectedCardChar, 1);
            }
            else
            {
                printSpecialChar(1, indent + i - (numberOfCards / 2), cardChar, 0);
            }
        }
    }
}

void startAnimation(int numberOfCards, int potentioMeterIndex)
{
    // This function is used to print all the cards on the screen.
    int indent = (16 - (numberOfCards / 2)) / 2;
    for (int i = 0; i < numberOfCards; i++)
    {
        if (i < (numberOfCards / 2))
        {
            if(i == potentioMeterIndex)
            {
                printSpecialChar(0, indent + i, selectedCardChar, 1);
            }
            else
            {
                printSpecialChar(0, indent + i, cardChar, 0);
            }
        }
        else
        {
            if(i == potentioMeterIndex)
            {
                printSpecialChar(1, indent + i - (numberOfCards / 2), selectedCardChar, 1);
            }
            else
            {
                printSpecialChar(1, indent + i - (numberOfCards / 2), cardChar, 0);
            }
        }

        delay(200);
    }
}