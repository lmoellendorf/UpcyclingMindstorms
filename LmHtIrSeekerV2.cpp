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

HtIrSeekerV2::HtIrSeekerV2(void): i2c(HISV2_ADDR)
{
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
