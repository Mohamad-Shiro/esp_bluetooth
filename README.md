# ESP32 Bluetooth and WiFi Integration

This project demonstrates how to create an ESP32-based device that communicates with a mobile phone application over Bluetooth to configure WiFi credentials and subsequently connect to a WiFi network. Once connected, the ESP32 can perform various tasks or operations depending on your application.

## Table of Contents
- [Features](#features)
- [Prerequisites](#prerequisites)
- [Hardware Setup](#hardware-setup)
- [Usage](#usage)

## Features
- Bluetooth communication with a mobile application to set WiFi credentials.
- Scanning and listing available WiFi networks.
- Automatic connection to a specified WiFi network.
- Status monitoring for WiFi connectivity.

## Prerequisites
Before you begin, ensure you have the following:

- An ESP32 development board.
- Arduino IDE with ESP32 support installed.
- A mobile phone with a Bluetooth-enabled app for communication (e.g., a custom app or a Bluetooth terminal app).
- USB cable for programming the ESP32.
- A WiFi network to which the ESP32 will connect.

## Hardware Setup
1. Connect the ESP32 to your computer via USB.
2. Install the required libraries from library manager depending on your IDE:
   - `BluetoothSerial` (for Bluetooth communication).
   - `WiFi` (for WiFi connectivity).
3. Upload the provided code to your ESP32.

## Usage
1. Flash the ESP32 with the uploaded code.
2. Power on the ESP32.
3. On your mobile phone, open a Bluetooth terminal app or your custom app that supports Bluetooth communication.
4. Pair your mobile phone with the ESP32 device.
5. Send WiFi credentials to the ESP32 over Bluetooth. The credentials should be in the format: `SSID*PASSWORD`, where `SSID` is the WiFi network name, and `PASSWORD` is the WiFi password.
6. The ESP32 will attempt to connect to the specified WiFi network.
7. Once connected, you can expand the project's functionality based on your requirements.
