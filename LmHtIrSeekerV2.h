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
		enum Mode {
			AC,
			DC,
		};
		HtIrSeekerV2(int pin, enum Mode mode);
		HtIrSeekerV2(int pin);
		HtIrSeekerV2(void);
		int GetVersion(char *version, size_t len);
		int GetVendorId(char *vendor, size_t len);
		int GetDeviceId(char *device, size_t len);
		bool HasDirection(void);
		int GetDirection(void);
		int GetDirection(enum Mode mode);
		int GetDirection(bool block);
		int GetDirection(enum Mode mode, bool block);
		int GetAngle(void);
		int GetAngle(enum Mode mode);
		int GetAngle(bool block);
		int GetAngle(enum Mode mode, bool block);
		int GetSensorValue(unsigned int id);
		int GetSensorValue(unsigned int id, enum Mode mode);
		int GetSensorValues(int values[], size_t n_values);
		int GetSensorValues(int values[], size_t n_values, enum Mode mode);
		int GetAverage(void);

	private:
		I2C i2c;
		enum Mode mode;

};

//! @cond SuppressGuard
#endif
//! @endcond
