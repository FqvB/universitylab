#ifndef AUX_FUNCTIONS_H
#define AUX_FUNCTIONS_H

#include <stdint.h>

void display(uint8_t digit);
void indication(uint8_t digit12, uint8_t digit34, uint8_t which_digit);
void indication2(uint8_t digit1, uint8_t digit2, uint8_t digit3, uint8_t digit4, uint8_t which_digit);
void delay(uint32_t ms);
void digit_blinking(uint8_t digit_position, uint8_t blink_digit_position1, uint8_t blink_digit_position2, uint16_t j2);
void play(uint8_t n, uint8_t e);

#endif
