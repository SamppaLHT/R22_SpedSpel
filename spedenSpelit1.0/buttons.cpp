#include "buttons.h"
#include "SpedenSpelit.h"
#include "leds.h"

unsigned long lastDebounceTime = 0;    // Ajastin kytkinvärähtelyä varten
const unsigned long debounceDelay = 200; // 50 ms debounce-ajastin
volatile uint8_t buttonNumber = 0;
volatile bool buttonPressed = false;


// Kytkimien ja keskeytysten alustus
void initButtonsAndButtonInterrupts(void) 
{
    // Aseta pinnit 2-6 tulopinneiksi
    for (byte pin = firstPin; pin <= startPin; pin++) {
        pinMode(pin, INPUT_PULLUP); // Asetetaan sisääntulopinneiksi ja käytetään pull-up vastuksia
    }

    // Ota käyttöön Pin Change Interrupt PCICR-rekisterissä
    PCICR |= (1 << PCIE2);  // Ota käyttöön keskeytykset PCINT[23:16] (vastaa D-pinssejä 0-7)

    // Aseta PCMSK2-rekisteri niin, että keskeytyksiä syntyy pinneille 2-6
    PCMSK2 |= (1 << PCINT18) | (1 << PCINT19) | (1 << PCINT20) | (1 << PCINT21) | (1 << PCINT22); // pin 2-6
}

// Keskeytyspalvelija kytkinpainalluksille
// Keskeytyspalvelija kytkinpainalluksille
ISR(PCINT2_vect) 
{
  unsigned long currentTime = millis();

  if ((currentTime - lastDebounceTime) > debounceDelay) 
  {
    lastDebounceTime = currentTime;
        
      for (byte pin = firstPin; pin <= startPin; pin++) 
      {
          int buttonState = digitalRead(pin);
            
          if (buttonState == LOW) 
          { 
              if (!buttonPressed) 
              {
                  buttonPressed = true;
                  buttonWasPressed = true;
                  if (buttonIndex < 100) 
                  {
                      switch (pin) 
                      {
                          case 2:
                            buttonPresses[buttonIndex] = 0;
                            Serial.println("Button 0 pressed");
                            break;
                          case 3:
                            buttonPresses[buttonIndex] = 1;
                            Serial.println("Button 1 pressed");
                            break;
                          case 4:
                            buttonPresses[buttonIndex] = 2;
                            Serial.println("Button 2 pressed");
                            break;
                          case 5:
                            buttonPresses[buttonIndex] = 3;
                            Serial.println("Button 3 pressed");
                            break;
                          case 6:
                            gameStarted = true;
                            startTheGame();
                            break;
                          default:
                            break;
                      }
                      buttonIndex++; 
                      printButtonPresses();
                      clearAllLeds();
                  }
                  if (gameStarted && pin != 6) 
                  {
                    checkGame();
                  }
              }
          } else {
              buttonPressed = false;
          }
      }
  }
}

void resetButtonPresses()
{
  buttonIndex = 0;
  for (int i = 0; i < 100; i++)
  {
    buttonPresses[i] = -1;
  }
}

void printButtonPresses() 
{
    Serial.print("Button Presses: ");
    bool hasPrinted = false;

    for (int i = 0; i < 100; i++) 
    {
        if (buttonPresses[i] != -1) 
        {
            Serial.print(buttonPresses[i]);
            hasPrinted = true;
            if (i < 100 - 1) 
            {
                Serial.print(", ");
            }
        }
    }
    if (!hasPrinted) 
    {
        Serial.print("None");
    }

    Serial.println();
}
