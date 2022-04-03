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
		int getVersion(char *version, size_t len);
		int getVendorId(char *vendor, size_t len);
		int getDeviceId(char *device, size_t len);
		bool hasDirection(void);
		int getDirection(void);
		int getDirection(enum Mode mode);
		int getDirection(bool block);
		int getDirection(enum Mode mode, bool block);
		int getAngle(void);
		int getAngle(enum Mode mode);
		int getAngle(bool block);
		int getAngle(enum Mode mode, bool block);
		int getSensorValue(unsigned int id);
		int getSensorValue(unsigned int id, enum Mode mode);
		int getSensorValues(int values[], size_t n_values);
		int getSensorValues(int values[], size_t n_values, enum Mode mode);
		int getAverage(void);

	private:
		I2C i2c;
		enum Mode mode;

};

//! @cond SuppressGuard
#endif
//! @endcond
