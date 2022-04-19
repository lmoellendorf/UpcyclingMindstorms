/**
 * @copyright Lars Möllendorf
 * @file
 * @author Lars Möllendorf <lars@moellendorf.eu>
 * @brief Mindsensors touch sensor for Arduino
 *
 * @details
 */

#include "LmTouch.h"
#include <Arduino.h>

Touch::Touch(int pin)
{
	Touch::pin = pin;
	pinMode(pin, INPUT_PULLUP);
}

bool Touch::isDown(void)
{
	return digitalRead(pin) == HIGH ? false : true;
}

bool Touch::isUp(void)
{
	return !isDown();
}
