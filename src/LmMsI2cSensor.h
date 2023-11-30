/**
 * @copyright Lars Möllendorf
 * @file
 * @author Lars Möllendorf <lars@moellendorf.eu>
 * @brief Common Mindsensors I2C sensors registers and commands
 *
 * @details
 *
 */

//! @cond SuppressGuard
#ifndef LM_MS_I2C_SENSOR_
#define LM_MS_I2C_SENSOR_
//! @endcond

#include "LmI2C.h"
#include <stddef.h>

class MsI2cSensor: public I2C
{

	public:
		/**
		 * Constructor of the sensor
		 */
		MsI2cSensor(void);

		/**
		 * Get Version information
		 *
		 * @param[out] version  Pointer to array of length len to write
		 *                      version information to
		 * @param      len      Length of array `version` points to
		 * @return              0 on success, -1 else
		 */
		int getVersion(char *version, size_t len);

		/**
		 * Get Vedor ID information
		 *
		 * @param[out] vendoer  Pointer to array of length len to write
		 *                      vendor ID information to
		 * @param      len      Length of array `vendor` points to
		 * @return              0 on success, -1 else
		 */
		int getVendorId(char *vendor, size_t len);

		/**
		 * Get Device ID information
		 *
		 * @param[out] device  Pointer to array of length len to write
		 *                     device ID information to
		 * @param      len     Length of array `device` points to
		 * @return             0 on success, -1 else
		 */
		int getDeviceId(char *device, size_t len);

		/**
		 * Change I2C address of sensor
		 *
		 * @param addr  New address of the sensor
		 * @return      0 on success, -1 else
		 */
		int changeAddress(char addr);

		/**
		 * Write I2C command to the sensor
		 *
		 * CMD  Description
		 * D  Put Sensor to sleep
		 * P  Wake up the sensor
		 * A  Configure Sensor for US region
		 *    (and regions with 60 Hz electrical frequency).
		 * E  Configure sensor for European region
		 *    (and regions with 50 Hz electrical frequency)
		 * U  Configure sensor for universal frequency
		 *    (in this mode the sensor adjusts for any frequency,
		 *    this is also the default mode).
		 *
		 * @param cmd  Command to write
		 * @return     0 on success, -1 else
		 */
		int writeCmd(char cmd);
		int putToSleep(void);
		int wakeUp(void);
		int cfgUs(void);
		int cfgEu(void);
		int cfgUniversal(void);
};

//! @cond SuppressGuard
#endif
//! @endcond
