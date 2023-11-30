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

#include "LmMsLineSensorArray.h"
#include <stddef.h>

class MsLineLeaderV2: public MsLineSensorArray
{

	public:
		/**
		 * Constructor of the sensor
		 */
		MsLineLeaderV2(void);

		/**
		 * Write I2C command to the sensor
		 *
		 * Additional commands for this sensor:
		 *
		 * CMD  Description
		 * I  Color inversion (White line on a black background)
		 * R  Reset Color inversion
		 *    (black line on a white background,
		 *    this is also the default).
		 * S  Take a snapshot, this command looks at the line under the
		 *    sensor and stores the width and position of the line in
		 *    sensor’s memory. Subsequently, sensor will use these
		 *    characteristics of line to track it. This command inverts
		 *    the colors if it sees a white line on black background.
		 *    (PID parameters are not affected).
		 *
		 * @param cmd  Command to write
		 * @return     0 on success, -1 else
		 */
		int writeCmd(char cmd);
		int invertColor(void);
		int resetInversion(void);
		int takeSnapshot(void);
		int getCalibrated(char *readings, size_t len);
		int getWhiteLimit(char *values, size_t len);
		int getBlackLimit(char *values, size_t len);
		int getWhiteCalibration(char *values, size_t len);
		int getBlackCalibration(char *values, size_t len);
		int getVoltage(uint16_t *readings, size_t len);
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
};

//! @cond SuppressGuard
#endif
//! @endcond
