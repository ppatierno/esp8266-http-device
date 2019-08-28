#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include "settings.h"

char endpoint[100];
char payload[100];

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

  // initialize LED digital pin as an output.
  pinMode(2, OUTPUT);

  sprintf(endpoint, "http://%s/topics/%s", bridge, topic);
  Serial.print("Bridge endpoint: ");
  Serial.println(endpoint);
}

void loop() {
  // turn the LED on (HIGH is the voltage level)
  digitalWrite(2, HIGH);
  delay(1000);

  // turn the LED off by making the voltage LOW
  digitalWrite(2, LOW);

  // wait for a second
  delay(1000);

  WiFiClient client;
  HTTPClient http;
  
  // establish connection with the bridge
  http.begin(client, endpoint);
  http.addHeader("Content-Type", "application/vnd.kafka.json.v2+json");

  // build the payload
  int temperature = 29;
  sprintf(payload, "{ \"records\": [ { \"key\": \"%s\", \"value\": { \"deviceId\": \"%s\", \"temperature\": %d } } ] }", 
          deviceId, deviceId, temperature);
  Serial.print("Sending...");
  Serial.println(payload);

  // send the payload and close connection
  http.POST(payload);
  http.end();

  delay(5000);
}