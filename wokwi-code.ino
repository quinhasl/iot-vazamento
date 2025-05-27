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

void setup() {
  Serial.begin(115200);
  pinMode(BOTAO_FLUXO, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);
  
  Serial.println("Conectando ao WiFi...");
  delay(1000);
  Serial.println("Conectado! IP: 192.168.1.100 (simulado)");
  
  client.setServer(mqtt_server, 1883);
  Serial.println("Configurando MQTT...");
  Serial.println("Broker: broker.hivemq.com:1883");
  Serial.println("Tópico: projeto-vazamento");
  Serial.println("----------------------------------");
}

void loop() {
  int umidade = analogRead(SENSOR_UMIDADE);
  int fluxo = digitalRead(BOTAO_FLUXO);

  if (umidade < 2000 || fluxo == LOW) {
    digitalWrite(BUZZER, HIGH);  
    
    Serial.println("[MQTT SIMULADO] Mensagem enviada para broker.hivemq.com:");
    Serial.println("Tópico: projeto-vazamento");
    Serial.println("Payload: {\"umidade\":" + String(umidade) + ", \"alerta\":\"VAZAMENTO DETECTADO\"}");
    Serial.println("----------------------------------");
    
    delay(3000);  
  } else {
    digitalWrite(BUZZER, LOW);
  }
}
