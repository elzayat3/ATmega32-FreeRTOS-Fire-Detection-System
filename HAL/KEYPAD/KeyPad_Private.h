#ifndef KEYPAD_PRIVATE_H_
#define KEYPAD_PRIVATE_H_

/**
 * @file    KeyPad_Private.h
 * @author  Abdelrahman Elzayat
 * @brief   Private declarations for Keypad HAL driver
 *
 * @details
 * This file contains internal extern declarations used by the keypad
 * implementation file. It should not be included by the application layer.
 */

#include "StdTypes.h"
#include "DIO_Int.h"
#include "KeyPad_Cfg.h"

/**
 * @brief Keypad keys mapping array.
 */
extern const u8 KeysArr[ROWS][COLS];

/**
 * @brief Keypad output pins array.
 *
 * These pins are connected to keypad rows.
 */
extern const DIO_Pin_t PinOut[ROWS];

/**
 * @brief Keypad input pins array.
 *
 * These pins are connected to keypad columns.
 */
extern const DIO_Pin_t PinIn[COLS];

#endif /* KEYPAD_PRIVATE_H_ */