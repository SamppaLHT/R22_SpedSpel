#include "leds.h"


void initializeLeds()
{
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);
}

void setLed(byte ledNumber)
{
  switch(ledNumber) 
  {
    case 0:
      digitalWrite(A2, HIGH);
      break;
    case 1:
      digitalWrite(A3, HIGH);
      break;
    case 2:
      digitalWrite(A4, HIGH);
      break;
    case 3:
      digitalWrite(A5, HIGH);
      break;
  }
}


void clearAllLeds()
{
  digitalWrite(A2, LOW);
  digitalWrite(A3, LOW);
  digitalWrite(A4, LOW);
  digitalWrite(A5, LOW);
}

void setAllLeds()
{
  digitalWrite(A2, HIGH);
  digitalWrite(A3, HIGH);
  digitalWrite(A4, HIGH);
  digitalWrite(A5, HIGH);
}


void show1()
{
  for(int i = 0; i <= 15; i++)
  {
    digitalWrite(A5, i & 0x01);
    digitalWrite(A4, (i >> 1) & 0x01);
    digitalWrite(A3, (i >> 2) & 0x01);
    digitalWrite(A2, (i >> 3) & 0x01);

    delay (450);
  }
}

void show2(int rounds = 7)
{
  int delayTime = 450;
  int minDelay = 100;
  int speedIncrement = 50;

  for (int r = 0; r < rounds; r++)
  {
    for(int led = 0; led <= 3; led++)
    {
      clearAllLeds();
      setLed(led);
      delay(delayTime);

      if(delayTime > minDelay)
      {
        delayTime -= speedIncrement;
      }
    }
  }
  clearAllLeds();
}