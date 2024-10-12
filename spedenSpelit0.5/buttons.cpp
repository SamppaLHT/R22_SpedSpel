#include "buttons.h"
#include "SpedenSpelit.h"

unsigned long lastDebounceTime = 0;    // Ajastin kytkinvärähtelyä varten
const unsigned long debounceDelay = 200; // 50 ms debounce-ajastin
volatile uint8_t buttonNumber = 0;
volatile bool buttonPressed = false;


// Kytkimien ja keskeytysten alustus
void initButtonsAndButtonInterrupts(void) {
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
ISR(PCINT2_vect) {
    unsigned long currentTime = millis();

    if ((currentTime - lastDebounceTime) > debounceDelay) {
        lastDebounceTime = currentTime; // Update debounce time
        
        for (byte pin = firstPin; pin <= startPin; pin++) {
            // Read the button state
            int buttonState = digitalRead(pin);
            
            if (buttonState == LOW) { 
                if (!buttonPressed) {
                    buttonPressed = true;

                    switch (pin) {
                        case 2: // Pin 2 corresponds to button 0
                            buttonNumber = 0;
                            Serial.println("button 0 pressed");
                            break;
                        case 3: // Pin 3 corresponds to button 1
                            buttonNumber = 1;
                            Serial.println("button 1 pressed");
                            break;
                        case 4: // Pin 4 corresponds to button 2
                            buttonNumber = 2;
                            Serial.println("button 2 pressed");
                            break;
                        case 5: // Pin 5 corresponds to button 3
                            buttonNumber = 3;
                            Serial.println("button 3 pressed");
                            break;
                        case 6: // Pin 6 corresponds to the start button
                            gameStarted = true;
                            startTheGame(); // Start the game logic
                            break;
                        default:
                            break;
                    }

                    // Call checkGame() only for buttons 2-5
                    if (gameStarted && pin != 6) {
                        checkGame();
                    }
                }
            } else {
                buttonPressed = false;
            }
        }
    }
}