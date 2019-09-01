#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include "settings.h"
#if DHT11_SENSOR
#include <DHT.h>
#endif

char endpoint[100];
char payload[100];

#if DHT11_SENSOR
#define DHTPIN D4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
#endif


void setup() {
  delay(1000);
  
  Serial.begin(9600);                  
  Serial.println("ESP8266 HTTP based sensors device");

  WiFi.mode(WIFI_OFF);
  delay(1000);
  WiFi.mode(WIFI_STA);

  WiFi.begin(ssid, password);
  Serial.println("");
 
  Serial.print("Connecting");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  sprintf(endpoint, "http://%s/topics/%s", bridge, topic);
  Serial.print("Bridge endpoint: ");
  Serial.println(endpoint);

  #if DHT11_SENSOR
  dht.begin();
  #endif
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  WiFiClient client;
  HTTPClient http;
  
  // establish connection with the bridge
  http.begin(client, endpoint);
  http.addHeader("Content-Type", "application/vnd.kafka.json.v2+json");

  // build the payload
  #if DHT11_SENSOR
  int temperature = (int) dht.readTemperature();
  #else
  int temperature = random(minTemperature, maxTemperature + 1);
  #endif
  sprintf(payload, "{ \"records\": [ { \"key\": \"%s\", \"value\": { \"deviceId\": \"%s\", \"temperature\": %d } } ] }", 
          deviceId, deviceId, temperature);
  Serial.print("Sending...");
  Serial.println(payload);

  // send the payload and close connection
  http.POST(payload);
  http.end();

  delay(5000);
}