#ifndef APP_CFG_H_
#define APP_CFG_H_

/**
 * @file    App_Cfg.h
 * @author  Abdelrahman Elzayat
 * @brief   Application configuration file
 */

/* =========================
 * Task Stack Sizes
 * ========================= */

#define KEY_TASK_STACK      100u
#define CHECK_TASK_STACK    120u
#define FIRE_TASK_STACK     150u
#define LM35_TASK_STACK     150u
#define SMOKE_TASK_STACK    150u

/* =========================
 * Task Priorities
 * ========================= */

#define KEY_TASK_PRIORITY      5u
#define LM35_TASK_PRIORITY     4u
#define SMOKE_TASK_PRIORITY    4u
#define CHECK_TASK_PRIORITY    3u
#define FIRE_TASK_PRIORITY     2u

#endif /* APP_CFG_H_ */