#include <LmTouch.h>

Touch touch = Touch(A0);

void setup()
{
	pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
	bool down = touch.isDown();

	if (down)
		digitalWrite(LED_BUILTIN, 1);
	else
		digitalWrite(LED_BUILTIN, 0);
}
