/*
 * Fire_System_Cfg.h
 *
 * Created: 5/3/2026 4:06:27 PM
 *  Author: Abdelrahman Elzayat
 */ 


#ifndef FIRE_SYSTEM_CFG_H_
#define FIRE_SYSTEM_CFG_H_

#define MS_TO_TICKS(ms)            ((portTickType)((ms) / portTICK_RATE_MS))


#define  CHECK_TASK_PERIOD_MS          500U

#define  MAIN_TASK_PERIOD_MS         500U

#define FIRE_PASSWORD_LENGTH             4u
#define FIRE_KEYPAD_TASK_PERIOD_MS       50u

#define FIRE_KEYPAD_CLEAR_KEY            'D'
#define FIRE_KEYPAD_PASSWORD_VALUE       { '1', '2', '3', '4' }



#endif /* FIRE_SYSTEM_CFG_H_ */