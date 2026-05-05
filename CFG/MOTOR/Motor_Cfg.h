#ifndef MOTOR_CFG_H_
#define MOTOR_CFG_H_

/**
 * @file    MOTOR_Cfg.h
 * @author  Abdelrahman Elzayat
 * @brief   Configuration file for Motor HAL driver
 */

#include "StdTypes.h"
#include "DIO_Int.h"

/**
 * @brief Motor control pin.
 *
 * In this project, motor is controlled through an optocoupler
 * connected to PINC3.
 */
#define MOTOR_PIN              DIO_PINC4

/**
 * @brief Motor active voltage.
 *
 * Use HIGH if the optocoupler input turns ON when PINC3 is HIGH.
 * Use LOW  if the optocoupler input turns ON when PINC3 is LOW.
 */
#define MOTOR_ACTIVE_STATE     HIGH

/**
 * @brief Motor inactive voltage.
 */
#define MOTOR_INACTIVE_STATE   LOW

#endif /* MOTOR_CFG_H_ */