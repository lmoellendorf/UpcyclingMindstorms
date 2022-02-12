#include <LmMsLineLeaderV2.h>

MsLineLeaderV2 ll = MsLineLeaderV2();

void setup()
{
	Serial.begin(115200);
}

void loop()
{
	char fw_str[9] = {0};
	size_t len = sizeof(fw_str) / sizeof(fw_str[0]);
	int ret;

	ret = ll.GetFwVersion(fw_str, len);

	if (!ret) {
		Serial.println("version: ");
		Serial.println(fw_str);
	}

	ret = ll.GetFwVendor(fw_str, len);

	if (!ret) {
		Serial.println("vendor: ");
		Serial.println(fw_str);
	}

	ret = ll.GetFwDevice(fw_str, len);

	if (!ret) {
		Serial.println("device: ");
		Serial.println(fw_str);
	}

	delay(250);
}
