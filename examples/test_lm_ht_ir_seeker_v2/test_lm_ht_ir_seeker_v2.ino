#include <LmHtIrSeekerV2.h>

HtIrSeekerV2 seeker;

void setup()
{
	char fw_str[9] = {0};
	size_t len = sizeof(fw_str) / sizeof(fw_str[0]);
	int ret;

	seeker = HtIrSeekerV2(HtIrSeekerV2::Mode::AC);
	Serial.begin(115200);
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

void loop()
{
	int ret;
	int values[5];
	size_t n_values = sizeof(values) / sizeof(values[0]);

	ret = seeker.GetDirection();

	if (ret >= 0) {
		Serial.print("direction: ");
		Serial.println(ret);
	}

	ret = seeker.GetAngle(true);

	if (ret != -1) {
		Serial.print("angle: ");
		Serial.println(ret);
	}

	ret = seeker.GetSensorValues(values, n_values);

	if (ret >= 0) {
		for (int id = 0; id < n_values; id++) {
			Serial.print("value ");
			Serial.print(id);
			Serial.print(": ");
			Serial.println(values[id]);
		}
	}

	ret = seeker.GetAverage();

	if (ret >= 0) {
		Serial.print("average: ");
		Serial.println(ret);
	}

	while (!Serial.available())
		;

	Serial.read();
}
