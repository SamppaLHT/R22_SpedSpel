#include "buttons.h"
#include "SpedenSpelit.h"

volatile bool gameStarted = false;
volatile uint8_t lastButtonState = 0;  // Edellinen painikeasento
unsigned long lastDebounceTime = 0;    // Ajastin kytkinvärähtelyä varten
const unsigned long debounceDelay = 50; // 50 ms debounce-ajastin

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
ISR(PCINT2_vect) {
    unsigned long currentTime = millis();

    // Tarkistetaan debounce
    if ((currentTime - lastDebounceTime) > debounceDelay) {
        for (byte pin = firstPin; pin <= startPin; pin++) {
            if (digitalRead(pin) == LOW) { // Kytkintä painetaan (LOW)
                
                if (pin == startPin) {  // Jos napista 6 painetaan, peli alkaa
                    gameStarted = true;
                    startTheGame();
                    Serial.println("Peli aloitettu!");
                } else if (gameStarted) {  // Jos peli on käynnissä
                    if (pin == 5) {
                        Serial.println("Nappia 5 painettu");
                    } else {
                        Serial.print("Nappia ");
                        Serial.print(pin);
                        Serial.println(" painettu");
                    }
                } else if (pin == 5) { // Jos peli ei ole käynnissä ja nappia 5 painetaan
                    Serial.println("Nappia 5 painettu (peli ei ole vielä alkanut)");
                }
            }
        }
        lastDebounceTime = currentTime; // Päivitetään viimeisin debounce-aika
    }
}
