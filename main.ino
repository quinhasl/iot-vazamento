#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "kmdf_5g";
const char* password = "06454charlotte";
const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;
const char* mqtt_topic = "mackenzie/leak_detection";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  pinMode(5, OUTPUT);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) {
    while (!client.connect("ESP32_CLIENT")) delay(5000);
  }
  client.loop();

  int umidade = analogRead(34);
  int vazao = pulseIn(12, HIGH);

  if (umidade > 2000 || vazao > 500) {
    String payload = "{\"umidade\":"+String(umidade)+",\"vazao\":"+String(vazao)+"}";
    client.publish(mqtt_topic, payload.c_str());
    digitalWrite(5, HIGH);
    delay(10000);
    digitalWrite(5, LOW);
  }
  delay(2000);
}
