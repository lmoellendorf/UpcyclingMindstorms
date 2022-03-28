/**
 * @copyright Lars Möllendorf
 * @file
 * @author Lars Möllendorf <lars@moellendorf.eu>
 * @brief HiTechnick Infrared Seeker for Arduino
 *
 * @details
 */

//! @cond SuppressGuard
#ifndef LM_HT_IR_SEEKER_V2_
#define LM_HT_IR_SEEKER_V2_
//! @endcond

#include "LmI2C.h"
#include <stddef.h>

class HtIrSeekerV2
{

	public:
		HtIrSeekerV2(void);
		int GetVersion(char *version, size_t len);
		int GetVendorId(char *vendor, size_t len);
		int GetDeviceId(char *device, size_t len);

	private:
		I2C i2c;

};

//! @cond SuppressGuard
#endif
//! @endcond
