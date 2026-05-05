#include "StdTypes.h"

#include "LM35_Int.h"
#include "LM35_Private.h"
#include "LM35_Cfg.h"

u16 LM35_ConvertAdcToTemp(u16 adc_value)
{
	u32 volt_mv = 0u;
	u32 temp_celsius = 0u;

	volt_mv = ((u32)adc_value * LM35_ADC_REF_MV) / LM35_ADC_MAX_VALUE;

	temp_celsius = volt_mv / LM35_MV_PER_CELSIUS;

	return (u16)temp_celsius;
}

u16 LM35_ConvertMilliVoltToTemp(u16 volt_mv)
{
	u16 temp_celsius = 0u;

	temp_celsius = (u16)((u32)volt_mv / LM35_MV_PER_CELSIUS);

	return temp_celsius;
}
