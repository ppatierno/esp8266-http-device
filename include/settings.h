#ifndef Settings_h
#define Settings_h

const char *ssid = "<WIFI-SSID>";
const char *password = "<WIFI-PASSWORD>";

const char *bridge = "<HTTP-BRIDGE-URL>";
const char *topic = "<KAFKA-TOPIC>";

const char *deviceId = "<DEVICE-ID>";

const int minTemperature = 20;
const int maxTemperature = 25;

const int minHumidity = 50;
const int maxHumidity = 55;

#define DHT11_SENSOR false

#endif