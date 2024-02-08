#include <LmMsIRThermometer.h>

MsIRThermometer irt = MsIRThermometer();

void getDeviceInfo(void) {
  char fw_str[9] = { 0 };
  size_t len = sizeof(fw_str) / sizeof(fw_str[0]);
  int ret;

  ret = irt.getVersion(fw_str, len);

  if (!ret) {
    Serial.println("version: ");
    Serial.println(fw_str);
  }

  ret = irt.getVendorId(fw_str, len);

  if (!ret) {
    Serial.println("vendor: ");
    Serial.println(fw_str);
  }

  ret = irt.getDeviceId(fw_str, len);

  if (!ret) {
    Serial.println("device: ");
    Serial.println(fw_str);
  }
}

void setup() {
  Serial.begin(9600);
  getDeviceInfo();
}

void loop() {
  char key;
  const char v = 'v';
  const char a = 'a';
  const char t = 't';
  const char A = 'A';
  const char T = 'T';
  const char p = 'p';
  float temp;
  int addr;
  int ret;

  Serial.print(v);
  Serial.println(": getVersion, getVendorId, getDeviceId");
  Serial.print(a);
  Serial.println(": get ambient temperature in C");
  Serial.print(t);
  Serial.println(": get target temperature in C");
  Serial.print(A);
  Serial.println(": get ambient temperature in F");
  Serial.print(T);
  Serial.println(": get target temperature in F");
  Serial.print(p);
  Serial.println(": probe address");

  while (!Serial.available())
    ;

  key = Serial.read();

  switch (key) {
    case v:
      getDeviceInfo();
      break;

    case a:
      temp = irt.getAmbientTemperatureC();

      if (temp < 0) {
        Serial.print("Error: ");
        Serial.println((int)temp);
      } else {
        Serial.print("Ambient temperature: ");
        Serial.print(temp);
        Serial.println("C");
      }
      break;

    case t:
      temp = irt.getTargetTemperatureC();
      if (temp < 0) {
        Serial.print("Error: ");
        Serial.println((int)temp);
      } else {
        Serial.print("Target temperature: ");
        Serial.print(temp);
        Serial.println("C");
      }
      break;

    case A:
      temp = irt.getAmbientTemperatureF();
      if (temp < 0) {
        Serial.print("Error: ");
        Serial.println((int)temp);
      } else {
        Serial.print("Ambient temperature: ");
        Serial.print(temp);
        Serial.println("F");
      }
      break;

    case T:
      temp = irt.getTargetTemperatureF();
      if (temp < 0) {
        Serial.print("Error: ");
        Serial.println((int)temp);
      } else {
        Serial.print("Target temperature: ");
        Serial.print(temp);
        Serial.println("F");
      }
      break;

    case p:
      addr = irt.probeAddress();
      Serial.print("I2C address: ");
      Serial.println(addr);
      break;

    default:
      break;
  }
}
