/**
 * @copyright Lars Möllendorf
 * @file
 * @author Lars Möllendorf <lars@moellendorf.eu>
 * @brief I2C read/wirte functions for Arduino
 *
 * @details
 */

//! @cond SuppressGuard
#ifndef LM_I2C_
#define LM_I2C_
//! @endcond

#include <stddef.h>

class I2C
{

	public:
		I2C(void);
		int Read(int reg, char *val, size_t len);
		int ReadStr(int reg, char *val, size_t len);
		int ReadByte(int reg);
		int Write(int reg, char *val, size_t len);
		int GetVersion(char *version, size_t len);
		int GetVendorId(char *vendor, size_t len);
		int GetDeviceId(char *device, size_t len);

	private:
		int addr;

};

//! @cond SuppressGuard
#endif
//! @endcond
