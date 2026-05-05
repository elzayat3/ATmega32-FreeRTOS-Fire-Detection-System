#ifndef LM35_CFG_H_
#define LM35_CFG_H_

#include "ADC_Int.h"

/**
 * @file    LM35_Cfg.h
 * @author  Abdelrahman Elzayat
 * @brief   Configuration file for LM35 temperature sensor driver
 */

/**
 * @brief ADC channel connected to LM35 output pin.
 *
 * In this project:
 * LM35 output is connected to ADC0 / PA0.
 */
#define LM35_ADC_CHANNEL       CH_0

/**
 * @brief ADC reference voltage in millivolts.
 *
 * This value must match the ADC reference used in ADC_Init().
 *
 * If ADC_Init(VREF_VCC, ...), use 5000UL.
 * If ADC_Init(VREF_256, ...), use 2560UL.
 */
#define LM35_ADC_REF_MV        5000UL


#endif /* LM35_CFG_H_ */