#ifndef LEDS_INT_H_
#define LEDS_INT_H_

/**
 * @file    LEDS_Int.h
 * @author  Abdelrahman Elzayat
 * @brief   Interface for LEDs HAL driver
 *
 * @details
 * This file provides separate APIs for controlling
 * the Red LED and Yellow LED.
 */

/* =========================
 * Red LED APIs
 * ========================= */

/**
 * @brief Turns Red LED ON.
 *
 * @return void
 */
void RED_LED_On(void);

/**
 * @brief Turns Red LED OFF.
 *
 * @return void
 */
void RED_LED_Off(void);


/* =========================
 * Yellow LED APIs
 * ========================= */

/**
 * @brief Turns Yellow LED ON.
 *
 * @return void
 */
void YELLOW_LED_On(void);

/**
 * @brief Turns Yellow LED OFF.
 *
 * @return void
 */
void YELLOW_LED_Off(void);

#endif /* LEDS_INT_H_ */