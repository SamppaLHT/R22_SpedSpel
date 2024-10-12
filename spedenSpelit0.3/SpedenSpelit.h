#ifndef SPEDENSPELIT_H
#define SPEDENSPELIT_H
#include <arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>
extern volatile bool gameStarted;
extern uint8_t result;

void initializeTimer(void);

ISR(TIMER1_COMPA_vect);

void initializeGame(void);

void checkGame(byte);

void startTheGame(void);

void stopTheGame(void);

#endif