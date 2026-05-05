#ifndef BUZZER_CFG_H_
#define BUZZER_CFG_H_

/**
 * @file    BUZZER_Cfg.h
 * @author  Abdelrahman Elzayat
 * @brief   Configuration file for Buzzer HAL driver
 */

#include "StdTypes.h"
#include "DIO_Int.h"

/**
 * @brief Buzzer connected pin.
 *
 * In this project, buzzer is connected to PINC2.
 */
#define BUZZER_PIN              DIO_PINC5

/**
 * @brief Buzzer active voltage.
 *
 * Use HIGH for active-high buzzer connection.
 * Use LOW  for active-low buzzer connection.
 */
#define BUZZER_ACTIVE_STATE     HIGH

/**
 * @brief Buzzer inactive voltage.
 */
#define BUZZER_INACTIVE_STATE   LOW

#endif /* BUZZER_CFG_H_ */