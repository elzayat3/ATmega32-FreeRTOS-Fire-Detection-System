#include "StdTypes.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"
#include "LM35_Int.h"
#include "LM35_Cfg.h"

#include "Smoke_Int.h"
#include "Smoke_Cfg.h"

#include "Sensor_Tasks.h"
#include "Sensor_Tasks_Cfg.h"
#include "Fire_System.h"



#include "ADC_Int.h"



/* =========================
 * Shared sensor values
 * ========================= */

static u16 LM35_UnfilteredValue = 0u;
static u16 LM35_FilteredValue   = 0u;

static u16 Smoke_UnfilteredValue = 0u;
static u16 Smoke_FilteredValue   = 0u;

static void ADC_Callback(void);
static xSemaphoreHandle ADC_ResourceMutex = NULLPTR;
static xSemaphoreHandle ADC_DoneSemaphore = NULLPTR;


/* =========================
 * SENSOR INIT
 * ========================= */

error_t Sensor_Init(void)
{
	error_t status=OK;
	
	ADC_ResourceMutex = xSemaphoreCreateMutex();

	vSemaphoreCreateBinary(ADC_DoneSemaphore);
	
	if (ADC_DoneSemaphore != NULLPTR)
	{
		(void)xSemaphoreTake(ADC_DoneSemaphore, 0);
	}
	else
	{
		status=NULL_PTR;
	}
	if ((ADC_ResourceMutex == NULLPTR) || (ADC_DoneSemaphore == NULLPTR))
	{
		status = NULL_PTR;
	}
	else{;}
	ADC_SetCallBack(ADC_Callback);
	ADC_InterruptEnable();
	return status;
}

/* =========================
 * LM35 Task
 * ========================= */

void LM35_Task(void *pvParameters)
{
	u16 adc_value = 0u;
	u16 unfiltered_value = 0u;
	u16 filtered_value = 0u;
	u32 sum = 0u;
	u8 j = 0u;
	bool_t read_ok = FALSE;

	static u16 filter_arr[LM35_SAMPLE_SIZE] = {0u};
	static u8 i = 0u;

	(void)pvParameters;

	while (1)
	{
		read_ok = FALSE;

		if (xSemaphoreTake(ADC_ResourceMutex, portMAX_DELAY) == pdPASS)
		{
			(void)xSemaphoreTake(ADC_DoneSemaphore, 0);

			if (ADC_StartConversion(LM35_ADC_CHANNEL) == OK)
			{
				if (xSemaphoreTake(ADC_DoneSemaphore, portMAX_DELAY) == pdPASS)
				{
					adc_value = ADC_GetReadNoBlock();
					read_ok = TRUE;
				}
			}

			xSemaphoreGive(ADC_ResourceMutex);
		}
		else
		{
			/* ADC resource take failed */
		}

		if (read_ok == TRUE)
		{
			unfiltered_value = LM35_ConvertAdcToTemp(adc_value);

			if (i >= LM35_SAMPLE_SIZE)
			{
				i = 0u;
			}
			else
			{
				/* Do nothing */
			}

			filter_arr[i] = unfiltered_value;
			i++;

			sum = 0u;

			for (j = 0u; j < LM35_SAMPLE_SIZE; j++)
			{
				sum += filter_arr[j];
			}

			filtered_value = (u16)(sum / LM35_SAMPLE_SIZE);

			taskENTER_CRITICAL();
			LM35_UnfilteredValue = unfiltered_value;
			LM35_FilteredValue = filtered_value;
			taskEXIT_CRITICAL();
		}
		else
		{
			/* Do not update values if read failed */
		}

		vTaskDelay(MS_TO_TICKS(SENSOR_TASK_PERIOD_MS));
		
	}
}

/* =========================
 * Smoke Task
 * ========================= */

void Smoke_Task(void *pvParameters)
{
	u16 adc_value = 0u;
	u16 unfiltered_value = 0u;
	u16 filtered_value = 0u;
	u32 sum = 0u;
	u8 j = 0u;
	bool_t read_ok = FALSE;

	static u16 filter_arr[SMOKE_SAMPLE_SIZE] = {0u};
	static u8 i = 0u;

	(void)pvParameters;

	while (1)
	{
		
		if( Fire_System_GetState() != NORMAL)
		{
			read_ok = FALSE;

			if (xSemaphoreTake(ADC_ResourceMutex, portMAX_DELAY) == pdPASS)
			{
				(void)xSemaphoreTake(ADC_DoneSemaphore, 0);
				
				if (ADC_StartConversion(SMOKE_ADC_CHANNEL) == OK)
				{
					if (xSemaphoreTake(ADC_DoneSemaphore, portMAX_DELAY) == pdPASS)
					{
						adc_value = ADC_GetReadNoBlock();
						read_ok = TRUE;
					}
					else
					{
						/* ADC conversion wait failed */
					}
				}
				else
				{
					/* ADC start conversion failed */
				}

				xSemaphoreGive(ADC_ResourceMutex);
			}
			else
			{
				/* ADC resource take failed */
			}

			if (read_ok == TRUE)
			{
				unfiltered_value = Smoke_ConvertAdcToPercent(adc_value);

				if (i >= SMOKE_SAMPLE_SIZE)
				{
					i = 0u;
				}
				else
				{
					/* Do nothing */
				}

				filter_arr[i] = unfiltered_value;
				i++;

				sum = 0u;

				for (j = 0u; j < SMOKE_SAMPLE_SIZE; j++)
				{
					sum += filter_arr[j];
				}

				filtered_value = (u16)(sum / SMOKE_SAMPLE_SIZE);

				taskENTER_CRITICAL();
				Smoke_UnfilteredValue = unfiltered_value;
				Smoke_FilteredValue = filtered_value;
				taskEXIT_CRITICAL();
			}
			else
			{
				/* Do not update values if read failed */
			}
		}
		else{
			i = 0u;

			for (j = 0u; j < SMOKE_SAMPLE_SIZE; j++)
			{
				filter_arr[j] = 0u;
			}

			taskENTER_CRITICAL();
			Smoke_UnfilteredValue = 0u;
			Smoke_FilteredValue = 0u;
			taskEXIT_CRITICAL();
		}

		vTaskDelay(MS_TO_TICKS(SENSOR_TASK_PERIOD_MS));
	}
}

/* =========================
 * Getters
 * ========================= */

u16 LM35_GetUnfilteredValue(void)
{
	u16 value = 0u;

	taskENTER_CRITICAL();
	value = LM35_UnfilteredValue;
	taskEXIT_CRITICAL();

	return value;
}

u16 LM35_GetFilteredValue(void)
{
	u16 value = 0u;

	taskENTER_CRITICAL();
	value = LM35_FilteredValue;
	taskEXIT_CRITICAL();

	return value;
}

u16 Smoke_GetUnfilteredValue(void)
{
	u16 value = 0u;

	taskENTER_CRITICAL();
	value = Smoke_UnfilteredValue;
	taskEXIT_CRITICAL();

	return value;
}

u16 Smoke_GetFilteredValue(void)
{
	u16 value = 0u;

	taskENTER_CRITICAL();
	value = Smoke_FilteredValue;
	taskEXIT_CRITICAL();

	return value;
}
static void ADC_Callback(void)
{
	(void)xSemaphoreGiveFromISR(
	ADC_DoneSemaphore,
	NULLPTR
	);
}