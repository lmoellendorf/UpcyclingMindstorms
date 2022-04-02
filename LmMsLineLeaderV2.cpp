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

int MsLineLeaderV2::GetVersion(char *version, size_t len)
{
	len = len > 9 ? 9 : len;
	return i2c.GetVersion(version, len);
}

int MsLineLeaderV2::GetVendorId(char *vendor, size_t len)
{
	len = len > 9 ? 9 : len;
	return i2c.GetVendorId(vendor, len);
}

int MsLineLeaderV2::GetDeviceId(char *device, size_t len)
{
	len = len > 9 ? 9 : len;
	return i2c.GetDeviceId(device, len);
}

int MsLineLeaderV2::WriteCmd(char cmd)
{
	return i2c.Write(MLLV2_CMD, &cmd, 1);
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

int MsLineLeaderV2::GetCalibrated(char *readings, size_t len)
{
	len = len > 8 ? 8 : len;
	return i2c.Read(MLLV2_CALIB, readings, len);
}

int MsLineLeaderV2::GetWhiteLimit(char *values, size_t len)
{
	len = len > 8 ? 8 : len;
	return i2c.Read(MLLV2_W_LIMIT, values, len);
}

int MsLineLeaderV2::GetBlackLimit(char *values, size_t len)
{
	len = len > 8 ? 8 : len;
	return i2c.Read(MLLV2_B_LIMIT, values, len);
}

int MsLineLeaderV2::GetWhiteCalibration(char *values, size_t len)
{
	len = len > 8 ? 8 : len;
	return i2c.Read(MLLV2_W_CALIB, values, len);
}

int MsLineLeaderV2::GetBlackCalibration(char *values, size_t len)
{
	len = len > 8 ? 8 : len;
	return i2c.Read(MLLV2_B_CALIB, values, len);
}

int MsLineLeaderV2::GetVoltage(int *readings, size_t len)
{
	int swap, ret;

	len = len > 8 ? 8 : len;
	ret = i2c.Read(MLLV2_VOLTAGE, (char *)readings, len * 2);

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

int MsLineLeaderV2::GetAverage(void)
{
	return i2c.ReadByte(MLLV2_AVG);
}

int MsLineLeaderV2::GetSteering(void)
{
	return i2c.ReadByte(MLLV2_STEER);
}

int MsLineLeaderV2::GetResult(void)
{
	return i2c.ReadByte(MLLV2_RESULT);
}

int MsLineLeaderV2::GetSetpoint(void)
{
	return i2c.ReadByte(MLLV2_SETPT);
}

int MsLineLeaderV2::SetSetpoint(char setpoint)
{
	return i2c.Write(MLLV2_SETPT, &setpoint, 1);
}

int MsLineLeaderV2::GetKp(void)
{
	return i2c.ReadByte(MLLV2_KP);
}

int MsLineLeaderV2::SetKp(char k_p)
{
	return i2c.Write(MLLV2_KP, k_p, 1);
}

int MsLineLeaderV2::GetKi(void)
{
	return i2c.ReadByte(MLLV2_KI);
}

int MsLineLeaderV2::SetKi(char k_i)
{
	return i2c.Write(MLLV2_KI, k_i, 1);
}

int MsLineLeaderV2::GetKd(void)
{
	return i2c.ReadByte(MLLV2_KD);
}

int MsLineLeaderV2::SetKd(char k_d)
{
	return i2c.Write(MLLV2_KD, k_d, 1);
}

int MsLineLeaderV2::GetKpDiv(void)
{
	return i2c.ReadByte(MLLV2_KP_DIV);
}

int MsLineLeaderV2::SetKpDiv(char k_p_div)
{
	return i2c.Write(MLLV2_KP_DIV, k_p_div, 1);
}

int MsLineLeaderV2::GetKiDiv(void)
{
	return i2c.ReadByte(MLLV2_KI_DIV);
}

int MsLineLeaderV2::SetKiDiv(char k_i_div)
{
	return i2c.Write(MLLV2_KI_DIV, k_i_div, 1);
}

int MsLineLeaderV2::GetKdDiv(void)
{
	return i2c.ReadByte(MLLV2_KD_DIV);
}

int MsLineLeaderV2::SetKdDiv(char k_d_div)
{
	return i2c.Write(MLLV2_KD_DIV, k_d_div, 1);
}
