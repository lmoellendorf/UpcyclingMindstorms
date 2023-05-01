/**
 * @copyright Lars Möllendorf
 * @file
 * @author Lars Möllendorf <lars@moellendorf.eu>
 * @brief Mindsensors touch sensor for Arduino
 *
 * @details
 */

//! @cond SuppressGuard
#ifndef LM_TOUCH_
#define LM_TOUCH_
//! @endcond

#include <stdbool.h>

class Touch
{

	public:
		Touch(int pin);
		bool isUp(void);
		bool isDown(void);

	private:
		int pin;

};

//! @cond SuppressGuard
#endif
//! @endcond
