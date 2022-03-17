#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
WiFiClient client;
HTTPClient http;

const char* ssid = "SSID";
const char* password = "PASSWORD";
const char* HostName = "ESP8266_MQTT_HTTP_DEMO";
String server = "http://192.168.8.200:1880/ping";

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

//PING=======================================
int ping() {
  http.begin(client, server.c_str());
  int httpResponseCode = http.POST("PING");
  Serial.println("PING");
  Serial.print("Response : ");
  Serial.println(httpResponseCode);
  String respayload = http.getString();
  Serial.println(respayload);
  http.end();
  return(httpResponseCode);
}
//PING=======================================

//SETUP==================
void setup() {
  Serial.begin(115200);
  setup_wifi();
  ping();
}
//SETUP==================

//LOOP========
void loop() {
}
//LOOP========
