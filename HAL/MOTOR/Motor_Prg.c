#include "StdTypes.h"

#include "DIO_Int.h"

#include "MOTOR_Int.h"
#include "MOTOR_Cfg.h"

void MOTOR_On(void)
{
	DIO_WritePin(MOTOR_PIN, MOTOR_ACTIVE_STATE);
}

void MOTOR_Off(void)
{
	DIO_WritePin(MOTOR_PIN, MOTOR_INACTIVE_STATE);
}