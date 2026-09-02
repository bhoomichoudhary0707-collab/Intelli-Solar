# Intelli Solar ☀️

An Arduino-based intelligent solar tracking and temperature monitoring system developed during my internship.

## 📌 Overview

Intelli Solar is designed to track the direction of maximum sunlight using LDR sensors and automatically adjust a servo motor accordingly. The system also monitors temperature using a DHT11 sensor and displays the temperature on an OLED display.

A relay and buzzer are used for temperature-based automation and alerts.

## ✨ Features

- Automatic solar tracking using two LDR sensors
- Servo motor adjustment based on light intensity
- Temperature monitoring using a DHT11 sensor
- Temperature display on a 128×64 OLED display
- Relay control based on a temperature threshold
- Buzzer alert when the temperature reaches the set threshold

## 🔧 Components Used

- Arduino
- 2 × LDR Sensors
- Servo Motor
- DHT11 Temperature Sensor
- 128×64 OLED Display
- Relay Module
- Buzzer

## 📚 Libraries Used

- Wire
- Servo
- DHT Sensor Library
- Adafruit GFX Library
- Adafruit SSD1306 Library

## ⚙️ Working

### Solar Tracking

Two LDR sensors detect the light intensity from different directions. The Arduino compares their readings and adjusts the servo motor towards the direction with stronger light.

The servo movement is limited between 60° and 120°.

### Temperature Monitoring

The DHT11 sensor reads the surrounding temperature, which is displayed on the OLED screen.

When the temperature reaches 25°C or above:

- The relay is activated
- A buzzer alert is triggered

When the temperature drops below the threshold, the relay is turned off.

