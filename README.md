# IMU Sensor Fusion with Arduino

This project demonstrates how to estimate orientation angles (pitch and roll) using data from an MPU6050 IMU sensor on an Arduino board.

## 🎯 Objective

Convert raw accelerometer and gyroscope data into usable orientation angles using simple sensor fusion (Complementary Filter).

## 🔧 Hardware

- Arduino Uno or Nano
- MPU6050 IMU (I2C interface)
- Jumper wires

## 📐 Wiring

- VCC → 3.3V or 5V (depending on module)
- GND → GND
- SDA → A4 (Uno/Nano)
- SCL → A5 (Uno/Nano)

## 🧠 Algorithm

```text
angle = α * (angle + gyro * dt) + (1 - α) * accel_angle
