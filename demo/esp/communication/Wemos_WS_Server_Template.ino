#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WebSocketsServer.h>

WebSocketsServer webSocket = WebSocketsServer(80);
WiFiClient client;

const char* ssid = "SSID";
const char* password = "PASSWORD";
const char* HostName = "ESP8266_WS_SERVER_DEMO";

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
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      Serial.println("Disconnected");
      break;
    case WStype_CONNECTED:
      Serial.printf("Connected to url: %s\n", payload);
      webSocket.sendTXT(num, "Connected");
      break;
    case WStype_TEXT:
      Serial.printf("Received Text: %s\n", payload);
      webSocket.sendTXT(num, "PONG");
      break;
    case WStype_BIN:
      Serial.printf("Received binary length : %s\n", payload);
      hexdump(payload, length);
      //webSocket.sendBIN(num, payload, length);
      break;
  }
}
//WS callback==========================================================


void setup() {
  Serial.begin(115200);
  setup_wifi();
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);

}

void loop() {
  webSocket.loop();
}
