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
		static const int AC = 0;
		static const int DC = 1;
		HtIrSeekerV2(int pin, int mode);
		HtIrSeekerV2(void);
		int getVersion(char *version, size_t len);
		int getVendorId(char *vendor, size_t len);
		int getDeviceId(char *device, size_t len);
		bool hasDirection(void);
		int getDirection(void);
		int getDirection(int mode);
		int getDirection(bool block);
		int getDirection(int mode, bool block);
		int getAngle(void);
		int getAngle(int mode);
		int getAngle(bool block);
		int getAngle(int mode, bool block);
		int getSensorValue(unsigned int id);
		int getSensorValue(unsigned int id, int mode);
		int getSensorValues(int values[], size_t n_values);
		int getSensorValues(int values[], size_t n_values, int mode);
		int getAverage(void);

	protected:
		HtIrSeekerV2(int mode);
		void setMode(int mode);

	private:
		I2C i2c;
		int mode;
		int switchMode(int mode);

};

//! @cond SuppressGuard
#endif
//! @endcond
