#include "game_station.h"
#include "reaction_game.h"

// This file includes the implementation of the functions
// that are used in the REACTION game only.

void reactionGamePlay()
{
    // This function is used to play the reaction game.
    // The player has to press the button when the LED lights up.
    // The player's reaction time is then displayed on the screen.
    // In the end the player's average reaction time and best reaction time
    // are displayed on the screen.
    while (digitalRead(BUTTON_PIN) == HIGH)
    {
        // This while loop is used to make sure that the player
        // has released the button before the game starts.
    }
    detachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN));
    attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), reactionInterruptHandler, RISING);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Hit the button");
    lcd.setCursor(0, 1);
    lcd.print("when LED lits!");
    unsigned long firstTry;
    unsigned long secondTry;
    unsigned long thirdTry;
    unsigned long averageReactionTime;
    unsigned long bestReactionTime;
    firstTry = oneCycle("Be fast!");        // First round
    secondTry = oneCycle("Be faster!");     // Second round
    thirdTry = oneCycle("Be the fastest!"); // Third round
    while (digitalRead(BUTTON_PIN) == HIGH)
    {
        // Wait for the player to release the button.
    }
    while (digitalRead(BUTTON_PIN) == LOW)
    {
        // Wait for the player to push the button.
    }
    while (digitalRead(BUTTON_PIN) == HIGH)
    {
        // Wait for the player to release the button.
    }
    detachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN));
    calculateScores(firstTry, secondTry, thirdTry, averageReactionTime, bestReactionTime);
    printScores(averageReactionTime, bestReactionTime);
}

void reactionInterruptHandler(){
    // This function is used to handle the interrupt that is used
    // to pause the gameplay.
    while (digitalRead(INTERRUPT_PIN) == HIGH)
        ;
    noInterrupts();
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
    interrupts();
}

void calculateScores(unsigned long firstTry, unsigned long secondTry, unsigned long thirdTry, unsigned long &averageReactionTime, unsigned long &bestReactionTime)
{
    // This function is used to calculate the average reaction time and best reaction time.
    averageReactionTime = (firstTry + secondTry + thirdTry) / 3;
    if (firstTry < secondTry && firstTry < thirdTry)
    {
        bestReactionTime = firstTry;
    }
    else if (secondTry < firstTry && secondTry < thirdTry)
    {
        bestReactionTime = secondTry;
    }
    else
    {
        bestReactionTime = thirdTry;
    }
}

void printScores(unsigned long averageReactionTime, unsigned long bestReactionTime)
{
    // This function is used to print the average reaction time and best reaction time on the screen.
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Your avg time");
    lcd.setCursor(0, 1);

    if (averageReactionTime < 1000)
    {
        lcd.print("was 0," + String(averageReactionTime) + "s");
    }
    else if (averageReactionTime < 10000)
    {
        lcd.print("was " + String(averageReactionTime).substring(0, 1) + "," + String(averageReactionTime).substring(1) + "s");
    }
    else
    {
        lcd.print("was " + String(averageReactionTime).substring(0, 2) + "," + String(averageReactionTime).substring(2) + "s");
    }
    while (digitalRead(BUTTON_PIN) == LOW)
    {
        // Wait for the player to press the button.
    }
    while (digitalRead(BUTTON_PIN) == HIGH)
    {
        // Wait for the player to release the button.
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Your best time");
    lcd.setCursor(0, 1);

    if (bestReactionTime < 1000)
    {
        lcd.print("was 0," + String(bestReactionTime) + "s");
    }
    else if (bestReactionTime < 10000)
    {
        lcd.print("was " + String(bestReactionTime).substring(0, 1) + "," + String(bestReactionTime).substring(1) + "s");
    }
    else
    {
        lcd.print("was " + String(bestReactionTime).substring(0, 2) + "," + String(bestReactionTime).substring(2) + "s");
    }
    while (digitalRead(BUTTON_PIN) == LOW)
    {
        // Wait for the player to press the button.
    }
    while (digitalRead(BUTTON_PIN) == HIGH)
    {
        // Wait for the player to release the button.
    }
}

void randomDelay(int lowerBound, int upperBound)
{
    // This function is used to create a random delay.
    int randomDelay = random(lowerBound, upperBound);
    delay(randomDelay);
}

unsigned long oneCycle(String waitingMessage)
{
    // This function is used to run one cycle of the reaction game.
    while (digitalRead(BUTTON_PIN) == LOW)
    {
        // Wait for the player to press the button.
    }
    while (digitalRead(BUTTON_PIN) == HIGH)
    {
        // Wait for the player to release the button.
    }
    lcd.clear();
    // Set the message in the middle of the screen.
    int sizeOfMessage = waitingMessage.length();
    int spaces = (16 - sizeOfMessage) / 2;
    lcd.setCursor(spaces, 0);
    lcd.print(waitingMessage);
    lcd.setCursor(13, 1);
    lcd.print("-->");
    randomDelay(2000, 7000);
    digitalWrite(GREEN_LED_PIN, HIGH);
    unsigned long startTime = millis();
    while (digitalRead(BUTTON_PIN) == LOW)
    {
        // Wait for the player to press the button.
    }
    unsigned long endTime = millis();
    unsigned long reactionTime = endTime - startTime;
    digitalWrite(GREEN_LED_PIN, LOW);
    while (digitalRead(BUTTON_PIN) == HIGH)
    {
        // Wait for the player to release the button.
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Your reaction");
    if (reactionTime < 1000)
    {
        lcd.setCursor(0, 1);
        lcd.print("time was 0," + String(reactionTime) + "s");
    }
    else if (reactionTime < 10000)
    {
        lcd.setCursor(0, 1);
        lcd.print("time was " + String(reactionTime).substring(0, 1) + "," + String(reactionTime).substring(1) + "s");
    }
    else
    {
        lcd.setCursor(0, 1);
        lcd.print("time was " + String(reactionTime).substring(0, 2) + "," + String(reactionTime).substring(2) + "s");
    }

    return reactionTime;
}