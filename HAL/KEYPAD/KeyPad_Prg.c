#include "StdTypes.h"

#include "DIO_Int.h"

#include "KeyPad_Int.h"
#include "KeyPad_Cfg.h"
#include "KeyPad_Private.h"

void KEYPAD_Init(void)
{
	u8 r = 0u;

	for (r = 0u; r < ROWS; r++)
	{
		DIO_WritePin(PinOut[r], HIGH);
	}
}

u8 KEYPAD_GetKey(void)
{
	u8 r = 0u;
	u8 c = 0u;
	u8 key = KEYPAD_NO_KEY;

	for (r = 0u; r < ROWS; r++)
	{
		DIO_WritePin(PinOut[r], LOW);

		for (c = 0u; c < COLS; c++)
		{
			if (DIO_ReadPin(PinIn[c]) == LOW)
			{
				key = KeysArr[r][c];

			}
			else
			{
				/* Do nothing */
			}
		}

		DIO_WritePin(PinOut[r], HIGH);

		if (key != KEYPAD_NO_KEY)
		{
			break;
		}
		else
		{
			/* Continue scanning */
		}
	}

	return key;
}