const int analogPin = A6;
const float R1 = 470000.0; // 470kΩ
const float R2 = 47000.0;  // 47kΩ

void setup() {
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(analogPin);
  float voltage = sensorValue * (5.0 / 1024.0);
  float batteryVoltage = voltage * ((R1 + R2) / R2);
  
  Serial.print("Battery Voltage: ");
  Serial.print(batteryVoltage);
  Serial.println(" V");
  
  delay(1000);
}
