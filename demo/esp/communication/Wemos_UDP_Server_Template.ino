#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>

WiFiClient client;
const char* ssid = "SSID";
const char* password = "PASSWORD";
const char* HostName = "ESP8266_UDP_SERVER_DEMO";

#define UDP_PORT 2880
WiFiUDP UDP;
char packet[255];
char reply[] = "PONG";

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

//UDP
void UDPHandle() {
  int packetSize = UDP.parsePacket();
  if (packetSize) {
    Serial.print("Received packet! Size: ");
    Serial.println(packetSize);
    int len = UDP.read(packet, 255);
    if (len > 0)
    {
      packet[len] = '\0';
    }
    Serial.print("Packet received: ");
    Serial.println(packet);

    // Send return packet
    UDP.beginPacket(UDP.remoteIP(), UDP.remotePort());
    UDP.write(reply);
    UDP.endPacket();
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  UDP.begin(UDP_PORT);
  Serial.printf("Listening on UDP port : %d \n", UDP_PORT);
}

void loop() {
  UDPHandle();
}
