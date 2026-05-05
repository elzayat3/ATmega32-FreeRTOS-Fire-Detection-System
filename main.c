#include "StdTypes.h"

#include "FreeRTOS.h"
#include "task.h"

#include "DIO_Int.h"
#include "ADC_Int.h"
#include "LCD_Int.h"
#include "KeyPad_Int.h"

#include "Sensor_Tasks.h"
#include "Fire_System.h"
#include "App_Cfg.h"


int main(void)
{
	DIO_Init();
	LCD_Init();
	ADC_Init(VREF_VCC, ADC_SCALER_64);
	KEYPAD_Init();

	if ((Sensor_Init() == OK) && (Fire_System_Init() == OK))
	{
		LCD_Clear();

		if (xTaskCreate(Fire_System_KeypadTask,(const signed char *)"KEY",KEY_TASK_STACK,NULLPTR,KEY_TASK_PRIORITY,NULLPTR) != pdPASS)
		{
			LCD_Clear();
			LCD_WriteString("KEY FAIL");
			while (1)
			{
			}
		}

		if (xTaskCreate(Fire_System_CheckStateTask,(const signed char *)"CHK",CHECK_TASK_STACK,NULLPTR,CHECK_TASK_PRIORITY,NULLPTR) != pdPASS)
		{
			LCD_Clear();
			LCD_WriteString("CHK FAIL");
			while (1)
			{
			}
		}

		if (xTaskCreate(Fire_System_MainTask,(const signed char *)"SYS",FIRE_TASK_STACK,NULLPTR,FIRE_TASK_PRIORITY,NULLPTR) != pdPASS)
		{
			LCD_Clear();
			LCD_WriteString("SYS FAIL");
			while (1)
			{
			}
		}

		if (xTaskCreate(LM35_Task,(const signed char *)"LM35",LM35_TASK_STACK,NULLPTR,LM35_TASK_PRIORITY,NULLPTR) != pdPASS)
		{
			LCD_Clear();
			LCD_WriteString("LM35 FAIL");
			while (1)
			{
			}
		}

		if (xTaskCreate(Smoke_Task,(const signed char *)"SMK",SMOKE_TASK_STACK,NULLPTR,SMOKE_TASK_PRIORITY,NULLPTR) != pdPASS)
		{
			LCD_Clear();
			LCD_WriteString("SMK FAIL");
			while (1)
			{
			}
		}

		vTaskStartScheduler();

		LCD_Clear();
		LCD_WriteString("SCH FAIL");
	}
	else
	{
		LCD_Clear();
		LCD_WriteString("INIT ERROR");
	}

	while (1)
	{
	}
}