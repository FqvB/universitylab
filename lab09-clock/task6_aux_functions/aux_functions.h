#ifndef AUX_FUNCTIONS_H
#define AUX_FUNCTIONS_H

#include <stdint.h>

void display(uint8_t digit);
void indication(uint8_t digit12, uint8_t digit34, uint8_t which_digit);
void delay(uint32_t ms);
void digit_blinking(uint8_t digit_position, uint8_t blink_digit_position1, uint8_t blink_digit_position2, uint16_t j2);

#endif
