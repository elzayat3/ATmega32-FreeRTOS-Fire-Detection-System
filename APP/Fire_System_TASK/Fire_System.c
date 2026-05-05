#include "StdTypes.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"
#include "Fire_System.h"
#include "Fire_System_Cfg.h"
#include "Sensor_Tasks.h"
#include "Motor_Int.h"
#include "LEDS_Int.h"
#include "BUZZER_Int.h"
#include "KeyPad_Int.h"
#include "LCD_Int.h"


static void NORMAL_state(u16 temp);
static void HEAT_state(u16 temp,u16 smoke);
static void FIRE_state(u16 temp,u16 smoke);

static void Fire_System_ResetToNormal(void);


static volatile state_t state=NORMAL;

static volatile u8 reset_request = 0u;
static volatile u8 flag = 0u;

static xSemaphoreHandle LCD_ResourceMutex = NULLPTR;

static volatile u16 temp=0;
static volatile u16 smoke=0;

error_t Fire_System_Init(void)
{
	error_t status = OK;

	LCD_ResourceMutex = xSemaphoreCreateMutex();

	if(LCD_ResourceMutex == NULLPTR)
	{
		status = NOK;
	}

	return status;
}
void Fire_System_MainTask(void*pv)
{
	(void)pv;
	 state_t local_state;
	 u16 local_temp;
	 u16 local_smoke;
	while(1)
	{
		taskENTER_CRITICAL();
		local_state = state;
		local_temp  = temp;
		local_smoke = smoke;
		taskEXIT_CRITICAL();
		switch(local_state)
		{
			case NORMAL:
			NORMAL_state(local_temp);
			break;
			case HEAT:
			HEAT_state(local_temp,local_smoke);
			break;
			case FIRE:
			FIRE_state(local_temp,local_smoke);
			break;
			default:
			NORMAL_state(local_temp);
			break;	
		}
		vTaskDelay(MS_TO_TICKS(MAIN_TASK_PERIOD_MS));
	}
}

void Fire_System_CheckStateTask(void *pvParameters)
{
	(void)pvParameters;

	u16 local_temp = 0u;
	u16 local_smoke = 0u;
	state_t local_state = NORMAL;
	u8 local_reset = 0u;

	while(1)
	{
		local_reset = 0u;

		local_temp = LM35_GetFilteredValue();
		local_smoke = Smoke_GetFilteredValue();

		taskENTER_CRITICAL();

		if(reset_request == 1u)
		{
			reset_request = 0u;
			local_reset = 1u;

			state = NORMAL;
			flag = 0u;
			temp = local_temp;
			smoke = 0u;

			local_state = NORMAL;
		}
		else
		{
			local_state = state;
		}

		taskEXIT_CRITICAL();

		if(local_reset == 0u)
		{
			if(local_state != FIRE)
			{
				if(local_temp >= 50u)
				{
					local_state = HEAT;
					flag = 1u;
				}
				else if((local_temp < 50u) && (local_temp >= 45u))
				{
					if(flag == 1u)
					{
						local_state = HEAT;
					}
					else
					{
						local_state = NORMAL;
					}
				}
				else
				{
					local_state = NORMAL;
					flag = 0u;
				}

				if((local_state == HEAT) && (local_smoke >= 60u))
				{
					local_state = FIRE;
				}
			}
			else
			{
				/* Stay in FIRE state */
			}

			taskENTER_CRITICAL();
			temp = local_temp;
			smoke = local_smoke;
			state = local_state;
			taskEXIT_CRITICAL();
		}
		else
		{
			/* Reset done, skip decision for this cycle */
		}

		vTaskDelay(MS_TO_TICKS(CHECK_TASK_PERIOD_MS));
	}
}
void Fire_System_KeypadTask(void *pvParameters)
{
	(void)pvParameters;

	static const u8 password[FIRE_PASSWORD_LENGTH] = FIRE_KEYPAD_PASSWORD_VALUE;

	u8 key = KEYPAD_NO_KEY;
	u8 last_key = KEYPAD_NO_KEY;
	u8 password_index = 0u;

	while(1)
	{
		if(Fire_System_GetState() == FIRE)
		{
			key = KEYPAD_GetKey();

			if((key != KEYPAD_NO_KEY) && (last_key == KEYPAD_NO_KEY))
			{
				if(key == FIRE_KEYPAD_CLEAR_KEY)
				{
					password_index = 0u;
				}
				else if(key == password[password_index])
				{
					password_index++;

					if(password_index >= FIRE_PASSWORD_LENGTH)
					{
						Fire_System_ResetToNormal();
						password_index = 0u;
					}
					else
					{
						/* Wait for next key */
					}
				}
				else
				{
					password_index = 0u;
				}
			}
			else
			{
				/* No new key */
			}

			last_key = key;
		}
		else
		{
			password_index = 0u;
			last_key = KEYPAD_NO_KEY;
		}

		vTaskDelay(MS_TO_TICKS(FIRE_KEYPAD_TASK_PERIOD_MS));
	}
}


static void NORMAL_state(u16 temp)
{
	if (xSemaphoreTake(LCD_ResourceMutex, portMAX_DELAY) == pdPASS)
	{
		RED_LED_Off();
		YELLOW_LED_Off();
		MOTOR_Off();
		BUZZER_Off();
		LCD_SetCursor(0,5);
		LCD_WriteString("NORMAL    ");
		LCD_SetCursor(1,0);
		LCD_WriteString("T=");
		LCD_WriteNumber(temp);
		LCD_WriteString("                    ");
		xSemaphoreGive(LCD_ResourceMutex);
	}
	else{;}
			
}

static void HEAT_state(u16 temp,u16 smoke)
{
	if (xSemaphoreTake(LCD_ResourceMutex, portMAX_DELAY) == pdPASS)
	{
		RED_LED_Off();
		YELLOW_LED_On();
		MOTOR_Off();
		BUZZER_Off();
		LCD_SetCursor(0,5);
		LCD_WriteString("HEAT     ");
		LCD_SetCursor(1,0);
		LCD_WriteString("T=");
		LCD_WriteNumber(temp);
	    LCD_WriteString(" S=");
		LCD_WriteNumber(smoke);
		LCD_WriteString("%  ");
		xSemaphoreGive(LCD_ResourceMutex);
				
	}
	else{;}
		
}


static void FIRE_state(u16 temp,u16 smoke)
{
	if (xSemaphoreTake(LCD_ResourceMutex, portMAX_DELAY) == pdPASS)
	{
		RED_LED_On();
		YELLOW_LED_Off();
		MOTOR_On();
		BUZZER_On();
		LCD_SetCursor(0,5);
		LCD_WriteString("FIRE    ");
		LCD_SetCursor(1,0);
		LCD_WriteString("T=");
		LCD_WriteNumber(temp);
		LCD_WriteString(" S=");
		LCD_WriteNumber(smoke);
		LCD_WriteString("%   ");
		xSemaphoreGive(LCD_ResourceMutex);
				
	}
	else{;}	
}
state_t Fire_System_GetState(void)
{
	state_t local_state;

	taskENTER_CRITICAL();
	local_state = state;
	taskEXIT_CRITICAL();

	return local_state;
}
static void Fire_System_ResetToNormal(void)
{
	taskENTER_CRITICAL();
	reset_request = 1u;
	taskEXIT_CRITICAL();
}
