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

#include "LmI2C.h"
#include <stddef.h>

class MsLineLeaderV2
{

	public:
		MsLineLeaderV2(void);
		int getVersion(char *version, size_t len);
		int getVendorId(char *vendor, size_t len);
		int getDeviceId(char *device, size_t len);
		int writeCmd(char cmd);
		int calibrateWhite(void);
		int calibrateBlack(void);
		int putToSleep(void);
		int wakeUp(void);
		int invertColor(void);
		int resetInversion(void);
		int takeSnapshot(void);
		int cfgUs(void);
		int cfgEu(void);
		int cfgUniversal(void);
		int getCalibrated(char *readings, size_t len);
		int getWhiteLimit(char *values, size_t len);
		int getBlackLimit(char *values, size_t len);
		int getWhiteCalibration(char *values, size_t len);
		int getBlackCalibration(char *values, size_t len);
		int getVoltage(int *readings, size_t len);
		int getSteering(void);
		int getAverage(void);
		int getResult(void);
		int getSetpoint(void);
		int setSetpoint(char setpoint);
		int getKp(void);
		int setKp(char k_p);
		int getKi(void);
		int setKi(char k_i);
		int getKd(void);
		int setKd(char k_d);
		int getKpDiv(void);
		int setKpDiv(char k_p_div);
		int getKiDiv(void);
		int setKiDiv(char k_i_div);
		int getKdDiv(void);
		int setKdDiv(char k_d_div);

	private:
		I2C i2c;

};

//! @cond SuppressGuard
#endif
//! @endcond
