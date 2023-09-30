#include "game_station.h"
#include "memory_game.h"
#include <LiquidCrystal.h>

int potentioMeterIndex = 0;

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
    lcd.print("sequence!");

    while (digitalRead(2) == LOW)
    {
        // Wait for the player to push the button.
    }
    while (digitalRead(2) == HIGH)
    {
        // Wait for the player to release the button.
    }
    lcd.clear();
    while (digitalRead(2) == LOW)
    {
        lcd.clear();
        int potentiometerValue = analogRead(A0);
        potentioMeterIndex = map(potentiometerValue, 0, 1023, 0, 31);
        Serial.println(potentioMeterIndex);
        if (potentioMeterIndex < 16)
        {
            printSpecialChar(0, potentioMeterIndex, cardChar, 6);
        }
        else
        {
            printSpecialChar(1, potentioMeterIndex - 16, cardChar, 6);
        }
        
        delay(50);
    }
    while (digitalRead(2) == HIGH)
    {
        // Wait for the player to release the button.
    }
}