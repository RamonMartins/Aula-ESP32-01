#include <WiFi.h>
#include <PubSubClient.h>

// Informações da rede WiFi
const char* ssid = "ESPACO S";
const char* password = "senai@2019";

// Informações do Broker MQTT
const char* mqtt_server = "192.168.0.58";
const int mqtt_port = 1883; // A porta padrão do MQTT é 1883

WiFiClient espClient;
PubSubClient client(espClient);

// Função para reconexão ao Broker MQTT
void reconnect() {
  while (!client.connected()) {
    Serial.print("Tentando se conectar ao MQTT Broker...");
    if (client.connect("ESP32Client")) {
      Serial.println("Conectado ao MQTT Broker!");
    } else {
      Serial.print("Falha na conexão, rc=");
      Serial.print(client.state());
      Serial.println(" Tentando novamente em 5 segundos...");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao WiFi...");
  }

  Serial.println("Conectado ao WiFi!");

  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }

  // Publica uma mensagem em um tópico
  char message[50];
  snprintf(message, 50, "L");
  client.publish("home_artur/sensor", message);

  // Aguarda 2 segundos antes de publicar novamente
  delay(2000);
}
