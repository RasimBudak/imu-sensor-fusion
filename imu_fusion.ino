// IMU Sensor Fusion for Arduino (MPU6050)
// Developed by Rasim Budak – 2025

#include <Wire.h>
#include <MPU6050.h>

MPU6050 imu;

float accX, accY, accZ;
float gyroX, gyroY, gyroZ;

float pitch = 0.0, roll = 0.0;
float accPitch, accRoll;
float dt = 0.01; // 10 ms
float alpha = 0.96;

unsigned long previousTime = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  imu.initialize();
  if (!imu.testConnection()) {
    Serial.println("MPU6050 connection failed!");
    while (1);
  }
  previousTime = millis();
}

void loop() {
  unsigned long currentTime = millis();
  dt = (currentTime - previousTime) / 1000.0;
  previousTime = currentTime;

  // Read raw data
  imu.getAcceleration(&accX, &accY, &accZ);
  imu.getRotation(&gyroX, &gyroY, &gyroZ);

  // Convert gyro to deg/s
  float gyroXrate = gyroX / 131.0;
  float gyroYrate = gyroY / 131.0;

  // Calculate accelerometer angles
  accPitch = atan2(accY, sqrt(accX * accX + accZ * accZ)) * 180 / PI;
  accRoll = atan2(-accX, accZ) * 180 / PI;

  // Complementary Filter
  pitch = alpha * (pitch + gyroXrate * dt) + (1 - alpha) * accPitch;
  roll = alpha * (roll + gyroYrate * dt) + (1 - alpha) * accRoll;

  // Output
  Serial.print("Pitch: ");
  Serial.print(pitch, 2);
  Serial.print(" | Roll: ");
  Serial.println(roll, 2);

  delay(10); // 100 Hz loop
}
