# SpedenSpelit

SpedenSpelit is a simple reaction time related game.




## Description

The core concept of the game is based on one of the four LEDs on the board turning on and the player pressing the corresponding button to said LED within a decreasing timeframe. Each correct input by the user increases their score by 1 and progresses the game to the second round, while every tenth round speeds up the timeframe of the rounds by 10%. LEDs are turned on randomly, making this instance of SpedenSpelit strictly reaction-based. The player beats the game upon reaching the maximum score of 99 and loses the game by either pressing the wrong button or failing to input a button press within the timeframe.



## Overview

![Vuokaavio](https://github.com/user-attachments/assets/41eda644-629f-4765-82d3-1a8abe51559d)




The user interface features four buttons directly under the four LEDs, a fifth button assigned to be a 'start button', as well as two 7-segment displays to track the player's progress. Pressing start button runs the startTheGame function and the game begins.
Upon pressing the start button, the game will light up the first LED. An interrupt service routine (ISR) generates a random value between the parameter of four numbers that determines which of the four LEDs will be turned on. 
The base speed of the game is set to operate on a 1Hz frequency, making the initial timeframe for the user to input the correct button press a duration of one second. The game speed is increased on every ten successful rounds by 10%, which then becomes the new timeframe for the affected rounds until the command to speed the game up is run again after another ten successful rounds. This timeframe of the round is started when the ISR turns on the LED.


Upon the LED lighthing up and simultaneously the timer for the concurrent round starting, the program now awaits for the user to play that round. If the player does not press any button at all within the timeframe of the round, the program will run the stopTheGame function and the game session will end.
If the player presses a button, the button press is registered by the program. Each of the buttons have an assigned value, and the game determines in the checkGame function whether or not the button pressed was the correct button by comparing the value of the button pressed to the value that ISR generated to turn on one of the LEDs. 

If the program receives a different value from the button press than it did from the ISR's generated number corresponding to the LED of this round, then the program concludes the button press to be incorrect and subsequently runs the stopTheGame function to end the game session.
If the checkGame function determines the values to be the same, the program reads the button press to be the correct one and adds an increment to the user's score value. The updated score will be visible to the user as the checkGame function concludes by running the showResult function, which updates the 7-segment display(s) to show the current score of the player's game session. The 7-segment display(s) are updated by sending a set binary value utilizing the serial-to-parallel shift register components. When the game session ends, the player's score remains visible to the player.

Upon pressing the correct button, the score display is updated and the next round begins. The aforementioned ISR timer tracks the user's correct button presses to determine the round count of the game, decreasing the allocated timeframe per round as outlined previously.
The player can start a new game session at any point after the previous one ended by starting the game via the start button. The score input on the 7-segment display(s) and the tracked correct button presses along with the timeframe duration of the round will be reset between game sessions.

![SpedenSpelitV1](https://github.com/user-attachments/assets/de2763f6-4148-4605-86ec-7b75340bde7a)

![Full build of project1 0](https://github.com/user-attachments/assets/ddb56cba-ba5a-4194-90c5-3f93760964cb)

### Dependencies

Software and hardware (inside the brackets are the components used)

* Arduino IDE
* Arduino UNO
* 4x LED lights (HLMP-4740)
* 4x pushbutton switches (ESE20C321)
* 2x 7-segment displays (SC52-11EWA)
* 2x serial-to-parallel shift registers (SN74HC595N)



## Authors

[Samu Lyhty](https://github.com/SamppaLHT)

[Topias Perälä](https://github.com/saintcernunnos)

[Santeri Syrjälä](https://github.com/sYrreee)

[Joonas Väyrynen](https://github.com/Joneezzi)

## Version History

* 1.0      [Link to download](https://github.com/SamppaLHT/R22_SpedSpel/releases/tag/SpedenSpelit1.0)
    * Full release of the working program
 
* 0.9
    * Final test version with useful commands for debugging and testing individual features. Added ISR functions to support game logic and tie the program together as well as tidied up existing modules

* 0.5
    * First version of broadly working checkGame function and further reworks on existing modules to support it
      
* 0.3
    * Reworks to display and buttons modules as well as first instances of game logic aimed at integrating the separate modules

* 0.1
    * First versions of the modules and timer initialization
    
## License

This project is licensed under the GNU GPLv3 License - see the [LICENSE.txt file](https://github.com/SamppaLHT/R22_SpedSpel/blob/main/LICENCE.txt) for details

## Acknowledgments

* [Arduino Language Reference](https://docs.arduino.cc/language-reference/)
* [Led-Datasheet](https://www.farnell.com/datasheets/1918234.pdf?_gl=1*1ns2hag*_gcl_au*MTcyMjAyMzg3OS4xNzI3MzY1NTM2)
* [Pushbutton-Datasheet](https://www.farnell.com/datasheets/1790644.pdf?_gl=1*16wbfqn*_gcl_au*MTcyMjAyMzg3OS4xNzI3MzY1NTM2)
* [7-Segment display-Datasheet](https://www.farnell.com/datasheets/2047557.pdf?_gl=1*16wbfqn*_gcl_au*MTcyMjAyMzg3OS4xNzI3MzY1NTM2)
* [Shift Register 74HC595-Datasheet](https://www.ti.com/lit/ds/symlink/sn74hc595.pdf?ts=1728594662862&ref_url=https%253A%252F%252Fbr.mouser.com%252F)
* [Serial to Parallel Shifting-Out with a 74HC595](https://docs.arduino.cc/tutorials/communication/guide-to-shift-out/#shftout13)
* [Tinkercad](https://www.tinkercad.com)
