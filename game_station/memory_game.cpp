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
unsigned long memoryGameStartTime;

void memoryGameplay()
{
    // This function is used to the memory gameplay.
    while (digitalRead(BUTTON_PIN) == HIGH)
    {
        // This while loop is used to make sure that the player
        // has released the button before the game starts.
    }
    detachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN));
    attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), memoryGameInterruptHandler, RISING);
    memoryGameIntroScreen();
    shuffleCards();
    lcd.clear();
    startAnimation(numberOfCards, mapPotentiometerValue(numberOfCards));
    memoryGameStartTime = millis();
    while (!memoryGameOver)
    {
        // This while loop is used to play the memory game.
        while (digitalRead(BUTTON_PIN) == LOW || cards[mapPotentiometerValue(numberOfCards)] == "Removed")
        {
            // Waiting for the player to choose the first card.
            printAllCards(numberOfCards, mapPotentiometerValue(numberOfCards));
            delay(50);
        }
        while (digitalRead(BUTTON_PIN) == HIGH)
        {
            // Wait for the player to release the button.
        }
        int firstSelectedCardIndex = mapPotentiometerValue(numberOfCards);
        revealCards(numberOfCards, firstSelectedCardIndex, mapPotentiometerValue(numberOfCards));
        delay(1000);
        while (digitalRead(BUTTON_PIN) == LOW || firstSelectedCardIndex == mapPotentiometerValue(numberOfCards) || cards[mapPotentiometerValue(numberOfCards)] == "Removed")
        {
            // Waiting for the player to choose the second card.
            revealCards(numberOfCards, firstSelectedCardIndex, mapPotentiometerValue(numberOfCards));
            delay(50);
        }
        while (digitalRead(BUTTON_PIN) == HIGH)
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

void memoryGameInterruptHandler()
{
    // This function is used to handle the interrupt that is used
    // to pause the game.
    noInterrupts();
    unsigned long interruptStartTime = millis();
    while (digitalRead(INTERRUPT_PIN) == HIGH)
        ;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Game paused!");
    lcd.setCursor(0, 1);
    lcd.print("Press to go back");
    while (digitalRead(BUTTON_PIN) == LOW)
    {
        // Wait for the player to push the button.
    }
    while (digitalRead(BUTTON_PIN) == HIGH)
    {
        // Wait for the player to release the button.
    }
    lcd.clear();
    unsigned long interruptEndTime = millis();
    // Reduce the interrupt time from the game time
    // to make sure that the game time is not affected by the interrupt.
    unsigned long interruptTime = (interruptEndTime - interruptStartTime) / 1000;
    memoryGameStartTime -= interruptTime;
    interrupts();
}

void memoryGameIntroScreen()
{
    // This function is used to print the memory game intro screen
    // and instructions on the LCD screen.
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Memorize the");
    lcd.setCursor(0, 1);
    lcd.print("cards' order!");
    while (digitalRead(BUTTON_PIN) == LOW)
    {
        // Wait for the player to push the button.
    }
    while (digitalRead(BUTTON_PIN) == HIGH)
    {
        // Wait for the player to release the button.
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Use the knob");
    lcd.setCursor(0, 1);
    lcd.print("to select cards!");
    while (digitalRead(BUTTON_PIN) == LOW)
    {
        // Wait for the player to push the button.
    }
    while (digitalRead(BUTTON_PIN) == HIGH)
    {
        // Wait for the player to release the button.
    }
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
    while (digitalRead(BUTTON_PIN) == LOW)
    {
        greenLedOn(50);
    }
    while (digitalRead(BUTTON_PIN) == HIGH)
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
                        printSpecialChar(0, indent + i, selectedCardChar, 7);
                    }
                }
                else
                {
                    printSpecialChar(0, indent + i, cardChar, 6);
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
                        printSpecialChar(1, indent + i - (numberOfCards / 2), selectedCardChar, 7);
                    }
                }
                else
                {
                    printSpecialChar(1, indent + i - (numberOfCards / 2), cardChar, 6);
                }
            }
        }
    }
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
                    printSpecialChar(0, indent + i, selectedCardChar, 7);
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
                    printSpecialChar(0, indent + i, cardChar, 6);
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
                    printSpecialChar(1, indent + i - (numberOfCards / 2), selectedCardChar, 7);
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
                    printSpecialChar(1, indent + i - (numberOfCards / 2), cardChar, 6);
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
                printSpecialChar(0, indent + i, selectedCardChar, 7);
            }
            else
            {
                printSpecialChar(0, indent + i, cardChar, 6);
            }
        }
        else
        {
            if (i == potentioMeterIndex)
            {
                printSpecialChar(1, indent + i - (numberOfCards / 2), selectedCardChar, 7);
            }
            else
            {
                printSpecialChar(1, indent + i - (numberOfCards / 2), cardChar, 6);
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
    secondCardSelected = false;
    detachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN));
    for (int i = 0; i < numberOfCards; i++)
    {
        cards[i] = cardValues[i];
    }
}