/**
 * @copyright Lars Möllendorf
 * @file
 * @author Lars Möllendorf <lars@moellendorf.eu>
 * @brief Mindsensors LineLeader V2 for Arduino
 *
 * @details
 */

#include "LmMsLineLeaderV2.h"
#include <Arduino.h>
#include <string.h>


enum registers {
	MLLV2_CMD     = 0x41,
	MLLV2_CALIB   = 0x49,
	MLLV2_W_LIMIT = 0x51,
	MLLV2_B_LIMIT = 0x59,
	MLLV2_W_CALIB = 0x64,
	MLLV2_B_CALIB = 0x6C,
	MLLV2_VOLTAGE = 0x74,
	MLLV2_STEER   = 0x42,
	MLLV2_AVG     = 0x43,
	MLLV2_RESULT  = 0x44,
	MLLV2_SETPT   = 0x45,
	MLLV2_KP      = 0x46,
	MLLV2_KI      = 0x47,
	MLLV2_KD      = 0x48,
	MLLV2_KP_DIV  = 0x61,
	MLLV2_KI_DIV  = 0x62,
	MLLV2_KD_DIV  = 0x63,
};

MsLineLeaderV2::MsLineLeaderV2(void)
{
}

int MsLineLeaderV2::getVersion(char *version, size_t len)
{
	len = len > 9 ? 9 : len;
	return i2c.getVersion(version, len);
}

int MsLineLeaderV2::getVendorId(char *vendor, size_t len)
{
	len = len > 9 ? 9 : len;
	return i2c.getVendorId(vendor, len);
}

int MsLineLeaderV2::getDeviceId(char *device, size_t len)
{
	len = len > 9 ? 9 : len;
	return i2c.getDeviceId(device, len);
}

int MsLineLeaderV2::writeCmd(char cmd)
{
	return i2c.write(MLLV2_CMD, &cmd, 1);
}

int MsLineLeaderV2::calibrateWhite(void)
{
	return writeCmd('W');
}

int MsLineLeaderV2::calibrateBlack(void)
{
	return writeCmd('B');
}

int MsLineLeaderV2::putToSleep(void)
{
	return writeCmd('D');
}

int MsLineLeaderV2::wakeUp(void)
{
	return writeCmd('P');
}

int MsLineLeaderV2::invertColor(void)
{
	return writeCmd('I');
}

int MsLineLeaderV2::resetInversion(void)
{
	return writeCmd('R');
}

int MsLineLeaderV2::takeSnapshot(void)
{
	return writeCmd('S');
}

int MsLineLeaderV2::cfgUs(void)
{
	return writeCmd('A');
}

int MsLineLeaderV2::cfgEu(void)
{
	return writeCmd('E');
}

int MsLineLeaderV2::cfgUniversal(void)
{
	return writeCmd('U');
}

int MsLineLeaderV2::getCalibrated(char *readings, size_t len)
{
	len = len > 8 ? 8 : len;
	return i2c.read(MLLV2_CALIB, readings, len);
}

int MsLineLeaderV2::getWhiteLimit(char *values, size_t len)
{
	len = len > 8 ? 8 : len;
	return i2c.read(MLLV2_W_LIMIT, values, len);
}

int MsLineLeaderV2::getBlackLimit(char *values, size_t len)
{
	len = len > 8 ? 8 : len;
	return i2c.read(MLLV2_B_LIMIT, values, len);
}

int MsLineLeaderV2::getWhiteCalibration(char *values, size_t len)
{
	len = len > 8 ? 8 : len;
	return i2c.read(MLLV2_W_CALIB, values, len);
}

int MsLineLeaderV2::getBlackCalibration(char *values, size_t len)
{
	len = len > 8 ? 8 : len;
	return i2c.read(MLLV2_B_CALIB, values, len);
}

int MsLineLeaderV2::getVoltage(int *readings, size_t len)
{
	int swap, ret;

	len = len > 8 ? 8 : len;
	ret = i2c.read(MLLV2_VOLTAGE, (char *)readings, len * 2);

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
}

int MsLineLeaderV2::getAverage(void)
{
	return i2c.readByte(MLLV2_AVG);
}

int MsLineLeaderV2::getSteering(void)
{
	return i2c.readByte(MLLV2_STEER);
}

int MsLineLeaderV2::getResult(void)
{
	return i2c.readByte(MLLV2_RESULT);
}

int MsLineLeaderV2::getSetpoint(void)
{
	return i2c.readByte(MLLV2_SETPT);
}

int MsLineLeaderV2::setSetpoint(char setpoint)
{
	return i2c.write(MLLV2_SETPT, &setpoint, 1);
}

int MsLineLeaderV2::getKp(void)
{
	return i2c.readByte(MLLV2_KP);
}

int MsLineLeaderV2::setKp(char k_p)
{
	return i2c.write(MLLV2_KP, k_p, 1);
}

int MsLineLeaderV2::getKi(void)
{
	return i2c.readByte(MLLV2_KI);
}

int MsLineLeaderV2::setKi(char k_i)
{
	return i2c.write(MLLV2_KI, k_i, 1);
}

int MsLineLeaderV2::getKd(void)
{
	return i2c.readByte(MLLV2_KD);
}

int MsLineLeaderV2::setKd(char k_d)
{
	return i2c.write(MLLV2_KD, k_d, 1);
}

int MsLineLeaderV2::getKpDiv(void)
{
	return i2c.readByte(MLLV2_KP_DIV);
}

int MsLineLeaderV2::setKpDiv(char k_p_div)
{
	return i2c.write(MLLV2_KP_DIV, k_p_div, 1);
}

int MsLineLeaderV2::getKiDiv(void)
{
	return i2c.readByte(MLLV2_KI_DIV);
}

int MsLineLeaderV2::setKiDiv(char k_i_div)
{
	return i2c.write(MLLV2_KI_DIV, k_i_div, 1);
}

int MsLineLeaderV2::getKdDiv(void)
{
	return i2c.readByte(MLLV2_KD_DIV);
}

int MsLineLeaderV2::setKdDiv(char k_d_div)
{
	return i2c.write(MLLV2_KD_DIV, k_d_div, 1);
}
