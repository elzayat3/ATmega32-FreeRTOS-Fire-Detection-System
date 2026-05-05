#ifndef SMOKE_INT_H_
#define SMOKE_INT_H_

#include "StdTypes.h"

/**
 * @file    Smoke_Int.h
 * @author  Abdelrahman Elzayat
 * @brief   Interface for analog smoke sensor driver
 *
 * @details
 * This driver converts smoke sensor ADC readings into percentage.
 *
 * It does not start ADC conversion by itself.
 * ADC reading is handled by MCAL or Service Layer.
 */

/**
 * @brief Converts ADC digital value to smoke percentage.
 *
 * @param adc_value ADC digital reading, expected range: 0 to 1023.
 *
 * @return Smoke level percentage from 0 to 100.
 */
u8 Smoke_ConvertAdcToPercent(u16 adc_value);

#endif /* SMOKE_INT_H_ */