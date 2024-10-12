#include "buttons.h"
#include "SpedenSpelit.h"

unsigned long lastDebounceTime = 0;    // Ajastin kytkinvärähtelyä varten
const unsigned long debounceDelay = 50; // 50 ms debounce-ajastin
volatile uint8_t buttonNumber = 0;


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
        for (byte pin = firstPin; pin <= startPin; pin++) {
            if (digitalRead(pin) == LOW) {

                if (pin == 6) {
                    gameStarted = true;
                    startTheGame();
                    Serial.println("Peli aloitettu!");
                } else if (gameStarted) {
                    switch (pin) {
                        case 2:
                            buttonNumber = 0;
                            break;
                        case 3:
                            buttonNumber = 1;
                            break;
                        case 4:
                            buttonNumber = 2;
                            break;
                        case 5:
                            buttonNumber = 3;
                            break;
                        default:
                            break;
                    }
                    Serial.print("Nappia ");
                    Serial.print(buttonNumber);
                    Serial.println(" painettu");
                }

                break;
            }
        }
        lastDebounceTime = currentTime;
    }
}

