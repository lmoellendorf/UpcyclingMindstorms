#include <LmMsLineLeaderV2.h>

MsLineLeaderV2 ll = MsLineLeaderV2();

void setup()
{
	char fw_str[9] = {0};
	size_t len = sizeof(fw_str) / sizeof(fw_str[0]);
	int ret;

	Serial.begin(115200);
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

void loop()
{
	char readings[8];
	size_t n_readings = sizeof(readings) / sizeof(readings[0]);
	int voltage[8];
	size_t n_voltage = sizeof(voltage) / sizeof(voltage[0]);
	int ret;

	ret = ll.GetCalibrated(readings, n_readings);
	Serial.println("calibrated: ");

	for (int i = 0; i < n_readings; i++)
		Serial.println((int)readings[i]);

	ret = ll.GetWhiteLimit(readings, n_readings);
	Serial.println("white limit: ");

	for (int i = 0; i < n_readings; i++)
		Serial.println((int)readings[i]);

	ret = ll.GetBlackLimit(readings, n_readings);
	Serial.println("black limit: ");

	for (int i = 0; i < n_readings; i++)
		Serial.println((int)readings[i]);

	ret = ll.GetWhiteCalibration(readings, n_readings);
	Serial.println("white calibration: ");

	for (int i = 0; i < n_readings; i++)
		Serial.println((int)readings[i]);

	ret = ll.GetBlackCalibration(readings, n_readings);
	Serial.println("black calibration: ");

	for (int i = 0; i < n_readings; i++)
		Serial.println((int)readings[i]);

	ret = ll.GetVoltage(voltage, n_voltage);
	Serial.println("voltage: ");

	for (int i = 0; i < n_voltage; i++)
		Serial.println((int)voltage[i]);

	ret = ll.GetSteering();
	Serial.println("steering: ");
	Serial.println(ret);
	ret = ll.GetAverage();
	Serial.println("average: ");
	Serial.println(ret);
	ret = ll.GetResult();
	Serial.println("result: ");
	Serial.println(ret);

	delay(250);
	ll.PutToSleep();
	delay(500);
	ll.WakeUp();
	delay(250);
}
