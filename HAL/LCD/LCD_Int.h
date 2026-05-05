#ifndef LCD_INT_H_
#define LCD_INT_H_

/**
 * @file    LCD_Int.h
 * @brief   Public interface for LCD driver.
 *
 * @details
 * This file contains the public APIs used by the application layer
 * to initialize and control a character LCD.
 *
 * The driver supports:
 * - LCD initialization
 * - Character and string display
 * - Number display
 * - Cursor positioning
 * - Clear screen and clear selected cells
 * - Binary and hexadecimal display
 * - Custom character creation
 *
 * @author  Abdelrahman Elzayat
 */

#include "StdTypes.h"

/**
 * @brief Initializes the LCD module.
 *
 * @details
 * This function initializes the LCD according to the selected mode
 * in LCD configuration file, either 4-bit mode or 8-bit mode.
 *
 * @return void
 */
void LCD_Init(void);

/**
 * @brief Displays a single character on the LCD.
 *
 * @param ch Character to be displayed.
 *
 * @return void
 */
void LCD_WriteChar(c8 ch);

/**
 * @brief Displays a string on the LCD.
 *
 * @param str Pointer to the null-terminated string.
 *
 * @return void
 *
 * @note The string must be terminated with '\\0'.
 */
void LCD_WriteString(const c8 *str);

/**
 * @brief Clears the LCD display.
 *
 * @return void
 */
void LCD_Clear(void);

/**
 * @brief Displays a signed decimal number on the LCD.
 *
 * @param num Number to be displayed.
 *
 * @return void
 */
void LCD_WriteNumber(s32 num);

/**
 * @brief Sets the LCD cursor position.
 *
 * @param line LCD line number.
 *        - 0: First line
 *        - 1: Second line
 *
 * @param cell Cell position in the selected line.
 *
 * @return void
 */
void LCD_SetCursor(u8 line, u8 cell);

/**
 * @brief Displays a string at a specific LCD position.
 *
 * @param line LCD line number.
 * @param cell Cell position.
 * @param str  Pointer to the null-terminated string.
 *
 * @return void
 */
void LCD_WriteStringCursor(u8 line, u8 cell, const c8 *str);

/**
 * @brief Clears a number of cells starting from a specific position.
 *
 * @param line       LCD line number.
 * @param cell       Start cell position.
 * @param NofCells   Number of cells to clear.
 *
 * @return void
 */
void LCD_ClearCursor(u8 line, u8 cell, u8 NofCells);

/**
 * @brief Displays an 8-bit number in binary format.
 *
 * @param num Number to be displayed in binary.
 *
 * @return void
 */
void LCD_WriteBinary(u8 num);

/**
 * @brief Displays an 8-bit number in hexadecimal format.
 *
 * @param num Number to be displayed in hexadecimal.
 *
 * @return void
 */
void LCD_WriteHex(u8 num);

/**
 * @brief Creates and stores a custom LCD character in CGRAM.
 *
 * @param pattern Pointer to an array of 8 bytes representing the custom character.
 * @param address CGRAM address from 0 to 7.
 *
 * @return void
 */
void LCD_CustomChar(const u8 *pattern, u8 address);

#endif /* LCD_INT_H_ */