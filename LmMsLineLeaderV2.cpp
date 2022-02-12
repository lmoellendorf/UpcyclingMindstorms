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
	MLLV2_CMD     = 0x41,
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
	Wire.requestFrom(addr, len);

	/*  receive reading from sensor */
	if (len <= Wire.available())  {
		for (int i = 0; i < len; i++)
			val[i] = Wire.read();
	}

	return 0;
}

int MsLineLeaderV2::I2cReadStr(int reg, char *val, size_t len)
{
	if (!val || !len)
		return -1;

	val[len - 1] = '\0';
	return I2cRead(reg, val, len - 1);
}

int MsLineLeaderV2::I2cWrite(int reg, char *val, size_t len)
{
	if (!val || !len)
		return -1;

	/* set register pointer */
	Wire.beginTransmission(byte(addr));
	Wire.write(byte(reg));

	for (int i = 0; i < len; i++)
		Wire.write(val[i]);

	Wire.endTransmission();
	return 0;
}

int MsLineLeaderV2::GetFwVersion(char *version, size_t len)
{
	len = len > 9 ? 9 : len;
	return I2cReadStr(MLLV2_FW_VERS, version, len);
}

int MsLineLeaderV2::GetFwVendor(char *vendor, size_t len)
{
	len = len > 9 ? 9 : len;
	return I2cReadStr(MLLV2_FW_VEND, vendor, len);
}

int MsLineLeaderV2::GetFwDevice(char *device, size_t len)
{
	len = len > 9 ? 9 : len;
	return I2cReadStr(MLLV2_FW_DEV, device, len);
}

int MsLineLeaderV2::WriteCmd(char cmd)
{
	return I2cWrite(MLLV2_CMD, &cmd, 1);
}

int MsLineLeaderV2::CalibrateWhite(void)
{
	return WriteCmd('W');
}

int MsLineLeaderV2::CalibrateBlack(void)
{
	return WriteCmd('B');
}

int MsLineLeaderV2::PutToSleep(void)
{
	return WriteCmd('D');
}

int MsLineLeaderV2::WakeUp(void)
{
	return WriteCmd('P');
}

int MsLineLeaderV2::InvertColor(void)
{
	return WriteCmd('I');
}

int MsLineLeaderV2::ResetInversion(void)
{
	return WriteCmd('R');
}

int MsLineLeaderV2::TakeSnapshot(void)
{
	return WriteCmd('S');
}

int MsLineLeaderV2::CfgUs(void)
{
	return WriteCmd('A');
}

int MsLineLeaderV2::CfgEu(void)
{
	return WriteCmd('E');
}

int MsLineLeaderV2::CfgUniversal(void)
{
	return WriteCmd('U');
}

int MsLineLeaderV2::GetAvg()
{
	char val[1];
	size_t len = sizeof(val) / sizeof(val[0]);
	int avg, ret;

	ret = I2cRead(MLLV2_AVG, val, len);

	if (ret < 0)
		return ret;

	avg = val[0];
	return avg;
}
