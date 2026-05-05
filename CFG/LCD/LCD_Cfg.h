#ifndef LCD_CFG_H_
#define LCD_CFG_H_

/**
 * @file    LCD_Cfg.h
 * @author  Abdelrahman Elzayat
 * @brief   Configuration file for LCD driver
 */

#include "DIO_Int.h"

/* =========================
 * LCD Control Pins
 * ========================= */

/*
 * PINA0 and PINA1 are used for ADC sensors.
 * PIND0 and PIND1 are reserved for UART RX/TX.
 */
#define RS              DIO_PINA1
#define EN              DIO_PINA2

/* =========================
 * LCD 8-bit Port
 * ========================= */

/*
 * Used only if LCD_MODE == _8_BIT.
 * In this project LCD is configured in 4-bit mode,
 * so LCD_PORT is not used.
 */
#define LCD_PORT        PA

/* =========================
 * LCD Commands
 * ========================= */

/*
 * For 4-bit mode, 2 lines, 5x8 font.
 * 0x38 is for 8-bit mode.
 */
#define FUNCTION_SET    0x28

#define LCD_Display     0x0c
#define LCD_Clear_Init  0x01
#define LCD_ENTRY       0x06

/* =========================
 * LCD 4-bit Data Pins
 * ========================= */

#define D7              DIO_PINA6
#define D6              DIO_PINA5
#define D5              DIO_PINA4
#define D4              DIO_PINA3

/* =========================
 * LCD Mode
 * ========================= */

#define _4_BIT          1
#define _8_BIT          2

#define LCD_MODE        _4_BIT

#endif /* LCD_CFG_H_ */