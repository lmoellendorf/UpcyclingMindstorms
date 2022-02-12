/**
 * @copyright Lars Möllendorf
 * @file
 * @author Lars Möllendorf <lars@moellendorf.eu>
 * @brief Mindsensors LineLeader V2 for Arduino
 *
 * @details
 */

#include "LmMsLineLeaderV2.h"
#include <Wire.h>
#include <Arduino.h>


enum defaults {
	MLLV2_ADDR = 0x1,
};

enum registers {
	MLLV2_FW_VERS = 0x00,
	MLLV2_FW_VEND = 0x08,
	MLLV2_FW_DEV  = 0x10,
	MLLV2_AVG     = 0x43,
};

MsLineLeaderV2::MsLineLeaderV2(void)
{
	addr = MLLV2_ADDR;
	Wire.begin();
}

int MsLineLeaderV2::I2cRead(int reg, char *val, size_t len)
{
	if (!val || !len)
		return -1;

	/* set register pointer */
	Wire.beginTransmission(byte(addr));
	Wire.write(byte(reg));
	Wire.endTransmission();

	/* request bytes */
	Wire.requestFrom(addr, len - 1);

	/*  receive reading from sensor */
	if (len - 1 <= Wire.available())  {
		for (int i = 0; i < len - 1; i++)
			val[i] = Wire.read();
	}

	val[len - 1] = 0;
	return 0;
}

int MsLineLeaderV2::GetFwVersion(char *version, size_t len)
{
	len = len > 9 ? 9 : len;
	return I2cRead(MLLV2_FW_VERS, version, len);
}

int MsLineLeaderV2::GetFwVendor(char *vendor, size_t len)
{
	len = len > 9 ? 9 : len;
	return I2cRead(MLLV2_FW_VEND, vendor, len);
}

int MsLineLeaderV2::GetFwDevice(char *device, size_t len)
{
	len = len > 9 ? 9 : len;
	return I2cRead(MLLV2_FW_DEV, device, len);
}

int MsLineLeaderV2::GetAvg()
{
}
