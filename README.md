# :video_game:Game Station Arduino Project:video_game:

GameStation project for Arduino Uno R3 with a 2x16 LCD screen and some basic electronic components.
GameStation is a gaming device that allows the user play different games on a single device.
Goals for this project is to learn more about programming microcontrollers and getting
more familiar of using basic electronic components such as LCD, LEDs, capacitor, resistors, potentiometer
and piezo. <br>
Check out the video to see the GameStation in action: [![Video link](https://img.youtube.com/vi/sNhcjjXW0VE/default.jpg )](https://www.youtube.com/watch?v=sNhcjjXW0VE&ab_channel=JyriMäättä)
## :game_die:Games programmed so far:game_die::
1. MEMORY -game:black_joker:<br>
The classic memory card game now in your Arduino! Use the potentiometer to choose a card
and try to find the matching pair! See how fast you can solve it!
2. TOWER STACK - game:tokyo_tower:<br>
Got a steady hand like an architect? Now it's your time to build the tallest tower ever seen!
With presicion and fast fingers you'll be stacking blocks on top of each other by pushing
the button.
3. SPACESHIP - game:space_invader:<br>
Avoid the asteroids to stay alive! Move your spaceship with the push button to avoid
incoming asteroids. Beware as the asteroids may move unprecidtably and fast as a bullet.
4. REACTION -game:sparkler:<br>
You say you're fast? Let's see how fast you really are! Just push the button as soon
as you can see the LED light up. You must be consistant because you get three tries
and the average speed counts too!
5. TEMPERATURE -game:fire:<br>
Can you feel the atmosphere? Can you guess the right temperature? Use the potentiometer to
make a guess on how warm the temperature is in your room.
## :electric_plug:Circuit description:electric_plug::
Circuit has one **push button** which is for navigating through games and playing them.
Green **LED** is for blinking every time the player makes another point or proceeds in the game. With the **potentiometer**
the player can dim the **LED** or turn it off completely if he/she wants to do so.
**Piezo** is for making a "Game Over" sound whenever the player looses the game.
The second **potentiometer** is for the MEMORY -game where you can use it to choose
a card of your choice from the screen. **Decoupling capacitor** is for decoupling
changes caused by the components from the rest of the circuit(especially if the circuit has a motor later on). 
TEMPERATURE -game uses a **temperature sensor** to measure the temperature in the room.
The circuit is powered with a 9V battery through the DC jack.
You can view the circuit design from the AUTODESK Tinkercad from the following link:
https://www.tinkercad.com/things/2UjaoKeHYQ5
![GameStation](https://github.com/Jyppara/Game_Station_Arduino_Project/blob/main/Simulation%20pictures/GameStation.jpg)
![GameStation wiring](https://github.com/Jyppara/Game_Station_Arduino_Project/blob/main/Simulation%20pictures/GameStation-%20Emulator.png)
![GameStation schematic](https://github.com/Jyppara/Game_Station_Arduino_Project/blob/main/Simulation%20pictures/GameStation-%20Emulator_schematic.PNG)
