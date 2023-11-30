/**
 * @copyright Lars Möllendorf
 * @file
 * @author Lars Möllendorf <lars@moellendorf.eu>
 * @brief Mindsensors Line Sensor Array for Arduino
 *
 * @details
 */

#include "LmMsLineSensorArray.h"
#include <Arduino.h>
#include <string.h>

enum registers {
	MS_LSA_CALIB   = 0x42,
	MS_LSA_W_LIMIT = 0x4A,
	MS_LSA_B_LIMIT = 0x52,
	MS_LSA_W_CALIB = 0x5A,
	MS_LSA_B_CALIB = 0x62,
	MS_LSA_VOLTAGE = 0x6A,
};

MsLineSensorArray::MsLineSensorArray(void)
{
}

int MsLineSensorArray::calibrateWhite(void)
{
	return MsI2cSensor::writeCmd('W');
}

int MsLineSensorArray::calibrateBlack(void)
{
	return MsI2cSensor::writeCmd('B');
}

int MsLineSensorArray::getUpTo8Bytes(int reg, char *readings, size_t len)
{
	len = len > 8 ? 8 : len;
	return I2C::read(reg, readings, len);
}

int MsLineSensorArray::getUpTo8Words(int reg, uint16_t *readings, size_t len)
{
	int swap, ret;

	len = len > 8 ? 8 : len;
	ret = I2C::read(reg, (char *)readings, len * 2);

	if (ret < 0)
		return ret;

	/*
	 * swap byte - it is assumed that int is 16bit
	 */
	for (int i = 0; i < len; i++) {
		swap        = readings[i];
		readings[i] = readings[i] >> 8;
		readings[i] |= swap << 8;
	}

	return 0;
}

int MsLineSensorArray::getCalibrated(char *readings, size_t len)
{
	return getUpTo8Bytes(MS_LSA_CALIB, readings, len);
}

int MsLineSensorArray::getWhiteLimit(char *values, size_t len)
{
	return getUpTo8Bytes(MS_LSA_CALIB, values, len);
}

int MsLineSensorArray::getBlackLimit(char *values, size_t len)
{
	return getUpTo8Bytes(MS_LSA_B_LIMIT, values, len);
}

int MsLineSensorArray::getWhiteCalibration(char *values, size_t len)
{
	return getUpTo8Bytes(MS_LSA_W_CALIB, values, len);
}

int MsLineSensorArray::getBlackCalibration(char *values, size_t len)
{
	return getUpTo8Bytes(MS_LSA_B_CALIB, values, len);
}

int MsLineSensorArray::getVoltage(uint16_t *readings, size_t len)
{
	return getUpTo8Words(MS_LSA_VOLTAGE, readings, len);
}

int MsLineSensorArray::getResultNAverage(int *result, int *average)
{
	const size_t n = 8;
	char calib[n] = { 0 };
	int count = 0;
	int ret;

	if (!result && !average)
		return -1;

	ret = getCalibrated(calib, n);

	if (ret < 0)
		return ret;

	for (int i = 0; i < n; i++) {
		if (calib[i] < 50) {
			if (result)
				*result |= (1 << i);

			if (average)
				*average += ((i + 1) * 10);

			count++;
		}
	}

	if (average && count)
		*average /= count;

	return 0;
}

int MsLineSensorArray::getAverage(void)
{
	int ret, average = 0;

	ret = getResultNAverage(NULL, &average);

	if (ret < 0)
		return 0;

	return average;
}

int MsLineSensorArray::getResult(void)
{
	int ret, result = 0;

	ret = getResultNAverage(&result, NULL);

	if (ret < 0)
		return 0;

	return result;
}
