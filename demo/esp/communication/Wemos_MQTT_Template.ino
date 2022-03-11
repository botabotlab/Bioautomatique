//#include <ESP8266WiFi.h>
#include <WiFi.h>
#include <PubSubClient.h>
WiFiClient espClient;
PubSubClient client(espClient);

const char* ssid = "SSID";
const char* password = "PASSWORD";
const char* mqtt_server = "192.168.178.100";
const char* HostName = "ESP8266_MQTT_SERIAL_DEMO";
const char* TopicPING = "demo/topic/ping";
const char* TopicPONG = "demo/topic/pong";

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
}
//WIFI SETUP=============================

//MQTT RECONNECT====================================================
void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect(HostName)) {
      Serial.println("connected");

      //SUBSCRIBE to Topics-------------
      client.subscribe(TopicPING);
      //--------------------------------

    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}
//MQTT RECONNECT====================================================


void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

//CALLBACK==================================================================
//Callback function called when a new payload is sent on a subscribed topic
void callback(String topic, byte * message, unsigned int length) {
  String messageTemp;
  //Read the Payload
  for (int i = 0; i < length; i++) {
    messageTemp += (char)message[i];
  }
  Serial.println(messageTemp);

  if (messageTemp == "PING") {
    client.publish(TopicPONG, "PONG");
  }
}
//CALLBACK==================================================================

//LOOP======================================================================
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
//LOOP======================================================================
