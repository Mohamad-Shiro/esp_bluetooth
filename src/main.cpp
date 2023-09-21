#include <Arduino.h>
#include <BluetoothSerial.h>
#include <PubSubClient.h>
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
bool connectToNetwork(int timeOut = 5000);

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
        if (SerialBT.connected()) {
            listNetworks();
            getWiFiCredits();
            SerialBT.end();
            if (connectToNetwork())
                break;
            else {
                SerialBT.begin(device_name);
                Serial.println("Failed to connect. try again...");
                delay(400);
            }
        }
    }
}

void loop() {
    if (WiFi.status() == WL_CONNECTED) {
        Serial.printf("connected to %s.\n", WiFi.SSID().c_str());
    }
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
    int state = 0;
    while (state != 4) {
        switch (state) {
            case 0:
                SerialBT.println("Enter WIFI name: ");
                state = 1;
                break;

            case 1:
                while (true) {
                    if (SerialBT.available()) {
                        ssid = SerialBT.readString();
                        ssid.trim();
                        state = 2;
                        break;
                    }
                }
                break;

            case 2:
                SerialBT.println("Enter WIFI password: ");
                state = 3;
                break;

            case 3:
                while (true) {
                    if (SerialBT.available()) {
                        password = SerialBT.readString();
                        password.trim();
                        state = 4;
                        break;
                    }
                }
                break;
            default:
                break;
        }
    }

    Serial.printf("ssid: %s, password: %s\n", ssid.c_str(), password.c_str());
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

bool connectToNetwork(int timeOut) {
    WiFi.mode(WIFI_STA);
    Serial.printf("Connecting to: %s", ssid.c_str());
    long initTime = millis();
    long lastTime = millis();
    while (WiFi.status() != WL_CONNECTED && (lastTime - initTime) < timeOut) {
        WiFi.begin(ssid, password);
        lastTime = millis();
        Serial.print(".");
        delay(200);
    }
    if (WiFi.status() == WL_CONNECTED) {
        Serial.printf("Connected to Wi-Fi with local IP: %s\n", WiFi.localIP().toString().c_str());
        return 1;
    } else {
        return 0;
    }
}