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
		int GetAvg();

	private:
		int addr;

};

//! @cond SuppressGuard
#endif
//! @endcond
