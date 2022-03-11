#include <ESP8266WiFi.h>
#include <WiFiClient.h>

WiFiClient client;
const char* ssid = "SSID";
const char* password = "PASSWORD";
const char* HostName = "ESP8266_TCP_SERVER_DEMO";

#define TCP_PORT 80
WiFiServer server(TCP_PORT);

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

//TCP Handle=============================
void TCPHandle() {
  WiFiClient client = server.available();
  if (client) {
    while (client.connected()) {
      while (client.available() > 0) {
        char c = client.read();
        Serial.write(c);
      }
      delay(10);
      client.write("PONG");
    }

    client.stop();
    Serial.println("Client disconnected");
  }
}
void setup() {
  Serial.begin(115200);
  setup_wifi();
  server.begin();
}

void loop() {
  TCPHandle();
}
