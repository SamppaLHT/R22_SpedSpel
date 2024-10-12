#include "display.h"
#include "buttons.h"
#include "leds.h"
#include "SpedenSpelit.h"

volatile uint8_t interruptCount = 0;
float currentFrequency = 1.0;
volatile int ledNumber = 0;
extern volatile uint8_t buttonNumber;
volatile bool gameStarted = false;
uint8_t result = 0;

void setup()
{
  Serial.begin(9600);
  initializeLeds();
  initializeDisplay();
  initButtonsAndButtonInterrupts();
}

void loop()
{
  ledNumber = random(0, 4);
  setLed(ledNumber);
  delay(2000);
  checkGame();
  clearAllLeds();
  delay(500);
  
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

void checkGame() {
    if (gameStarted) {
        if (ledNumber == buttonNumber) 
        {
          showResult();  // Only show result if the game is running
        } else {
          stopTheGame(); // Call to stop the game on incorrect press
        }
    }
}

void initializeGame()
{
  
}

void startTheGame()
{
  result = 0; //timerin resetointi täytyy lisätä
  initializeGame();
  initializeTimer();
  Serial.println("Game has started");
}

void stopTheGame()
{
  gameStarted = false;
  TIMSK1 &= ~(1 << OCIE1A);
  TCCR1B &= ~((1 << CS12) | (1 << CS10));
  clearAllLeds();
  setToZero();
  Serial.println("Game has stopped and interrupts are disabled");
}
