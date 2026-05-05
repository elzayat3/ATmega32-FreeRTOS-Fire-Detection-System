#ifndef LEDS_CFG_H_
#define LEDS_CFG_H_

/**
 * @file    LEDS_Cfg.h
 * @author  Abdelrahman Elzayat
 * @brief   Configuration file for LEDs HAL driver
 */

#include "StdTypes.h"
#include "DIO_Int.h"

/* =========================
 * Red LED Configuration
 * ========================= */

/**
 * @brief Red LED connected pin.
 *
 * Change this pin according to your hardware connection.
 */
#define RED_LED_PIN                DIO_PINC0

/**
 * @brief Red LED active voltage.
 *
 * Use HIGH for active-high LED connection.
 * Use LOW  for active-low LED connection.
 */
#define RED_LED_ACTIVE_STATE       HIGH

/**
 * @brief Red LED inactive voltage.
 */
#define RED_LED_INACTIVE_STATE     LOW


/* =========================
 * Yellow LED Configuration
 * ========================= */

/**
 * @brief Yellow LED connected pin.
 *
 * Change this pin according to your hardware connection.
 */
#define YELLOW_LED_PIN             DIO_PINC1

/**
 * @brief Yellow LED active voltage.
 *
 * Use HIGH for active-high LED connection.
 * Use LOW  for active-low LED connection.
 */
#define YELLOW_LED_ACTIVE_STATE    HIGH

/**
 * @brief Yellow LED inactive voltage.
 */
#define YELLOW_LED_INACTIVE_STATE  LOW

#endif /* LEDS_CFG_H_ */