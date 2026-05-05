#include "StdTypes.h"

#include "Smoke_Int.h"
#include "Smoke_Private.h"
#include "Smoke_Cfg.h"

u8 Smoke_ConvertAdcToPercent(u16 adc_value)
{
	u32 percent = 0u;

	if (adc_value > SMOKE_ADC_MAX_VALUE)
	{
		adc_value = SMOKE_ADC_MAX_VALUE;
	}
	else
	{
		/* Do nothing */
	}

	percent = ((u32)adc_value * SMOKE_PERCENT_MAX) / SMOKE_ADC_MAX_VALUE;

	return (u8)percent;
}