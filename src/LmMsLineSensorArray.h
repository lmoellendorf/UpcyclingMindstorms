/**
 * @copyright Lars Möllendorf
 * @file
 * @author Lars Möllendorf <lars@moellendorf.eu>
 * @brief Mindsensors Line Sensor Array for Arduino
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
#ifndef LM_MS_LINE_SENSOR_ARRAY_
#define LM_MS_LINE_SENSOR_ARRAY_
//! @endcond

#include "LmMsI2cSensor.h"
#include <stddef.h>
#include <stdint.h>

class MsLineSensorArray: public MsI2cSensor
{

	public:
		/**
		 * Constructor of the sensor
		 */
		MsLineSensorArray(void);

		/**
		 * Write I2C command to the sensor
		 *
		 * Additional commands for this sensor:
		 *
		 * CMD  Description
		 * W  Calibrate White
		 * B  Calibrate Black
		 *
		 * @param cmd  Command to write
		 * @return     0 on success, -1 else
		 */
		int writeCmd(char cmd);
		int calibrateWhite(void);
		int calibrateBlack(void);
		int getCalibrated(char *readings, size_t len);
		int getWhiteLimit(char *values, size_t len);
		int getBlackLimit(char *values, size_t len);
		int getWhiteCalibration(char *values, size_t len);
		int getBlackCalibration(char *values, size_t len);
		int getVoltage(uint16_t *readings, size_t len);

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

	protected:
		int getUpTo8Bytes(int reg, char *readings, size_t len);
		int getUpTo8Words(int reg, uint16_t *readings, size_t len);
		int getResultNAverage(int *result, int *average);
};

//! @cond SuppressGuard
#endif
//! @endcond
