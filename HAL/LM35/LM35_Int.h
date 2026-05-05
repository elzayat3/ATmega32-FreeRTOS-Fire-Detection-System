#ifndef LM35_INT_H_
#define LM35_INT_H_

#include "StdTypes.h"



/**
 * @file    LM35_Int.h
 * @author  Abdelrahman Elzayat
 * @brief   Interface for LM35 temperature sensor driver
 *
 * @details
 * This driver is a HAL driver for the LM35 analog temperature sensor.
 *
 * It does not start ADC conversion by itself.
 * It only converts ADC readings or voltage values into temperature.
 */

/**
 * @brief Converts ADC digital value to temperature in Celsius.
 *
 * @param adc_value ADC digital reading, expected range: 0 to 1023.
 *
 * @return Temperature value in Celsius.
 */
u16 LM35_ConvertAdcToTemp(u16 adc_value);

/**
 * @brief Converts voltage in millivolts to temperature in Celsius.
 *
 * @param volt_mv LM35 output voltage in millivolts.
 *
 * @return Temperature value in Celsius.
 */
u16 LM35_ConvertMilliVoltToTemp(u16 volt_mv);

#endif /* LM35_INT_H_ */