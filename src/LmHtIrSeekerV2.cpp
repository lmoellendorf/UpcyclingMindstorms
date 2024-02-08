/**
 * @copyright Lars Möllendorf
 * @file
 * @author Lars Möllendorf <lars@moellendorf.eu>
 * @brief Mindsensors LineLeader V2 for Arduino
 *
 * @details
 */

#include "LmHtIrSeekerV2.h"
#include <Arduino.h>

enum defaults {
	HISV2_ADDR = 0x8,
};

enum registers {
	HISV2_REG_DC_DIR = 0x42,
	HISV2_REG_DC_VAL = 0x43,
	HISV2_REG_DC_AVG = 0x48,
	HISV2_REG_AC_DIR = 0x49,
	HISV2_REG_AC_VAL = 0x4A,
};

HtIrSeekerV2::HtIrSeekerV2(int pin, int mode): i2c(HISV2_ADDR)
{
	setMode(mode);
	pinMode(pin, OUTPUT);
	digitalWrite(pin, 1);
}

HtIrSeekerV2::HtIrSeekerV2(int mode): i2c(HISV2_ADDR)
{
	setMode(mode);
}

HtIrSeekerV2::HtIrSeekerV2(void): HtIrSeekerV2(A10, AC)
{
}

int HtIrSeekerV2::getVersion(char *version, size_t len)
{
	return i2c.getVersion(version, len);
}

int HtIrSeekerV2::getVendorId(char *vendor, size_t len)
{
	return i2c.getVendorId(vendor, len);
}

int HtIrSeekerV2::getDeviceId(char *device, size_t len)
{
	return i2c.getDeviceId(device, len);
}

bool HtIrSeekerV2::hasDirection(void)
{
	return !!getDirection(mode);
}

int HtIrSeekerV2::getDirection(void)
{
	return getDirection(mode);
}

int HtIrSeekerV2::getDirection(int mode)
{
	switch (switchMode(mode)) {
	case DC:
		return i2c.readByte(HISV2_REG_DC_DIR);

	case AC:
		return i2c.readByte(HISV2_REG_AC_DIR);
	}

	return -1;
}

int HtIrSeekerV2::getDirection(bool block)
{
	return getDirection(mode, block);
}

int HtIrSeekerV2::getDirection(int mode, bool block)
{
	int dir = -1;

	do {
		dir = getDirection(mode);

		if (dir)
			break;
	} while (block);

	return dir;
}

int HtIrSeekerV2::getAngle(void)
{
	return getAngle(mode);
}

int HtIrSeekerV2::getAngle(int mode)
{
	return getAngle(mode, false);
}

int HtIrSeekerV2::getAngle(bool block)
{
	return getAngle(mode, block);
}

int HtIrSeekerV2::getAngle(int mode, bool block)
{
	int dir;

	dir = getDirection(mode, block);

	if (dir < 0)
		return dir;

	return (dir - 5) * 30;
}

int HtIrSeekerV2::getSensorValue(unsigned int id)
{
	return getSensorValue(id, mode);
}

int HtIrSeekerV2::getSensorValue(unsigned int id, int mode)
{
	if (id > 4)
		return -1;

	switch (switchMode(mode)) {
	case DC:
		return i2c.readByte(HISV2_REG_DC_VAL + id);

	case AC:
		return i2c.readByte(HISV2_REG_AC_VAL + id);
	}

	return -1;
}

int HtIrSeekerV2::getSensorValues(int values[], size_t n_values)
{
	return getSensorValues(values, n_values, mode);
}

int HtIrSeekerV2::getSensorValues(int values[], size_t n_values, int mode)
{
	if (!values)
		return -1;

	for (int id = 0; id < n_values; id++)
		values[id] = getSensorValue(id % 5, mode);

	return 0;
}

int HtIrSeekerV2::getAverage(void)
{
	return i2c.readByte(HISV2_REG_DC_AVG);
}

int HtIrSeekerV2::switchMode(int mode)
{
	switch (mode) {
	case AC:

	/* fall through */
	case DC:
		return mode;

	default:
		return AC;
	}
}

void HtIrSeekerV2::setMode(int mode)
{
	HtIrSeekerV2::mode = switchMode(mode);
}
