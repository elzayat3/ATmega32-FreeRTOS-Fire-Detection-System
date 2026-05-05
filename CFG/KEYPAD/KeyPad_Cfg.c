#include "StdTypes.h"
#include "DIO_Int.h"

#include "KeyPad_Int.h"
#include "KeyPad_Cfg.h"
#include "KeyPad_Private.h"

/**
 * @file    KeyPad_Cfg.c
 * @author  Abdelrahman Elzayat
 * @brief   Keypad configuration source file
 *
 * @details
 * This file contains keypad button mapping and keypad pin configuration.
 */

/**
 * @brief Keypad button mapping.
 */
const u8 KeysArr[ROWS][COLS] =
{
	{'1', '2', '3', 'A'},
	{'4', '5', '6', 'B'},
	{'7', '8', '9', 'C'},
	{'*', '0', '#', 'D'}
};

/**
 * @brief Keypad output pins.
 *
 * These pins are connected to keypad rows.
 */
const DIO_Pin_t PinOut[ROWS] =
{
	DIO_PINB0,
	DIO_PINB1,
	DIO_PINB2,
	DIO_PINB3
};

/**
 * @brief Keypad input pins.
 *
 * These pins are connected to keypad columns.
 */
const DIO_Pin_t PinIn[COLS] =
{
	DIO_PINB4,
	DIO_PINB5,
	DIO_PINB6,
	DIO_PINB7
};