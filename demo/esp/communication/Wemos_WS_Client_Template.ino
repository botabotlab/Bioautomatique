#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WebSocketsClient.h>


WiFiClient client;
WebSocketsClient webSocket;

const char* ssid = "SSID";
const char* password = "PASSWORD";
const char* HostName = "ESP8266_WS_CLIENT_DEMO";

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

//WS callback==========================================================
void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      Serial.println("Disconnected");
      break;
    case WStype_CONNECTED:
      Serial.printf("Connected to url: %s\n", payload);
      webSocket.sendTXT("Connected");
      break;
    case WStype_TEXT:
      Serial.printf("Received Text: %s\n", payload);
      break;
    case WStype_BIN:
      Serial.printf("Received binary length : %s\n", payload);
      hexdump(payload, length);
      //webSocket.sendBIN(payload, length);
      break;
  }
}
//WS callback==========================================================

//SETUP==================
void setup() {
  Serial.begin(115200);
  setup_wifi();
  webSocket.begin("192.168.8.200", 1880, "/ws/ping");
  webSocket.onEvent(webSocketEvent);
  webSocket.setReconnectInterval(5000);
  webSocket.sendTXT("PING");
}
//SETUP==================

//LOOP========
void loop() {
  webSocket.loop();
}
//LOOP========
