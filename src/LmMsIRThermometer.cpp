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

float MsIRThermometer::getAmbientTemperatureC(void)
{
	return (float)I2C::readWord(MS_IRT_AMB_TEMP_C) / 100.;
}

float MsIRThermometer::getTargetTemperatureC(void)
{
	return (float)I2C::readWord(MS_IRT_TGT_TEMP_C) / 100.;
}

float MsIRThermometer::getAmbientTemperatureF(void)
{
	return (float)I2C::readWord(MS_IRT_AMB_TEMP_F) / 100.;
}

float MsIRThermometer::getTargetTemperatureF(void)
{
	return (float)I2C::readWord(MS_IRT_TGT_TEMP_F) / 100.;
}
