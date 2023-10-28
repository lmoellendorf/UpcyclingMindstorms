/**
 * @copyright Lars Möllendorf
 * @file
 * @author Lars Möllendorf <lars@moellendorf.eu>
 * @brief LEGO Mindstorms NXT touch sensor for Arduino
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
		/**
		 * Constructor
		 *
		 * @param pin  Analog Arduino pin used as input
		 */
		Touch(int pin);

		/**
		 * @return true, if touch sensor is released. false, else.
		 */
		bool isUp(void);

		/**
		 * @return true, if touch sensor is pressed. false, else
		 */
		bool isDown(void);

	private:
		int pin;

};

//! @cond SuppressGuard
#endif
//! @endcond
