#include <LmHtIrSeekerV2.h>


void setup()
{
	HtIrSeekerV2 seeker = HtIrSeekerV2();
	char fw_str[9] = {0};
	size_t len = sizeof(fw_str) / sizeof(fw_str[0]);
	int ret;

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
}
