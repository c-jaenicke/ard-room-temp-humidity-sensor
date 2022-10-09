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
 * CONTAINS FUNCTIONS FOR DEBUGGING WIFI INFORMATION WHILE CONNECTED TO SERIAL
 * NOT NEEDED FOR NORMAL OPERATION
*/


// print wifi data
void printWifiData() {
  // print device ip adress
  IPAddress ip = WiFi.localIP();
  Serial.print("IP:\t\t");
  Serial.println(ip);
  // print your MAC address:
  byte mac[6];
  WiFi.macAddress(mac);
  Serial.print("MAC:\t\t");
  printMacAddress(mac);
}


// print information about current network
void printCurrentNet() {
  // get SSID of network
  Serial.print("SSID:\t\t");
  Serial.println(WiFi.SSID());
  // get mac address of device
  byte bssid[6];
  WiFi.BSSID(bssid);
  Serial.print("BSSID:\t\t");
  printMacAddress(bssid);
  // get recieved signal strength of network
  long rssi = WiFi.RSSI();
  Serial.print("RSSI:\t\t");
  Serial.println(rssi);
  // get encryption type of network
  //byte encryption = WiFi.encryptionType();
  //Serial.print("Encryption Type:");
  //Serial.println(encryption, HEX);
  //Serial.println();
}


// print mac address
void printMacAddress(byte mac[]) {
  for (int i = 5; i >= 0; i--) {
    if (mac[i] < 16) {
      Serial.print("0");
    }
    Serial.print(mac[i], HEX);
    if (i > 0) {
      Serial.print(":");
    }
  }
  Serial.println();
}