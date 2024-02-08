/**
 * @copyright Lars Möllendorf
 * @file
 * @author Lars Möllendorf <lars@moellendorf.eu>
 * @brief Mindsensors IR Thermometer for Arduino
 *
 * @details
 */

#include "LmMsIRThermometer.h"
#include <Arduino.h>
#include <string.h>

enum registers {
	MS_IRT_AMB_TEMP_C = 0x42,
	MS_IRT_TGT_TEMP_C = 0x44,
	MS_IRT_AMB_TEMP_F = 0x46,
	MS_IRT_TGT_TEMP_F = 0x48,
};

MsIRThermometer::MsIRThermometer(void)
{
	addr = 0x2A / 2;
}

float MsIRThermometer::getTemperature(int reg)
{
	uint16_t word;
	int ret;

	ret = I2C::readWord(&word, reg);

	if(ret < 0)
		return -1;

	return (float)word / 100.;
}

float MsIRThermometer::getAmbientTemperatureC(void)
{
	return getTemperature(MS_IRT_AMB_TEMP_C);
}

float MsIRThermometer::getTargetTemperatureC(void)
{
	return getTemperature(MS_IRT_TGT_TEMP_C);
}

float MsIRThermometer::getAmbientTemperatureF(void)
{
	return getTemperature(MS_IRT_AMB_TEMP_F);
}

float MsIRThermometer::getTargetTemperatureF(void)
{
	return getTemperature(MS_IRT_TGT_TEMP_F);
}
