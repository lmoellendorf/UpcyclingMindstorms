/**
 * @copyright Lars Möllendorf
 * @file
 * @author Lars Möllendorf <lars@moellendorf.eu>
 * @brief Mindsensors IR Thermometer for Arduino
 *
 * @details
 *
 */

//! @cond SuppressGuard
#ifndef LM_MS_IR_THERMOMETER_ARRAY_
#define LM_MS_IR_THERMOMETER_ARRAY_
//! @endcond

#include "LmMsI2cSensor.h"
#include <stddef.h>
#include <stdint.h>

class MsIRThermometer: public MsI2cSensor
{

	public:
		/**
		 * Constructor of the sensor
		 */
		MsIRThermometer(void);

		float getAmbientTemperatureC(void);
		float getTargetTemperatureC(void);
		float getAmbientTemperatureF(void);
		float getTargetTemperatureF(void);

	private:
		float getTemperature(int reg);
};

//! @cond SuppressGuard
#endif
//! @endcond
