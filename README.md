# Arduino Room sensor

Using an Arduino to monitor the temperature and relative humidity in a room, and pushing that data to a Prometheus Pushgateway.

## Hardware

- Arduino Nano 33 IoT
- Adafruit HTU21D-F Temperature & Humidity Sensor

| Device                                          | Price | Usage                                         |
| ----------------------------------------------- | ----- | --------------------------------------------- |
| Arduino Nano 33 IoT                             | 20 €  | Collecting the data and sending it to server  |
| Adafruit HTU21D-F Temperature & Humidity Sensor | 10 €  | getting measurements                          |
| Raspberry Pi 3 Model B                          | 45 €  | Server fr Prometheus, Pushgateway and Grafana |

## Arduino Libraries

| Library                                                                          | Version | Usage                           |
| -------------------------------------------------------------------------------- | ------- | ------------------------------- |
| [Adafruit_HTU21DF_Library](https://github.com/adafruit/Adafruit_HTU21DF_Library) | 1.1.0   | Getting data from sensor        |
| [ArduinoHttpClient](https://github.com/arduino-libraries/ArduinoHttpClient)      | 0.4.0   | Client for making push requests |
| [WiFiNINA](https://www.arduino.cc/reference/en/librarieswifinina/)               | 1.8.13  | Connecting to WiFi              |
|                                                                                  |         |                                 |
| And all requirements of the libraries above                                      |         |                                 |

## Requires config.h

This requires a `config.h` containing the secret values for your WiFi and Pushgateway server info.

```C++
// define wifi SSID and password to connect
#define WIFI_SSID "<SSID>"
#define WIFI_PASSWORD "<WPA2>"

// make sure to reserve a static ip address for your Pushgateway
#define PUSHGATEWAYIP "<PUSHGATEWAY IP>" // ip of the server running the Pushgateway
#define PORT 9091 // standard port of Prometheus Pushgateway
```

Replace `<>` with the corresponding data and remove the `<>`.
