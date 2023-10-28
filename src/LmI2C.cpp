/**
 * @copyright Lars Möllendorf
 * @file
 * @author Lars Möllendorf <lars@moellendorf.eu>
 * @brief I2C read/wirte functions for Arduino
 *
 * @details
 */

#include "LmI2C.h"
#include <Wire.h>
#include <Arduino.h>
#include <string.h>

enum defaults {
	I2C_ADDR = 0x1,
};

enum registers {
	I2C_REG_VERS = 0x00,
	I2C_REG_VEND = 0x08,
	I2C_REG_DEV  = 0x10,
};

I2C::I2C(int addr)
{
	I2C::addr = addr;
	Wire.begin();
}

I2C::I2C(void) : I2C(I2C_ADDR)
{
}

int I2C::getVersion(char *version, size_t len)
{
	len = len > 9 ? 9 : len;
	return readStr(I2C_REG_VERS, version, len);
}

int I2C::getVendorId(char *vendor, size_t len)
{
	len = len > 9 ? 9 : len;
	return readStr(I2C_REG_VEND, vendor, len);
}

int I2C::getDeviceId(char *device, size_t len)
{
	len = len > 9 ? 9 : len;
	return readStr(I2C_REG_DEV, device, len);
}

int I2C::read(int reg, char *val, size_t len)
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

int I2C::readStr(int reg, char *val, size_t len)
{
	if (!val || !len)
		return -1;

	val[len - 1] = '\0';
	return read(reg, val, len - 1);
}

int I2C::readByte(int reg)
{
	char val[1];
	size_t len = sizeof(val) / sizeof(val[0]);
	int ret;

	ret = read(reg, val, len);

	if (ret < 0)
		return ret;

	return val[0];
}

int I2C::write(int reg, char *val, size_t len)
{
	if (!val || !len)
		return -1;

	/* set register pointer */
	Wire.beginTransmission(byte(addr));
	Wire.write(byte(reg));

	for (int i = 0; i < len; i++)
		Wire.write(byte(val[i]));

	Wire.endTransmission();
	return 0;
}
