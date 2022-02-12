/**
 * @copyright Lars Möllendorf
 * @file
 * @author Lars Möllendorf <lars@moellendorf.eu>
 * @brief Mindsensors LineLeader V2 for Arduino
 *
 * @details
 */

//! @cond SuppressGuard
#ifndef LM_MS_LINE_LEADER_V2_
#define LM_MS_LINE_LEADER_V2_
//! @endcond

#include <stddef.h>

class MsLineLeaderV2
{

	public:
		MsLineLeaderV2(void);
		int GetFwVersion(char *version, size_t len);
		int GetFwVendor(char *vendor, size_t len);
		int GetFwDevice(char *device, size_t len);
		int GetAvg();

	private:
		int addr;
		int I2cRead(int reg, char *val, size_t len);

};

//! @cond SuppressGuard
#endif
//! @endcond
