#include "game_station.h"
#include <LiquidCrystal.h>

void stackTowerGameplay()
{
    // print game name to test'
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Stack Tower");
    lcd.setCursor(0, 1);
    lcd.print("Gameplay");
    delay(200);
    while (digitalRead(2) == LOW)
    {
        delay(150);
    }
    // This while loop is used to make sure that the player has released the button
    while (digitalRead(2) == HIGH)
    {
        delay(50);
    }
    lcd.clear();
}