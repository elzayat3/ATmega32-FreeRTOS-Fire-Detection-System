#ifndef KEYPAD_INT_H_
#define KEYPAD_INT_H_

/**
 * @file    KEYPAD_Int.h
 * @author  Abdelrahman Elzayat
 * @brief   Keypad HAL driver interface
 *
 * @details
 * This file provides the public APIs for keypad initialization
 * and key reading.
 */

#include "StdTypes.h"

/**
 * @brief Returned value when no key is pressed.
 */
#define KEYPAD_NO_KEY    0u

/**
 * @brief Initializes keypad pins.
 *
 * @details
 * This function initializes keypad rows and columns according
 * to the keypad driver configuration.
 *
 * @return void
 */
void KEYPAD_Init(void);

/**
 * @brief Gets the currently pressed key.
 *
 * @details
 * This function scans the keypad and returns the pressed key value.
 * If no key is pressed, it returns KEYPAD_NO_KEY.
 *
 * @return u8
 *         - Pressed key value
 *         - KEYPAD_NO_KEY if no key is pressed
 */
u8 KEYPAD_GetKey(void);

#endif /* KEYPAD_INT_H_ */