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
		int I2cRead(int reg, char *val, size_t len);
		int I2cReadStr(int reg, char *val, size_t len);
		int I2cReadByte(int reg);
		int I2cWrite(int reg, char *val, size_t len);
		int GetFwVersion(char *version, size_t len);
		int GetFwVendor(char *vendor, size_t len);
		int GetFwDevice(char *device, size_t len);
		int WriteCmd(char cmd);
		int CalibrateWhite(void);
		int CalibrateBlack(void);
		int PutToSleep(void);
		int WakeUp(void);
		int InvertColor(void);
		int ResetInversion(void);
		int TakeSnapshot(void);
		int CfgUs(void);
		int CfgEu(void);
		int CfgUniversal(void);
		int GetCalibrated(char *readings, size_t len);
		int GetWhiteLimit(char *values, size_t len);
		int GetBlackLimit(char *values, size_t len);
		int GetWhiteCalibration(char *values, size_t len);
		int GetBlackCalibration(char *values, size_t len);
		int GetVoltage(int *readings, size_t len);
		int GetSteering(void);
		int GetAverage(void);
		int GetResult(void);
		int GetSetpoint(void);
		int SetSetpoint(char setpoint);
		int GetKp(void);
		int SetKp(char k_p);
		int GetKi(void);
		int SetKi(char k_i);
		int GetKd(void);
		int SetKd(char k_d);
		int GetKpDiv(void);
		int SetKpDiv(char k_p_div);
		int GetKiDiv(void);
		int SetKiDiv(char k_i_div);
		int GetKdDiv(void);
		int SetKdDiv(char k_d_div);

	private:
		int addr;

};

//! @cond SuppressGuard
#endif
//! @endcond
