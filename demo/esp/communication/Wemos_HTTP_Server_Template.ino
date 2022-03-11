#include <ESP8266WiFi.h>
WiFiServer server(80);

const char* ssid = "SSID";
const char* password = "PASSWORD";
const char* HostName = "ESP8266_HTTP_SERVER_DEMO";
String header;

unsigned long currentTime = millis();
unsigned long previousTime = 0;
const long timeoutTime = 2000;

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
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}
//WIFI SETUP=============================

//SETUP=================
void setup() {
  Serial.begin(115200);
  setup_wifi();
}
//SETUP=================

//LOOP===========================================================================
void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New Client.");
    String currentLine = "";
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) {
      currentTime = millis();
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        header += c;
        if (c == '\n') {
          if (header.indexOf("POST /ping") >= 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text");
            client.println("Connection: close");
            client.println();

            Serial.println("PONG");
            client.println("PONG");
            client.println();
            client.println();
            header = "";
            client.stop();
            Serial.println("Client disconnected.");
          }
        }
      }
    }
  }
}
//LOOP===========================================================================
