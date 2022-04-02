#include <LmMsLineLeaderV2.h>

MsLineLeaderV2 ll = MsLineLeaderV2();

void getDeviceInfo(void)
{
	char fw_str[9] = {0};
	size_t len = sizeof(fw_str) / sizeof(fw_str[0]);
	int ret;

	ret = ll.GetVersion(fw_str, len);

	if (!ret) {
		Serial.println("version: ");
		Serial.println(fw_str);
	}

	ret = ll.GetVendorId(fw_str, len);

	if (!ret) {
		Serial.println("vendor: ");
		Serial.println(fw_str);
	}

	ret = ll.GetDeviceId(fw_str, len);

	if (!ret) {
		Serial.println("device: ");
		Serial.println(fw_str);
	}
}

void setup()
{
	Serial.begin(115200);
	getDeviceInfo();
}

void loop()
{
	char readings[8];
	size_t n_readings = sizeof(readings) / sizeof(readings[0]);
	int voltage[8];
	size_t n_voltage = sizeof(voltage) / sizeof(voltage[0]);
	char key;
	const char v = 'v';
	const char c = 'c';
	const char w = 'w';
	const char b = 'b';
	const char W = 'W';
	const char B = 'B';
	const char V = 'V';
	const char s = 's';
	const char a = 'a';
	const char r = 'r';
	const char p = 'p';
	const char u = 'u';
	int ret;

	Serial.print(v);
	Serial.println(": GetVersion, GetVendorId, GetDeviceId");
	Serial.print(c);
	Serial.println(": GetCalibrated");
	Serial.print(w);
	Serial.println(": GetWhiteLimit");
	Serial.print(b);
	Serial.println(": GetBlackLimit");
	Serial.print(W);
	Serial.println(": GetWhiteCalibration");
	Serial.print(B);
	Serial.println(": GetBlackCalibration");
	Serial.print(V);
	Serial.println(": GetVoltage");
	Serial.print(s);
	Serial.println(": GetSteering");
	Serial.print(a);
	Serial.println(": GetAverage");
	Serial.print(r);
	Serial.println(": GetResult");
	Serial.print(p);
	Serial.println(": PutToSleep");
	Serial.print(u);
	Serial.println(": WakeUp");

	while (!Serial.available())
		;

	key = Serial.read();

	switch (key) {
	case v:
		getDeviceInfo();
		break;

	case c:
		ret = ll.GetCalibrated(readings, n_readings);
		Serial.println("calibrated: ");

		for (int i = 0; i < n_readings; i++) {
			Serial.print((int)readings[i]);

			if (i != n_readings - 1)
				Serial.print(":");
		}

		Serial.println("");
		break;

	case w:
		ret = ll.GetWhiteLimit(readings, n_readings);
		Serial.println("white limit: ");

		for (int i = 0; i < n_readings; i++) {
			Serial.print((int)readings[i]);

			if (i != n_readings - 1)
				Serial.print(":");
		}

		Serial.println("");
		break;

	case b:
		ret = ll.GetBlackLimit(readings, n_readings);
		Serial.println("black limit: ");

		for (int i = 0; i < n_readings; i++) {
			Serial.print((int)readings[i]);

			if (i != n_readings - 1)
				Serial.print(":");
		}

		Serial.println("");
		break;

	case W:
		ret = ll.GetWhiteCalibration(readings, n_readings);
		Serial.println("white calibration: ");

		for (int i = 0; i < n_readings; i++) {
			Serial.print((int)readings[i]);

			if (i != n_readings - 1)
				Serial.print(":");
		}

		Serial.println("");
		break;

	case B:
		ret = ll.GetBlackCalibration(readings, n_readings);
		Serial.println("black calibration: ");

		for (int i = 0; i < n_readings; i++) {
			Serial.print((int)readings[i]);

			if (i != n_readings - 1)
				Serial.print(":");
		}

		Serial.println("");
		break;

	case V:
		ret = ll.GetVoltage(voltage, n_voltage);
		Serial.println("voltage: ");

		for (int i = 0; i < n_voltage; i++) {
			Serial.print((int)voltage[i]);

			if (i != n_voltage - 1)
				Serial.print(":");
		}

		Serial.println("");
		break;

	case s:
		ret = ll.GetSteering();
		Serial.println("steering: ");
		Serial.println(ret);
		break;

	case a:
		ret = ll.GetAverage();
		Serial.println("average: ");
		Serial.println(ret);
		break;

	case r:
		ret = ll.GetResult();
		Serial.println("result: ");
		Serial.println(ret);
		break;

	case p:
		ll.PutToSleep();
		delay(500);
		break;

	case u:
		ll.WakeUp();
		delay(250);
		break;
	}
}
