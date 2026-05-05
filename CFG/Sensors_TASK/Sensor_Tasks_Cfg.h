#ifndef SENSOR_TASKS_CFG_H_
#define SENSOR_TASKS_CFG_H_

/**
 * @file    Sensor_Tasks_Cfg.h
 * @author  Abdelrahman Elzayat
 * @brief   Configuration file for sensor tasks
 */

/**
 * @brief Sensor tasks period in milliseconds.
 *
 * Both LM35_Task and Smoke_Task will run every 500ms.
 */
#define SENSOR_TASK_PERIOD_MS      500u

/**
 * @brief Number of samples used by LM35 mean filter.
 */
#define LM35_SAMPLE_SIZE           10u

/**
 * @brief Number of samples used by smoke sensor mean filter.
 */
#define SMOKE_SAMPLE_SIZE          10u

/**
 * @brief Converts milliseconds to FreeRTOS ticks.
 *
 * This project uses FreeRTOS V7 style timing based on portTICK_RATE_MS.
 */
#define MS_TO_TICKS(ms)            ((portTickType)((ms) / portTICK_RATE_MS))

#endif /* SENSOR_TASKS_CFG_H_ */