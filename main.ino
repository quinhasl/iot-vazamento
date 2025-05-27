#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "NOME_DA_SUA_REDE";
const char* password = "SENHA_DA_REDE";
const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;
const char* mqtt_topic = "mackenzie/leak_detection";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  conectarWiFi();
  client.setServer(mqtt_server, mqtt_port);
  pinMode(5, OUTPUT);
}

void loop() {
  if (!client.connected()) {
    reconectarMQTT();
  }
  client.loop();

  int umidade = analogRead(34);
  int vazao = pulseIn(12, HIGH);

  if (umidade > 2000 || vazao > 500) {
    String mensagem = "{\"umidade\":" + String(umidade) + ",\"vazao\":" + String(vazao) + "}";
    client.publish(mqtt_topic, mensagem.c_str());
    digitalWrite(5, HIGH);
    delay(10000);
    digitalWrite(5, LOW);
  }
  delay(2000);
}

void conectarWiFi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void reconectarMQTT() {
  while (!client.connected()) {
    if (client.connect("ESP32_CLIENT")) {
    } else {
      delay(5000);
    }
  }
}
