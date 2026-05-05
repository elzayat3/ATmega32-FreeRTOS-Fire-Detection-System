#include "StdTypes.h"

#include "DIO_Int.h"

#include "LEDS_Int.h"
#include "LEDS_Cfg.h"


void RED_LED_On(void)
{
	DIO_WritePin(RED_LED_PIN, RED_LED_ACTIVE_STATE);
}

void RED_LED_Off(void)
{
	DIO_WritePin(RED_LED_PIN, RED_LED_INACTIVE_STATE);
}

void YELLOW_LED_On(void)
{
	DIO_WritePin(YELLOW_LED_PIN, YELLOW_LED_ACTIVE_STATE);
}

void YELLOW_LED_Off(void)
{
	DIO_WritePin(YELLOW_LED_PIN, YELLOW_LED_INACTIVE_STATE);
}