#include <WiFi.h> //Inclui a biblioteca

const char* ssid = "Rede Ramon"; //Define o nome do ponto de acesso
const char* pass = "12345678"; //Define a senha
WiFiServer server(80); //Cria um servidor na porta 80

const byte ledPin = 2; //Define o pino do Led

void setup() {
  Serial.begin(115200); //Inicia o monitor serial

  pinMode(ledPin, OUTPUT); //Define o tipo da porta do Led
  delay(10);  //Atraso de 10 milissegundos

  Serial.println("\n"); //Pula uma linha
  WiFi.softAP(ssid, pass); //Inicia o ponto de acesso
  Serial.print("Se conectando a: "); //Imprime mensagem sobre o nome do ponto de acesso
  Serial.println(ssid);
  IPAddress ip = WiFi.softAPIP(); //Endereço de IP
  
  Serial.print("Endereço de IP: "); //Imprime o endereço de IP
  Serial.println(ip);
  server.begin(); //Inicia o servidor 
  Serial.println("Servidor online"); //Imprime a mensagem de início
}

void loop() {
  WiFiClient client = server.available(); //Cria o objeto cliente
  
  if (client) { //Se este objeto estiver disponível
    String line = ""; //Variável para armazenar os dados recebidos
    
    while (client.connected()) { //Enquanto estiver conectado
      if (client.available()) { //Se estiver disponível
        char c = client.read(); //Lê os caracteres recebidos
        if (c == '\n') { //Se houver uma quebra de linha
          if (line.length() == 0) { //Se a nova linha tiver 0 de tamanho
            client.println("HTTP/1.1 200 OK"); //Envio padrão de início de comunicação
            client.println("Content-type:text/html");
            client.println();
            client.print("<meta charset=\"utf-8\" />");
            client.print("<html>");
            client.print("<body style=\"text-align: center\">");
            client.print("<h1>Controle de Automação</h1>");
            client.print("<div><p>Luz da Sala</p></div>");
            client.print("<div><a href=\"/ligar\"><button>Ligar</button></a></div>");
            client.print("<div><a href=\"/desligar\"><button>Desligar</button></a></div>");
            client.print("</body>");
            client.print("</html>");
            client.println();
            break;
          } else {   
            line = "";
          }
        } else if (c != '\r') { 
          line += c; //Adiciona o caractere recebido à linha de leitura
        }
        if (line.endsWith("GET /ligar")) { //Se a linha terminar com "/ligar", liga o led
          digitalWrite(ledPin, HIGH);               
        }
        if (line.endsWith("GET /desligar")) { //Se a linha terminar com "/desligar", desliga o led
          digitalWrite(ledPin, LOW);              
        }
      }
    }
    client.stop(); //Para o cliente
  }
}