#include "game_station.h"
#include "memory_game.h"
#include <LiquidCrystal.h>

// This file includes the implementation of the functions
// that are used in the MEMORY game only.

bool memoryGameOver = false;
bool secondCardSelected = false;
String cards[] = {"*", "*", "!", "!", "#", "#", "$", "$", "%", "%"};
String cardValues[] = {"*", "*", "!", "!", "#", "#", "$", "$", "%", "%"};
int numberOfCards = sizeof(cards) / sizeof(cards[0]);

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
    shuffleCards();
    while (digitalRead(2) == LOW)
    {
        // Wait for the player to push the button.
    }
    while (digitalRead(2) == HIGH)
    {
        // Wait for the player to release the button.
    }
    lcd.clear();
    startAnimation(numberOfCards, mapPotentiometerValue(numberOfCards));
    unsigned long memoryGameStartTime = millis();
    while (!memoryGameOver)
    {
        // This while loop is used to play the memory game.
        while (digitalRead(2) == LOW)
        {
            // Waiting for the player to choose the first card.
            printAllCards(numberOfCards, mapPotentiometerValue(numberOfCards));
            delay(50);
        }
        while (digitalRead(2) == HIGH)
        {
            // Wait for the player to release the button.
        }
        int firstSelectedCardIndex = mapPotentiometerValue(numberOfCards);
        revealCards(numberOfCards, firstSelectedCardIndex, mapPotentiometerValue(numberOfCards));
        delay(1000);
        while (digitalRead(2) == LOW || firstSelectedCardIndex == mapPotentiometerValue(numberOfCards))
        {
            // Waiting for the player to choose the second card.
            revealCards(numberOfCards, firstSelectedCardIndex, mapPotentiometerValue(numberOfCards));
            delay(50);
        }
        while (digitalRead(2) == HIGH)
        {
            // Wait for the player to release the button.
        }
        int secondSelectedCardIndex = mapPotentiometerValue(numberOfCards);
        secondCardSelected = true;
        revealCards(numberOfCards, secondSelectedCardIndex, firstSelectedCardIndex);
        if (checkIfCardsMatch(firstSelectedCardIndex, secondSelectedCardIndex))
        {
            // If the cards match they are removed from the screen.
            cards[firstSelectedCardIndex] = "Removed";
            cards[secondSelectedCardIndex] = "Removed";
            greenLedOn(1000);
        }
        else
        {
            delay(1000);
        }
        secondCardSelected = false;
        memoryGameOver = checkIfAllCardsAreRemoved();
    }
    unsigned long memoryGameEndTime = millis();
    int memoryGameTime = (memoryGameEndTime - memoryGameStartTime) / 1000;
    memoryGameEndScreen(memoryGameTime);
    resetMemoryGameVariables();
}

void shuffleCards()
{
    // Shuffle the cards array to have a random order of cards every time the game is played.
    for (int i = numberOfCards - 1; i > 0; i--)
    {
        int j = random(0, i + 1);
        String temp = cards[i];
        cards[i] = cards[j];
        cards[j] = temp;
    }
}

void memoryGameEndScreen(int memoryGameTime)
{
    // This function is used to print the memory game ending screen
    // and the finishing time.
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("You made it!");
    lcd.setCursor(0, 1);
    lcd.print("Your time: " + String(memoryGameTime) + "s");
    while (digitalRead(2) == LOW)
    {
        greenLedOn(50);
    }
    while (digitalRead(2) == HIGH)
    {
        greenLedOn(50);
    }
}

bool checkIfAllCardsAreRemoved()
{
    // This function is used to check if all the cards are removed.
    for (int i = 0; i < numberOfCards; i++)
    {
        if (cards[i] != "Removed")
        {
            return false;
        }
    }
    return true;
}

bool checkIfCardsMatch(int firstSelectedCardIndex, int secondSelectedCardIndex)
{
    // This function is used to check if the two selected cards match.
    // Also checks if the same card is selected twice.
    if (firstSelectedCardIndex == secondSelectedCardIndex)
    {
        return false;
    }
    else if (cards[firstSelectedCardIndex] == cards[secondSelectedCardIndex])
    {
        return true;
    }
    else
    {
        return false;
    }
}

