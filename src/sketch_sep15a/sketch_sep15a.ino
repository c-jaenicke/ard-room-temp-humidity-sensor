/* Arduino Room Sensor
 * Using an Arduino to monitor the temperature and relative humidity in a room, and pushing that data to a Prometheus Pushgateway.
 * GitHub: https://github.com/c-jaenicke/zimmersensor
 * This requires a `config.h` containing the secret values for your WiFi and Pushgateway server info. Check README.md for more info 
 * https://github.com/c-jaenicke/zimmersensor/blob/main/README.md#requires-configh
 *
 * Requirements:
 *    Adafruit_HTU21DF_Library
 *    ArduinoHttpClient
 *    WiFiNINA
*/

// import standard libs for strings
#include <iostream>
#include <string>
using std::cout;
using std::cin;
using std::endl;
using std::string;

// include secrets file
#include "config.h"
//#include "network.h"

// sensors libraries
#include <Wire.h>
#include "Adafruit_HTU21DF.h"
// create sensor object
Adafruit_HTU21DF htu = Adafruit_HTU21DF();

// include wifi library
#include <SPI.h>
#include <WiFiNINA.h>
// import wifi network info
char ssid[] = WIFI_SSID;
char pass[] = WIFI_PASSWORD;
int status = WL_IDLE_STATUS;
// create wifi client object
WiFiClient wifi;

char pushgatewayIP[] = PUSHGATEWAYIP;
int port = PORT;

float rel_hum;
std::string humidityString;

float temp;
std::string tempString;

// include http client library
#include <ArduinoHttpClient.h>
// create client object
HttpClient client = HttpClient(wifi, pushgatewayIP, PORT);
HttpClient client2 = HttpClient(wifi, pushgatewayIP, PORT);

// run at beginning of boot
void setup() {
  // setup sensor
  Serial.begin(9600);
  Serial.println("--- Setup begin ---");

  // wait for serial to connect
  /*while (!Serial) {
    ; 
  }*/

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("!!! Communication with WiFi module failed !!!");
    // don't continue
    while (true)
      ;
  }

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);
    // wait 10 seconds for connection:
    delay(10000);
  }

  // print wifi network info
  Serial.print("--- Connection successful\n");
  //printCurrentNet();
  //printWifiData();

  // if sensor not connected
  if (!htu.begin()) {
    Serial.println("!!! Sensor not available !!!");
    while (1)
      ;
  }
}


void loop() {
  // test code for sensor
  //float temp = htu.readTemperature();
  //float rel_hum = htu.readHumidity();
  //Serial.print("Temp: "); Serial.print(temp); Serial.println(" C");
  //Serial.print("Humidity: "); Serial.print(rel_hum); Serial.println(" \%");
  //delay(10000);
  //printCurrentNet();

  request();

  // every 10 seconds
  // delay(10000);
  // every 1 second
  //delay(1000);
  // every 1 minute
  delay(60000);
  
}


// make post request to pushgateway
void request() {
  // get humidity data
  rel_hum = htu.readHumidity();
  //std::string hum =std::to_string(rel_hum);
  humidityString = "humidity ";
  humidityString.append(std::to_string(rel_hum));
  humidityString.append("\n");
  Serial.println(humidityString.c_str());

  temp = htu.readTemperature();
  //std::string hum =std::to_string(temp);
  tempString = "temperature ";
  tempString.append(std::to_string(temp));
  tempString.append("\n");
  Serial.println(tempString.c_str());

  humidityString.append(tempString);


  Serial.println("--- Making request");

  client.post("/metrics/job/pushgateway/pushgateway_inst/arduino", "text/plain", humidityString.c_str());

  // debugging sending of data
  // read the status code and body of the response
  int statusCode = client.responseStatusCode();
  String response = client.responseBody();

  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.print("Response: ");
  Serial.println(response);
}