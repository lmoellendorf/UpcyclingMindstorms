/**
 * @copyright Lars Möllendorf
 * @file
 * @author Lars Möllendorf <lars@moellendorf.eu>
 * @brief Mindsensors LineLeader V2 for Arduino
 *
 * @details
 */

#include "LmHtIrSeekerV2.h"

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


HtIrSeekerV2::HtIrSeekerV2(enum Mode mode): i2c(HISV2_ADDR)
{
	HtIrSeekerV2::mode = mode;
}

HtIrSeekerV2::HtIrSeekerV2(void)
{
	HtIrSeekerV2(Mode::AC);
}

int HtIrSeekerV2::GetVersion(char *version, size_t len)
{
	return i2c.GetVersion(version, len);
}

int HtIrSeekerV2::GetVendorId(char *vendor, size_t len)
{
	return i2c.GetVendorId(vendor, len);
}

int HtIrSeekerV2::GetDeviceId(char *device, size_t len)
{
	return i2c.GetDeviceId(device, len);
}

bool HtIrSeekerV2::HasDirection(void)
{
	return !!GetDirection(mode);
}

int HtIrSeekerV2::GetDirection(void)
{
	return GetDirection(mode);
}

int HtIrSeekerV2::GetDirection(enum Mode mode)
{
	switch (mode) {
	case DC:
		return i2c.ReadByte(HISV2_REG_DC_DIR);

	case AC:
		return i2c.ReadByte(HISV2_REG_AC_DIR);
	}
}

int HtIrSeekerV2::GetDirection(bool block)
{
	return GetDirection(mode, block);
}

int HtIrSeekerV2::GetDirection(enum Mode mode, bool block)
{
	int dir = -1;

	do {
		dir = GetDirection(mode);

		if (dir)
			break;
	} while (block);

	return dir;
}

int HtIrSeekerV2::GetAngle(void)
{
	return GetAngle(mode);
}

int HtIrSeekerV2::GetAngle(enum Mode mode)
{
	return GetAngle(mode, false);
}

int HtIrSeekerV2::GetAngle(bool block)
{
	return GetAngle(mode, block);
}

int HtIrSeekerV2::GetAngle(enum Mode mode, bool block)
{
	int dir;

	dir = GetDirection(mode, block);

	if (dir < 0)
		return dir;

	return (dir - 5) * 30;
}

int HtIrSeekerV2::GetSensorValue(unsigned int id)
{
	return GetSensorValue(id, mode);
}

int HtIrSeekerV2::GetSensorValue(unsigned int id, enum Mode mode)
{
	if (id > 4)
		return -1;

	switch (mode) {
	case DC:
		return i2c.ReadByte(HISV2_REG_DC_VAL + id);

	case AC:
		return i2c.ReadByte(HISV2_REG_AC_VAL + id);
	}
}

int HtIrSeekerV2::GetSensorValues(int values[], size_t n_values)
{
	return GetSensorValues(values, n_values, mode);
}

int HtIrSeekerV2::GetSensorValues(int values[], size_t n_values, enum Mode mode)
{
	if (!values)
		return -1;

	for (int id = 0; id < n_values; id++)
		values[id] = GetSensorValue(id % 5, mode);

	return 0;
}

int HtIrSeekerV2::GetAverage(void)
{
	return i2c.ReadByte(HISV2_REG_DC_AVG);
}
