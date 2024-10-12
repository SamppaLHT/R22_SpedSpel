#include "display.h"
#include <stdint.h>
#include "SpedenSpelit.h"

const int resetPin = 12;
const int shiftClockPin = 11;
const int latchClockPin = 10;
const int serialInputPin = 8;

const uint8_t digits[10] =
{
  0b00111111, // 0
  0b00000110, // 1
  0b01011011, // 2
  0b01001111, // 3
  0b01100110, // 4
  0b01101101, // 5
  0b01111101, // 6
  0b00000111, // 7
  0b01111111, // 8
  0b01101111  // 9
};

void initializeDisplay()
{
    pinMode(resetPin, OUTPUT);
    pinMode(shiftClockPin, OUTPUT);
    pinMode(latchClockPin, OUTPUT);
    pinMode(serialInputPin, OUTPUT);

    digitalWrite(resetPin, HIGH);
    digitalWrite(shiftClockPin, LOW);
    digitalWrite(latchClockPin, LOW);
    digitalWrite(serialInputPin, LOW);
}


void writeTwoBytes(uint8_t digit1, uint8_t digit2)
{
    for (int i = 7; i >= 0; i--) 
    {
        digitalWrite(serialInputPin, (digit1 >> i) & 0x01);
        digitalWrite(shiftClockPin, HIGH);
        delayMicroseconds(1);
        digitalWrite(shiftClockPin, LOW);
    }

    for (int i = 7; i >= 0; i--) 
    {
        digitalWrite(serialInputPin, (digit2 >> i) & 0x01);
        digitalWrite(shiftClockPin, HIGH);
        delayMicroseconds(1);
        digitalWrite(shiftClockPin, LOW);
    }

    digitalWrite(latchClockPin, HIGH);
    delayMicroseconds(1);
    digitalWrite(latchClockPin, LOW);
}

void showResult()
{
  if (gameStarted)
  {
  if (result > 99) 
  {
    return;
  }
  uint8_t tens = result % 10;
  uint8_t ones = result / 10;
  writeTwoBytes(digits[tens], digits[ones]);
  }
}

void setToZero()
{
  writeTwoBytes(0x00, 0x00);
}
