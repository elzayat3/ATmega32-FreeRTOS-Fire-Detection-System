#ifndef SMOKE_CFG_H_
#define SMOKE_CFG_H_

#include "ADC_Int.h"

/**
 * @file    Smoke_Cfg.h
 * @author  Abdelrahman Elzayat
 * @brief   Configuration file for smoke sensor driver
 */

/**
 * @brief ADC channel connected to smoke sensor analog output.
 *
 * In this project:
 * Smoke sensor output is connected to ADC1 / PA1.
 */
#define SMOKE_ADC_CHANNEL    CH_7

#endif /* SMOKE_CFG_H_ */