#ifndef BUTTONS_H
#define BUTTONS_H

#include <arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>

const byte firstPin = 2;
const byte lastPin = 5;
const byte startPin = 6;

extern volatile bool gameStarted;

void initButtonsAndButtonInterrupts(void);

ISR(PCINT2_vect);

void resetButtonPresses(void);

#endif
