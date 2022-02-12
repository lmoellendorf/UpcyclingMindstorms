#include <LmMsLineLeaderV2.h>

MsLineLeaderV2 ll = MsLineLeaderV2();

void setup()
{
	char fw_str[9] = {0};
	size_t len = sizeof(fw_str) / sizeof(fw_str[0]);
	int ret;

	Serial.begin(115200);
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
}

void loop()
{
	int avg;
	char readings[8];
	size_t n_readings = sizeof(readings) / sizeof(readings[0]);

	avg = ll.GetCalibrated(readings, n_readings);
	Serial.println("calibrated: ");

	for (int i = 0; i < n_readings; i++)
		Serial.println((int)readings[i]);

	avg = ll.GetWhiteLimit(readings, n_readings);
	Serial.println("white limit: ");

	for (int i = 0; i < n_readings; i++)
		Serial.println((int)readings[i]);

	avg = ll.GetBlackLimit(readings, n_readings);
	Serial.println("black limit: ");

	for (int i = 0; i < n_readings; i++)
		Serial.println((int)readings[i]);

	avg = ll.GetWhiteCalibration(readings, n_readings);
	Serial.println("white calibration: ");

	for (int i = 0; i < n_readings; i++)
		Serial.println((int)readings[i]);

	avg = ll.GetBlackCalibration(readings, n_readings);
	Serial.println("black calibration: ");

	for (int i = 0; i < n_readings; i++)
		Serial.println((int)readings[i]);

	avg = ll.GetAvg();
	Serial.println("average: ");
	Serial.println(avg);

	delay(250);
	ll.PutToSleep();
	delay(500);
	ll.WakeUp();
	delay(250);
}
