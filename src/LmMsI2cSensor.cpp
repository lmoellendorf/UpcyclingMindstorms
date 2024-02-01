/**
 * @copyright Lars Möllendorf
 * @file
 * @author Lars Möllendorf <lars@moellendorf.eu>
 * @brief Common Mindsensors I2C sensors registers and commands
 *
 * @details
 */

#include "LmMsI2cSensor.h"
#include <Arduino.h>
#include <string.h>


enum registers {
	MS_I2C_CMD    = 0x41,
};

static char cmd_addr[] = {'\xA0', '\xAA', '\xA5', '\x00'};
static const size_t n_cmd_addr = sizeof(cmd_addr) / sizeof(cmd_addr[0]);

MsI2cSensor::MsI2cSensor(void)
{
}

int MsI2cSensor::getVersion(char *version, size_t len)
{
	len = len > 9 ? 9 : len;
	return I2C::getVersion(version, len);
}

int MsI2cSensor::getVendorId(char *vendor, size_t len)
{
	len = len > 9 ? 9 : len;
	return I2C::getVendorId(vendor, len);
}

int MsI2cSensor::getDeviceId(char *device, size_t len)
{
	len = len > 9 ? 9 : len;
	return I2C::getDeviceId(device, len);
}

int MsI2cSensor::changeAddress(char addr)
{
	cmd_addr[n_cmd_addr - 1] = addr << 1;

	for (int i = 0; i < n_cmd_addr; i++) {
		writeCmd(cmd_addr[i]);
		delay(100);
	}

	I2C::addr = addr;

	for (int i = 0; i < addr; i++) {
		putToSleep();
		delay(300);
		wakeUp();
		delay(300);
	}

	return 0;
}

int MsI2cSensor::probeAddress(void)
{
	char vendor[9] = {};
	size_t len = sizeof(vendor) / sizeof(vendor[0]);
	int oldaddr, ret = 0;

	oldaddr = addr;

	for (int a = 8; a < 119; a++) {
		addr = a;
		ret = getVendorId(vendor, len);

		if (ret < 0)
			continue;

		ret = strncmp("mndsnsrs", vendor, len);

		if (!ret)
			break;
	}

	if (ret != 0)
		addr = oldaddr;

	return addr;
}

int MsI2cSensor::writeCmd(char cmd)
{
	return I2C::write(MS_I2C_CMD, &cmd, 1);
}

int MsI2cSensor::putToSleep(void)
{
	return writeCmd('D');
}

int MsI2cSensor::wakeUp(void)
{
	return writeCmd('P');
}

int MsI2cSensor::cfgUs(void)
{
	return writeCmd('A');
}

int MsI2cSensor::cfgEu(void)
{
	return writeCmd('E');
}

int MsI2cSensor::cfgUniversal(void)
{
	return writeCmd('U');
}
