#include "display.h"
#include "buttons.h"
#include "leds.h"
#include "SpedenSpelit.h"

float currentFrequency = 1.0;
volatile bool gameStarted = false;
uint8_t result = 0;
volatile int ledValues[100];
volatile int ledIndex = 0;
volatile int buttonPresses[100];
volatile int buttonIndex = 0;
volatile int correctPressCount = 0;
volatile bool buttonWasPressed = false;

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
  cli();

  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;

  OCR1A = 15624;

  TCCR1B |= (1 << WGM12);

  TCCR1B |= (1 << CS12) | (1 << CS10);

  TIMSK1 |= (1 << OCIE1A);

  TIFR1 |= (1 << OCF1A);

  sei();
}

ISR(TIMER1_COMPA_vect) 
{
    if (ledIndex < 100) 
    {
        if (!buttonWasPressed && ledIndex > 0)
        {
          stopTheGame();
          return;
        }
        buttonWasPressed = false;
        int randomValue = random(0, 4);
        ledValues[ledIndex] = randomValue;
        setLed(ledValues[ledIndex]);
        ledIndex++;
    }
}

void setTimerFrequency(float frequency)
{
  uint16_t newOCR1A = (16000000 / (1024 * frequency)) - 1;
  OCR1A = newOCR1A;
}

void speedUpGame()
{
  currentFrequency *= 1.1;
  setTimerFrequency(currentFrequency);
}

void checkGame() 
{
  if (buttonIndex > 0 && ledIndex > 0) 
  {
    int lastLedValue = ledValues[ledIndex -1];
    int lastButtonPress = buttonPresses[buttonIndex -1];

    if (lastLedValue == lastButtonPress)
    {
      result++;
      correctPressCount++;
      showResult();
      if(correctPressCount % 10 == 0)
      {
        speedUpGame();
      }
    } else 
      {
        stopTheGame();
      }
  }
}

void startTheGame()
{
  resetLedValues();
  resetButtonPresses();
  result = 0;
  initializeTimer();
}

void stopTheGame()
{
  clearDisplay();
  gameStarted = false;
  TIMSK1 &= ~(1 << OCIE1A);
  TCCR1B &= ~((1 << CS12) | (1 << CS10));
  clearAllLeds();
  resetLedValues();
  resetButtonPresses();
}

void resetLedValues()
{
  ledIndex = 0;
  for (int i = 0; i < 100; i++)
  {
    ledValues[i] = -1;
  }
}
