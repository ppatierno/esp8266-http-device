# ESP8266 HTTP device

This repository is about an embedded application running on [ESP8266](https://www.espressif.com/en/products/hardware/esp8266ex/overview) module in order to connect via HTTP protocol to an Apache Kafka cluster through a Kafka - HTTP bridge.
It's mostly related to use the [Strimzi Kafka - HTTP bridge](https://github.com/strimzi/strimzi-kafka-bridge) which is part of the [Strimzi](https://strimzi.io/) project which provides a way for deploying and managing an Apache Kafka cluster on Kubernetes.

The application is intended to be used with this [demo](https://github.com/ppatierno/rhte-2019) due to the current message payload format but it can be used as reference for a different scenario.

It was developed using the [PlatformIO](https://platformio.org/) framework and its extension for [VSCode](https://code.visualstudio.com/).

Before compiling and flashing the firmware on the ESP8266 board, the `settings.h` header should be updated with the following configuration parameters:

* `ssid`: the SSID of the WiFi network to connect to;
* `password`: the password of the WiFi network to connect to;
* `bridge`: the Kafka - HTTP bridge URL to connect to;
* `topic`: the topic to send messages to;
* `deviceId`: the device ID;

The application can be used emulating the temperature readings or with a real [DHT11](https://learn.adafruit.com/dht) sensor.
In order to enable/disable the real sensor, change the `DHT11_SENSOR` constant value (trut/false) in the `settings.h` header.