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
	addr = 0x02 / 2;
}

int MsLineLeaderV2::invertColor(void)
{
	return MsI2cSensor::writeCmd('I');
}

int MsLineLeaderV2::resetInversion(void)
{
	return MsI2cSensor::writeCmd('R');
}

int MsLineLeaderV2::takeSnapshot(void)
{
	return MsI2cSensor::writeCmd('S');
}

int MsLineLeaderV2::getCalibrated(char *readings, size_t len)
{
	return MsLineSensorArray::getUpTo8Bytes(MLLV2_CALIB, readings, len);
}

int MsLineLeaderV2::getWhiteLimit(char *values, size_t len)
{
	return MsLineSensorArray::getUpTo8Bytes(MLLV2_W_LIMIT, values, len);
}

int MsLineLeaderV2::getBlackLimit(char *values, size_t len)
{
	return MsLineSensorArray::getUpTo8Bytes(MLLV2_B_LIMIT, values, len);
}

int MsLineLeaderV2::getWhiteCalibration(char *values, size_t len)
{
	return MsLineSensorArray::getUpTo8Bytes(MLLV2_W_CALIB, values, len);
}

int MsLineLeaderV2::getBlackCalibration(char *values, size_t len)
{
	return MsLineSensorArray::getUpTo8Bytes(MLLV2_B_CALIB, values, len);
}

int MsLineLeaderV2::getVoltage(uint16_t *readings, size_t len)
{
	return MsLineSensorArray::getUpTo8Words(MLLV2_VOLTAGE, readings, len);
}

int MsLineLeaderV2::getAverage(void)
{
	return I2C::readByte(MLLV2_AVG);
}

int MsLineLeaderV2::getSteering(void)
{
	return I2C::readByte(MLLV2_STEER);
}

int MsLineLeaderV2::getResult(void)
{
	return I2C::readByte(MLLV2_RESULT);
}

int MsLineLeaderV2::getSetpoint(void)
{
	return I2C::readByte(MLLV2_SETPT);
}

int MsLineLeaderV2::setSetpoint(char setpoint)
{
	return I2C::write(MLLV2_SETPT, &setpoint, 1);
}

int MsLineLeaderV2::getKp(void)
{
	return I2C::readByte(MLLV2_KP);
}

int MsLineLeaderV2::setKp(char k_p)
{
	return I2C::write(MLLV2_KP, &k_p, 1);
}

int MsLineLeaderV2::getKi(void)
{
	return I2C::readByte(MLLV2_KI);
}

int MsLineLeaderV2::setKi(char k_i)
{
	return I2C::write(MLLV2_KI, &k_i, 1);
}

int MsLineLeaderV2::getKd(void)
{
	return I2C::readByte(MLLV2_KD);
}

int MsLineLeaderV2::setKd(char k_d)
{
	return I2C::write(MLLV2_KD, &k_d, 1);
}

int MsLineLeaderV2::getKpDiv(void)
{
	return I2C::readByte(MLLV2_KP_DIV);
}

int MsLineLeaderV2::setKpDiv(char k_p_div)
{
	return I2C::write(MLLV2_KP_DIV, &k_p_div, 1);
}

int MsLineLeaderV2::getKiDiv(void)
{
	return I2C::readByte(MLLV2_KI_DIV);
}

int MsLineLeaderV2::setKiDiv(char k_i_div)
{
	return I2C::write(MLLV2_KI_DIV, &k_i_div, 1);
}

int MsLineLeaderV2::getKdDiv(void)
{
	return I2C::readByte(MLLV2_KD_DIV);
}

int MsLineLeaderV2::setKdDiv(char k_d_div)
{
	return I2C::write(MLLV2_KD_DIV, &k_d_div, 1);
}
