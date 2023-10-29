#include "game_station.h"
#include "temperature_game.h"

int readTemperature()
{
    // This function is used to read the temperature from the
    // temperature sensor.
    int sensorValue = analogRead(TEMPERATURE_PIN);
    float voltage = sensorValue * (5.0 / 1023.0);
    float temperature = (voltage - 0.5) * 100;
    return temperature;
}

void temperatureIntroScreen()
{
    // This function is used to print the intro screen of the temperature game.

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Guess the");
    lcd.setCursor(0, 1);
    lcd.print("temperature!");
    while (digitalRead(BUTTON_PIN) == LOW)
        ;
    while (digitalRead(BUTTON_PIN) == HIGH)
        ;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Use the knob");
    lcd.setCursor(0, 1);
    lcd.print("to guess.");
    while (digitalRead(BUTTON_PIN) == LOW)
        ;
    while (digitalRead(BUTTON_PIN) == HIGH)
        ;
    lcd.clear();
}

int mapPotentiometerTemperature(int minIndex, int maxIndex)
{
    // This function is used to read the potentiometer value
    // and map it to the number of cards.
    int potentiometerValue = analogRead(A0);
    int potentioMeterIndex = map(potentiometerValue, 0, 1022, minIndex, maxIndex);
    return potentioMeterIndex;
}

void temperatureGameplay()
{
    // This function is used to run the gameplay of the temperature game.
    temperatureIntroScreen();
    while (digitalRead(BUTTON_PIN) == LOW)
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Your guess: ");
        lcd.setCursor(3, 1);
        lcd.print("=" + String(mapPotentiometerTemperature(0, 40)) + " celcius");
        // This while loop is used to make sure that the screen
        // is refreshed only when the potentiometer value has changed.
        int compareIndex = mapPotentiometerTemperature(0, 40);
        while (compareIndex == mapPotentiometerTemperature(0, 40) && digitalRead(BUTTON_PIN) == LOW)
        {
            compareIndex = mapPotentiometerTemperature(0, 40);
        }
        delay(50);
    }
    while (digitalRead(BUTTON_PIN) == HIGH)
    {
        // Wait for the player to release the button.
    }
    int temperature = readTemperature();
    int playerGuess = mapPotentiometerTemperature(0, 40);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("The temperature");
    lcd.setCursor(0, 1);
    lcd.print("is " + String(temperature) + " celcius");
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
    lcd.print("Your guess");
    lcd.setCursor(0, 1);
    lcd.print("was " + String(playerGuess) + " celcius");
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
    if (temperature == playerGuess)
    {
        lcd.print("You were right!");
        lcd.setCursor(0, 1);
        lcd.print("You won!");
    }
    else
    {

        lcd.print("You were wrong");
        lcd.setCursor(0, 1);
        lcd.print("by " + String(abs(temperature - playerGuess)) + " celcius");
    }
    while (digitalRead(BUTTON_PIN) == LOW)
    {
        // Wait for the player to push the button.
    }
    while (digitalRead(BUTTON_PIN) == HIGH)
    {
        // Wait for the player to release the button.
    }
    lcd.clear();
}