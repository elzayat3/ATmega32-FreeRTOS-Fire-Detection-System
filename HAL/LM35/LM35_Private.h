#ifndef LM35_PRIVATE_H_
#define LM35_PRIVATE_H_

/**
 * @file    LM35_Private.h
 * @author  Abdelrahman Elzayat
 * @brief   Private definitions for LM35 driver
 */

/**
 * @brief LM35 output voltage scale.
 *
 * LM35 gives 10 mV for each 1 Celsius degree.
 */
#define LM35_MV_PER_CELSIUS    10UL

/**
 * @brief Maximum ADC digital value for 10-bit ADC.
 *
 * ATmega32 ADC result range is 0 to 1023.
 */
#define LM35_ADC_MAX_VALUE     1023UL

#endif /* LM35_PRIVATE_H_ */