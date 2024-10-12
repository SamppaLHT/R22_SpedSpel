#include "display.h"
#include "buttons.h"
#include "leds.h"
#include "SpedenSpelit.h"

// Use these 2 volatile variables for communicating between
// loop() function and interrupt handlers
volatile int buttonNumber = -1;           // for buttons interrupt handler
volatile bool newTimerInterrupt = false;  // for timer interrupt handler
volatile bool generateRandom = false;
volatile uint8_t interruptCount = 0;
float currentFrequency = 1.0;


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
void setTimerFrequency(float frequency)
{
    // Calculate new compare match value (OCR1A)
    uint16_t newOCR1A = (16000000 / (1024 * frequency)) - 1;
    OCR1A = newOCR1A;
}
ISR(TIMER1_COMPA_vect)
{
  generateRandom = true;
  interruptCount++;

  if (interruptCount > 0 && interruptCount % 10 == 0);
  {
    currentFrequency *= 1.1;
    setTimerFrequency(currentFrequency);
  }
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
  initializeGame();
  initializeTimer();

  Serial.println("Game has started");
}

