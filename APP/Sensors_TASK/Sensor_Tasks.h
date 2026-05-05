#ifndef SENSOR_TASKS_H_
#define SENSOR_TASKS_H_

/**
 * @file    Sensor_Tasks.h
 * @author  Abdelrahman Elzayat
 * @brief   Application sensor tasks interface
 */

error_t Sensor_Init(void);

/**
 * @brief LM35 sensor task.
 *
 * @details
 * Periodically reads LM35 every 500ms, writes unfiltered value
 * to mailbox, applies mean filter, then writes filtered value to mailbox.
 *
 * @param pvParameters FreeRTOS task parameter. Not used.
 */
void LM35_Task(void *pvParameters);

/**
 * @brief Smoke sensor task.
 *
 * @details
 * Periodically reads smoke sensor every 500ms, writes unfiltered value
 * to mailbox, applies mean filter, then writes filtered value to mailbox.
 *
 * @param pvParameters FreeRTOS task parameter. Not used.
 */
void Smoke_Task(void *pvParameters);

/**
 * @brief Gets latest unfiltered LM35 value.
 *
 * @return Latest unfiltered temperature value.
 */
u16 LM35_GetUnfilteredValue(void);

/**
 * @brief Gets latest filtered LM35 value.
 *
 * @return Latest filtered temperature value.
 */
u16 LM35_GetFilteredValue(void);
/**
 * @brief Gets latest unfiltered smoke value.
 *
 * @return Latest unfiltered smoke percentage.
 */
u16 Smoke_GetUnfilteredValue(void);

/**
 * @brief Gets latest filtered smoke value.
 *
 * @return Latest filtered smoke percentage.
 */
u16 Smoke_GetFilteredValue(void);

#endif /* SENSOR_TASKS_H_ */