#include <LmMsLineLeaderV2.h>

MsLineLeaderV2 ll = MsLineLeaderV2();

void setup()
{
	Serial.begin(115200);
}

void loop()
{
	char version[9] = {0};
	char vendor[9] = {0};
	int ret;

	ret = ll.GetFwVersion(version, sizeof(version) / sizeof(version[0]));

	if (!ret) {
		Serial.println("version: ");
		Serial.println(version);
	}

	ret = ll.GetFwVendor(vendor, sizeof(vendor) / sizeof(vendor[0]));

	if (!ret) {
		Serial.println("vendor: ");
		Serial.println(vendor);
	}

	delay(250);
}
