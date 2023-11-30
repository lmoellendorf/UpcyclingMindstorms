/**
 * @copyright Lars Möllendorf
 * @file
 * @author Lars Möllendorf <lars@moellendorf.eu>
 * @brief Mindsensors LineLeader V2 for Arduino
 *
 * @details
 *
 * The sensor's normal orientation is:
 *
 * Socket upward and port facing to the robot.
 *
 * The values of `getResult()` and `getAverage()` need more detailed
 * information. Therefore citing LineLeader-v2 User Guide
 * - Copyright (C) 2016 mindsensors.com
 *
 * # Average:
 *
 * The average is a weighted average of the bits set to 1 based
 * on the position.
 * i.e. left most bit has weight of 10, second bit has weight
 * of 20.
 *
 * The diagrams below explains the line scenario and the
 * Average returned.
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Suppose your line is narrow and only under the sensor 5.
 * I.e. all the 8 sensors except the 5th sensor will return
 * zero value. And the 5 th bit will be 1.
 *
 * <pre>
 *                             XXXXX
 *                             XXXXX
 *             +---+---+---+---+---+---+---+---+
 *             | W | W | W | W | B | W | W | W |
 *             +---+---+---+---+---+---+---+---+
 *                             XXXXX
 *                             XXXXX
 * </pre>
 *
 * The ‘Average’ returned in this case
 * will be 50, calculated as: (0+0+0+0+50+0+0+0)/1
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Suppose, your line is wider, and 4 sensors are over the
 * line.
 *
 * <pre>
 *                     XXXXXXXXXXXXXXXXX
 *                     XXXXXXXXXXXXXXXXX
 *             +---+---+---+---+---+---+---+---+
 *             | W | W | B | B | B | B | W | W |
 *             +---+---+---+---+---+---+---+---+
 *                     XXXXXXXXXXXXXXXXX
 *                     XXXXXXXXXXXXXXXXX
 * </pre>
 *
 * The ‘Average’ returned in this case will be 45, calculated
 * as: (0+0+30+40+50+60+0+0)/4
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * <pre>
 *                                         XXXXX
 *                                         XXXXX
 *             +---+---+---+---+---+---+---+---+
 *             | W | W | W | W | W | W | W | B |
 *             +---+---+---+---+---+---+---+---+
 *                                         XXXXX
 *                                         XXXXX
 * </pre>
 *
 * The ‘Average’ returned in this case will be 80, calculated
 * as: (0+0+0+0+0+0+0+80)/1
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Result:
 *
 * Result is a byte value of the sensor reading. Each bit
 * corresponding to the sensor where the line is seen is set to
 * 1, or else the bit is zero.
 *
 * The diagrams below explains the line scenario and the
 * Result returned.
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Suppose your line is narrow and only under the sensor 5.
 * I.e. all the 8 sensors except the 5th sensor will return
 * zero value. And the 5 th bit will be 1.
 *
 * <pre>
 *                             XXXXX
 *                             XXXXX
 *             +---+---+---+---+---+---+---+---+
 *             | W | W | W | W | B | W | W | W |
 *             +---+---+---+---+---+---+---+---+
 *                             XXXXX
 *                             XXXXX
 * </pre>
 *
 * The ‘Result’ returned in this case will be binary:
 * 0b00001000 (or decimal: 8 or hex: 0x08).
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Suppose, your line is wider, and 4 sensors are over the
 * line.
 *
 * <pre>
 *                     XXXXXXXXXXXXXXXXX
 *                     XXXXXXXXXXXXXXXXX
 *             +---+---+---+---+---+---+---+---+
 *             | W | W | B | B | B | B | W | W |
 *             +---+---+---+---+---+---+---+---+
 *                     XXXXXXXXXXXXXXXXX
 *                     XXXXXXXXXXXXXXXXX
 * </pre>
 *
 * The Result returned in this case will be binary: 0b00111100
 * (or decimal: 60 or hex: 0x3C)
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * <pre>
 *                                         XXXXX
 *                                         XXXXX
 *             +---+---+---+---+---+---+---+---+
 *             | W | W | W | W | W | W | W | B |
 *             +---+---+---+---+---+---+---+---+
 *                                         XXXXX
 *                                         XXXXX
 * </pre>
 *
 * The ‘Result’ returned in this case will be binary:
 * 0b00000001 (or decimal: 1 or hex: 0x01).
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

//! @cond SuppressGuard
#ifndef LM_MS_LINE_LEADER_V2_
#define LM_MS_LINE_LEADER_V2_
//! @endcond

#include "LmMsI2cSensor.h"
#include <stddef.h>

class MsLineLeaderV2: public MsI2cSensor
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
		 * W  Calibrate White
		 * B  Calibrate Black
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
		int calibrateWhite(void);
		int calibrateBlack(void);
		int invertColor(void);
		int resetInversion(void);
		int takeSnapshot(void);
		int getCalibrated(char *readings, size_t len);
		int getWhiteLimit(char *values, size_t len);
		int getBlackLimit(char *values, size_t len);
		int getWhiteCalibration(char *values, size_t len);
		int getBlackCalibration(char *values, size_t len);
		int getVoltage(int *readings, size_t len);
		int getSteering(void);

		/**
		 * Get Average value
		 *
		 * See header comment for details.
		 *
		 * @return  Weighted average of the bits set to 1 based on the
		 *          position.
		 */
		int getAverage(void);

		/**
		 * Get Result value
		 *
		 * See header comment for details.
		 *
		 * @return  Byte value of the sensor reading. Each bit
		 *          corresponding to the sensor where the line is seen
		 *          is set to 1, or else the bit is zero.
		 */
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
