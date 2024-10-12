#include "display.h"
#include "buttons.h"
#include "leds.h"
#include "SpedenSpelit.h"

void setup()
{
  Serial.begin(9600);
  initializeLeds();
  initializeDisplay();
  initButtonsAndButtonInterrupts();
}

void loop()
{
  
}

void initializeTimer(void)
{
	TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;

  OCR1A = 15624; //16  MHz / 1024 prescaler = 15625 for 1 Hz

  TCCR1B |= (1 << WGM12); //CTC mode

  TCCR1B |= (1 << CS12) | (1<< CS10); //CS10 & CS12 for 1024 prescaler

  TIMSK1 |= (1 << OCIE1A); //Timer compare interrupt

  sei();
}

ISR(TIMER1_COMPA_vect)
{

}

void checkGame(byte nbrOfButtonPush)
{

}

void initializeGame()
{
	// see requirements for the function from SpedenSpelit.h
}

void startTheGame()
{

}