void revealCards(int numberOfCards, int flippedCard, int potentioMeterIndex)
{
    // This function is used to show the flipped card(s) on the screen
    // and hide the other cards.
    int indent = (16 - (numberOfCards / 2)) / 2;
    for (int i = 0; i < numberOfCards; i++)
    {
        if (i < (numberOfCards / 2))
        {
            if (i == flippedCard)
            {
                if (cards[i] == "Removed")
                {
                    lcd.setCursor(indent + i, 0);
                    lcd.print(" ");
                }
                else
                {
                    lcd.setCursor(indent + i, 0);
                    lcd.print(cards[i]);
                }
            }
            else
            {
                if (cards[i] == "Removed")
                {
                    lcd.setCursor(indent + i, 0);
                    lcd.print(" ");
                }
                else if (i == potentioMeterIndex)
                {
                    if (secondCardSelected)
                    {
                        lcd.setCursor(indent + i, 0);
                        lcd.print(cards[i]);
                    }
                    else
                    {
                        printSpecialChar(0, indent + i, selectedCardChar, 1);
                    }
                }
                else
                {
                    printSpecialChar(0, indent + i, cardChar, 0);
                }
            }
        }
        else
        {
            if (i == flippedCard)
            {
                if (cards[i] == "Removed")
                {
                    lcd.setCursor(indent + i - (numberOfCards / 2), 1);
                    lcd.print(" ");
                }
                else
                {
                    lcd.setCursor(indent + i - (numberOfCards / 2), 1);
                    lcd.print(cards[i]);
                }
            }
            else
            {
                if (cards[i] == "Removed")
                {
                    lcd.setCursor(indent + i - (numberOfCards / 2), 1);
                    lcd.print(" ");
                }
                else if (i == potentioMeterIndex)
                {
                    if (secondCardSelected)
                    {
                        lcd.setCursor(indent + i - (numberOfCards / 2), 1);
                        lcd.print(cards[i]);
                    }
                    else
                    {
                        printSpecialChar(1, indent + i - (numberOfCards / 2), selectedCardChar, 1);
                    }
                }
                else
                {
                    printSpecialChar(1, indent + i - (numberOfCards / 2), cardChar, 0);
                }
            }
        }
    }
}

int mapPotentiometerValue(int numberOfCards)
{
    // This function is used to read the potentiometer value
    // and map it to the number of cards.
    int potentiometerValue = analogRead(A0);
    int potentioMeterIndex = map(potentiometerValue, 0, 1023, 0, numberOfCards - 1);
    return potentioMeterIndex;
}
void printAllCards(int numberOfCards, int potentioMeterIndex)
{
    // This function is used to print all the cards on the screen upside down.
    int indent = (16 - (numberOfCards / 2)) / 2;
    for (int i = 0; i < numberOfCards; i++)
    {
        if (i < (numberOfCards / 2))
        {
            if (i == potentioMeterIndex)
            {
                if (cards[i] == "Removed")
                {
                    lcd.setCursor(indent + i, 0);
                    lcd.print(" ");
                }
                else
                {
                    printSpecialChar(0, indent + i, selectedCardChar, 1);
                }
            }
            else
            {
                if (cards[i] == "Removed")
                {
                    lcd.setCursor(indent + i, 0);
                    lcd.print(" ");
                }
                else
                {
                    printSpecialChar(0, indent + i, cardChar, 0);
                }
            }
        }
        else
        {
            if (i == potentioMeterIndex)
            {
                if (cards[i] == "Removed")
                {
                    lcd.setCursor(indent + i - (numberOfCards / 2), 1);
                    lcd.print(" ");
                }
                else
                {
                    printSpecialChar(1, indent + i - (numberOfCards / 2), selectedCardChar, 1);
                }
            }
            else
            {
                if (cards[i] == "Removed")
                {
                    lcd.setCursor(indent + i - (numberOfCards / 2), 1);
                    lcd.print(" ");
                }
                else
                {
                    printSpecialChar(1, indent + i - (numberOfCards / 2), cardChar, 0);
                }
            }
        }
    }
}

void startAnimation(int numberOfCards, int potentioMeterIndex)
{
    // This function is used to print all the cards on the screen with animation.
    int indent = (16 - (numberOfCards / 2)) / 2;
    for (int i = 0; i < numberOfCards; i++)
    {
        if (i < (numberOfCards / 2))
        {
            if (i == potentioMeterIndex)
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
            if (i == potentioMeterIndex)
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

void resetMemoryGameVariables()
{
    // This function is used to reset the memory game variables
    // to their default values.
    memoryGameOver = false;
    for (int i = 0; i < numberOfCards; i++)
    {
        cards[i] = cardValues[i];
    }
}