# SpedenSpelit

SpedenSpelit is a simple reaction time related game.

## Description

The game works by the software turning on a single randomized led on at a time, then it waits for a button press, the duration of the "active time" of the led. When correct button has been pressed within the approved timeframe, the game increments the current score on the 7-segment displays, continues to the second round and turns on the second randomized led. When the player has reached the score of 10, the game speeds up the "led active time" and the delay between leds by 10% and the game speeds up evey 10 successful rounds. If the player fails to press a button on time or presses the wrong button the game stops and score is then reset.

## Getting Started!

![Vuokaavio](https://github.com/user-attachments/assets/41eda644-629f-4765-82d3-1a8abe51559d)

![SpedenSpelitV1](https://github.com/user-attachments/assets/de2763f6-4148-4605-86ec-7b75340bde7a)


### Dependencies

Software and hardware (inside the brackets are the components we used)

* Arduino IDE
* Arduino UNO
* 4x led lights (HLMP-4740)
* 4x pushbutton switches (ESE20C321)
* 2x 7-segment displays (SC52-11EWA)
* 2x Serial to parallel shift registers (SN74HC595N)


## Authors

[Samu Lyhty](https://github.com/SamppaLHT)

[Topias Perälä](https://github.com/saintcernunnos)

[Santeri Syrjälä](https://github.com/sYrreee)

Joonas Väyrynen

## Version History

* 1.0      [Link to download](https://github.com/SamppaLHT/R22_SpedSpel/releases/tag/SpedenSpelit1.0)
    * Full release of the working program  

* 0.5
    * Reworks on gamelogic
      
* 0.3
    * Introduced first bits of gamelogic

* 0.1
    * First stage versions of the modules
    
## License

This project is licensed under the GNU GPLv3 License - see the LICENSE.txt file for details

## Acknowledgments

* [Arduino Language Reference](https://docs.arduino.cc/language-reference/)
* [Led-Datasheet](https://www.farnell.com/datasheets/1918234.pdf?_gl=1*1ns2hag*_gcl_au*MTcyMjAyMzg3OS4xNzI3MzY1NTM2)
* [Pushbutton-Datasheet](https://www.farnell.com/datasheets/1790644.pdf?_gl=1*16wbfqn*_gcl_au*MTcyMjAyMzg3OS4xNzI3MzY1NTM2)
* [7-Segment display-Datasheet](https://www.farnell.com/datasheets/2047557.pdf?_gl=1*16wbfqn*_gcl_au*MTcyMjAyMzg3OS4xNzI3MzY1NTM2)
* [Shift Register 74HC595-Datasheet](https://www.ti.com/lit/ds/symlink/sn74hc595.pdf?ts=1728594662862&ref_url=https%253A%252F%252Fbr.mouser.com%252F)
* [Serial to Parallel Shifting-Out with a 74HC595](https://docs.arduino.cc/tutorials/communication/guide-to-shift-out/#shftout13)
* [Tinkercad](https://www.tinkercad.com)
