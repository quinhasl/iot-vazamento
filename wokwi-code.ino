#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* mqtt_server = "broker.hivemq.com";

WiFiClient espClient;
PubSubClient client(espClient);

#define SENSOR_UMIDADE 0
#define BOTAO_FLUXO 2
#define BUZZER 3

unsigned long lastMsgTime = 0;
const long interval = 1000;

void setup() {
  Serial.begin(115200);
  
  pinMode(BOTAO_FLUXO, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);
  
  WiFi.begin(ssid, password);
  Serial.print("Conectando ao WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado!");
  
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  int umidade = analogRead(SENSOR_UMIDADE);
  int fluxo = digitalRead(BOTAO_FLUXO);

  if (umidade < 2000 || fluxo == LOW) {
    digitalWrite(BUZZER, HIGH);
    
    unsigned long now = millis();
    if (now - lastMsgTime > interval) {
      lastMsgTime = now;
      if (client.publish("projeto-vazamento", "ALERTA: VAZAMENTO DETECTADO!")) {
        Serial.println("Mensagem MQTT enviada!");
      } else {
        Serial.println("Falha no envio MQTT");
      }
    }
  } else {
    digitalWrite(BUZZER, LOW);
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensagem recebida [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando ao MQTT...");
    if (client.connect("ESP32-Wokwi")) {
      Serial.println("Conectado!");
      client.subscribe("projeto-vazamento");
    } else {
      Serial.print("Falha, rc=");
      Serial.print(client.state());
      Serial.println(" Tentando novamente em 5 segundos...");
      delay(5000);
    }
  }
}
