#include <Arduino.h>
#include <BluetoothSerial.h>
#include <WiFi.h>

#define USE_PIN
const char *pin = "1234";

#define RED_LED 32

String device_name = "ESP32-BT-Slave";
String ssid;
String password;

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial SerialBT;

String takeInput(int);
void getWiFiCredits();
void listNetworks();

void setup() {
    Serial.begin(115200);
    SerialBT.begin(device_name);
    Serial.printf("The device with name \"%s\" is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str());
#ifdef USE_PIN
    SerialBT.setPin(pin);
    Serial.println("Using PIN..");
#endif

    pinMode(RED_LED, OUTPUT);

    // List wifi networks to the user
    // get wifi credits
    // connect to wifi
    // if connection failed, try again
    while (true) {
        listNetworks();
        getWiFiCredits();
        // connect to network
        // if connected, break
    }
}

void loop() {
    delay(2000);
}

String takeInput(int device) {
    String msg;
    if (device == 0) {
        // ESP Serial
        msg = Serial.readString();
    } else {
        // Bluetooth Serial
        msg = SerialBT.readString();
    }
    msg.trim();
    return msg;
}

void getWiFiCredits() {
}

void listNetworks() {
    SerialBT.println("Scanning...");
    int numNetworks = WiFi.scanNetworks();
    delay(300);

    for (int i = 0; i < numNetworks; ++i) {
        SerialBT.printf("%d: %s (%d)  %s\n", i + 1, WiFi.SSID(i).c_str(),
                        WiFi.RSSI(i), WiFi.encryptionType(i) == WIFI_AUTH_OPEN ? "( )" : "(*)");
    }
}