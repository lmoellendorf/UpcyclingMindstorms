#include <MeAuriga.h>
#include <Wire.h>
#include <math.h>

MeEncoderMotor motor(0x09, SLOT1);
int speed = 100;

void setup()
{
	Serial.begin(115200);
	motor.begin();
}

void loop()
{
	char key;
	int pos;
	double k = 500. / (360. * 3.); // / 2.16;
	const char f = 'f';
	const char b = 'b';
	const char plus = '+';
	const char minus = '-';
	const char s = 's';
	const char t = 't';
	const char r = 'r';
	const char T = 'T';

	Serial.print(f);
	Serial.println(": forward");
	Serial.print(b);
	Serial.println(": backward");
	Serial.print(plus);
	Serial.println(": accelerate");
	Serial.print(minus);
	Serial.println(": decelerate");
	Serial.print(s);
	Serial.println(": stop");
	Serial.print(t);
	Serial.println(": read tacho count");
	Serial.print(r);
	Serial.println(": read current speed");
	Serial.print(T);
	Serial.println(": turn once");
	Serial.println("");

	while (!Serial.available())
		;

	key = Serial.read();

	switch (key) {
	case f:
		Serial.println("FORWARD");
		speed = abs(speed);
		Serial.println(speed);
		break;

	case b:
		Serial.println("BACKWARD");
		speed = -abs(speed);
		Serial.println(speed);
		break;

	case plus:
		speed += 10;
		Serial.println(speed);
		break;

	case minus:
		speed -= 10;
		Serial.println(speed);
		break;

	case s:
		Serial.println("STOP");
		speed = 0;
		break;

	case t:
		Serial.println(motor.getCurrentPosition());
		break;

	case r:
		Serial.println(motor.getCurrentSpeed());
		break;

	case T:
		pos = motor.getCurrentPosition();
		Serial.println("TURN");
		motor.move(360 * k, 50);
		delay(2000);
		speed = 0;
		Serial.println((motor.getCurrentPosition() - pos) / k);
		break;

	default:

		break;
	}

	motor.runSpeed(speed);
}
