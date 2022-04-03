#include <LmHtIrSeekerV2.h>

HtIrSeekerV2 seeker;

void getDeviceInfo(void)
{
	char fw_str[9] = {0};
	size_t len = sizeof(fw_str) / sizeof(fw_str[0]);
	int ret;

	ret = seeker.GetVersion(fw_str, len);

	if (!ret) {
		Serial.println("version: ");
		Serial.println(fw_str);
	}

	ret = seeker.GetVendorId(fw_str, len);

	if (!ret) {
		Serial.println("vendor: ");
		Serial.println(fw_str);
	}

	ret = seeker.GetDeviceId(fw_str, len);

	if (!ret) {
		Serial.println("device: ");
		Serial.println(fw_str);
	}
}

void setup()
{
	seeker = HtIrSeekerV2();
	Serial.begin(115200);
	/* wait untill the sensor is fully powered */
	delay(1);
	getDeviceInfo();
}

void loop()
{
	int values[5];
	size_t n_values = sizeof(values) / sizeof(values[0]);
	char key;
	const char v = 'v';
	const char d = 'd';
	const char a = 'a';
	const char V = 'V';
	const char A = 'A';
	int ret;

	Serial.print(v);
	Serial.println(": GetVersion, GetVendorId, GetDeviceId");
	Serial.print(d);
	Serial.println(": GetDirection");
	Serial.print(a);
	Serial.println(": GetAngle");
	Serial.print(V);
	Serial.println(": GetSensorValues");
	Serial.print(A);
	Serial.println(": GetAverage");

	while (!Serial.available())
		;

	key = Serial.read();

	switch (key) {
	case v:
		getDeviceInfo();
		break;

	case d:
		ret = seeker.GetDirection();

		if (ret >= 0) {
			Serial.print("direction: ");
			Serial.println(ret);
		}

		break;

	case a:
		ret = seeker.GetAngle(true);

		if (ret != -1) {
			Serial.print("angle: ");
			Serial.println(ret);
		}

		break;

	case V:
		ret = seeker.GetSensorValues(values, n_values);

		if (ret >= 0) {
			for (int id = 0; id < n_values; id++) {
				Serial.print("value ");
				Serial.print(id);
				Serial.print(": ");
				Serial.println(values[id]);
			}
		}

		break;

	case A:
		ret = seeker.GetAverage();

		if (ret >= 0) {
			Serial.print("average: ");
			Serial.println(ret);
		}
	}
}
