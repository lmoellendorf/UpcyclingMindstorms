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
		I2C(int addr);
		I2C(void);
		int read(int reg, char *val, size_t len);
		int readStr(int reg, char *val, size_t len);
		int readByte(int reg);
		int readWord(int reg);
		int write(int reg, char *val, size_t len);
		int getVersion(char *version, size_t len);
		int getVendorId(char *vendor, size_t len);
		int getDeviceId(char *device, size_t len);
		int addr;

	private:

};

//! @cond SuppressGuard
#endif
//! @endcond
