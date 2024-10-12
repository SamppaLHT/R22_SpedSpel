#ifndef DISPLAY_H
#define DISPLAY_H
#include <arduino.h>

void initializeDisplay(void);

void writeByte(uint8_t number, bool last);

void showResult();

void clearDisplay();

#endif
