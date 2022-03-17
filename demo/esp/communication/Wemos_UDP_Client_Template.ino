#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>

WiFiClient client;
const char* ssid = "SSID";
const char* password = "PASSWORD";
const char* HostName = "ESP8266_UDP_CLIENT_DEMO";

#define UDP_PORT 2880
#define UDP_SERVER "192.168.8.200"

WiFiUDP UDP;
char ping[] = "PING";

//WIFI SETUP=============================
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.hostname(HostName);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address : ");
  Serial.println(WiFi.localIP());
}
//WIFI SETUP=============================

void setup() {
  Serial.begin(115200);
  setup_wifi();

  //PING---------------------------------
  UDP.beginPacket(UDP_SERVER, UDP_PORT);
  Serial.println("Sending PING");
  UDP.write(ping);
  UDP.endPacket();
  //PING---------------------------------
}

void loop() {
}
