#ifndef SPEDENSPELIT_H
#define SPEDENSPELIT_H
#include <arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>

extern volatile bool gameStarted;
extern uint8_t result;
extern volatile int buttonPresses[100];
extern volatile int buttonIndex;
extern volatile int lastButtonPress;
extern volatile bool buttonWasPressed;

void initializeTimer(void);

ISR(TIMER1_COMPA_vect);

void checkGame();

void startTheGame(void);

void stopTheGame(void);

#endif