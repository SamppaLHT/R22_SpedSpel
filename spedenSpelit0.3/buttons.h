#ifndef BUTTONS_H
#define BUTTONS_H

#include <arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>

const byte firstPin = 2; // Ensimmäinen kytkinpinni D-väylällä (2-5 pelin kytkimille)
const byte lastPin = 5;  // Viimeinen kytkinpinni D-väylällä
const byte startPin = 6; // Pin 6 pelin aloituskytkimelle

extern volatile bool gameStarted;

void initButtonsAndButtonInterrupts(void);

ISR(PCINT2_vect);

#endif
