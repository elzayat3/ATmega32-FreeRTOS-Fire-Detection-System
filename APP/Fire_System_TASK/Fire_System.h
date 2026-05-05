#ifndef FIRE_SYSTEM_H_
#define FIRE_SYSTEM_H_

/**
 * @file    Fire_System.h
 * @author  Abdelrahman Elzayat
 * @brief   Interface for fire detection and control system.
 *
 * @details
 * This module contains the public APIs and system states used by
 * the fire detection application. It manages the system state machine
 * and provides FreeRTOS task functions for monitoring sensors,
 * controlling outputs, and handling keypad reset.
 */

#include "StdTypes.h"

/**
 * @enum state_t
 * @brief Defines the fire system operating states.
 */
typedef enum
{
	NORMAL = 0,  /**< Normal state: no heat or fire detected */
	HEAT,       /**< Heat warning state */
	FIRE        /**< Fire alarm state */
} state_t;

/**
 * @brief Initializes the fire system module.
 *
 * @details
 * Creates required synchronization resources used by the fire system,
 * such as LCD mutex.
 *
 * @return error_t
 *         - OK  if initialization succeeded
 *         - NOK if initialization failed
 */
error_t Fire_System_Init(void);

/**
 * @brief Main fire system control task.
 *
 * @details
 * Executes the output actions according to the current system state.
 * It controls LCD, LEDs, motor, and buzzer.
 *
 * @param pvParameters FreeRTOS task parameter. Not used.
 *
 * @return void
 */
void Fire_System_MainTask(void *pvParameters);

/**
 * @brief Fire system state checking task.
 *
 * @details
 * Reads filtered sensor values and updates the system state
 * according to temperature and smoke thresholds.
 *
 * @param pvParameters FreeRTOS task parameter. Not used.
 *
 * @return void
 */
void Fire_System_CheckStateTask(void *pvParameters);

/**
 * @brief Fire system keypad task.
 *
 * @details
 * Handles keypad password input while the system is in FIRE state.
 * If the correct password is entered, the system requests reset to NORMAL.
 *
 * @param pvParameters FreeRTOS task parameter. Not used.
 *
 * @return void
 */
void Fire_System_KeypadTask(void *pvParameters);

/**
 * @brief Gets the current fire system state.
 *
 * @return Current system state.
 */
state_t Fire_System_GetState(void);

#endif /* FIRE_SYSTEM_H_ */