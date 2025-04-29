// Inclusão das bibliotecas necessárias
#include <WiFi.h>         // Biblioteca para conexão WiFi
#include "camera.h"       // Biblioteca para configuração e captura da câmera
#include "http_post.h"    // Biblioteca para envio da imagem capturada
#include "camera_pins.h"  // Definição dos pinos usados pela câmera
#include "config.h"       // Importa as configurações de WiFi e API

// Definição dos pinos
#define LED_PIN 4      // Pino do LED embutido da ESP32-CAM
#define SENSOR_PIN 13  // Pino do sensor de movimento PIR

// Variável para armazenar o estado do sensor de movimento
bool estadoSensor = false;

// Função de configuração do sistema (executada uma única vez no início)
void setup() {
  Serial.begin(115200);  // Inicializa a comunicação serial com baud rate de 115200

  // Configuração dos pinos de entrada e saída
  pinMode(LED_PIN, OUTPUT);    // Define o LED como saída
  pinMode(SENSOR_PIN, INPUT);  // Define o sensor PIR como entrada

  // Garante que o LED inicie apagado ao ligar a ESP32-CAM
  digitalWrite(LED_PIN, LOW);
  Serial.println("LED apagado ao iniciar.");

  // Configuração do WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);  // Inicia a conexão com o WiFi
  WiFi.setSleep(false);                  // Desativa o modo de economia de energia do WiFi

  // Aguarda a conexão WiFi
  Serial.print("Conectando ao WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);  // Aguarda 500ms antes de verificar novamente
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado!");  // Exibe no monitor serial que o WiFi foi conectado com sucesso
  Serial.print("IP do ESP32-CAM: ");
  Serial.println(WiFi.localIP()); //Exibe o IP do dispositivo
}

// Função principal (executada em loop)
void loop() {
  int leitura = digitalRead(SENSOR_PIN);  // Lê o estado do sensor de movimento

  if (leitura == HIGH) {          // Se o sensor detectar movimento
    digitalWrite(LED_PIN, HIGH);  // Liga o LED indicando que movimento foi detectado

    if (!estadoSensor) {  // Se o estado do sensor for falso (para evitar capturas repetidas)
      Serial.println("Movimento Detectado");
      estadoSensor = true;  // Atualiza o estado do sensor para evitar novas capturas em sequência

      Serial.println("Desativando câmera (caso esteja ativa)...");
      esp_camera_deinit();  // Desativa a câmera para garantir que ela não estava ativa
      delay(100);           // Pequeno delay para liberar memória antes de reiniciar a câmera

      Serial.println("Iniciando câmera...");
      if (!setupCamera()) {                                // Inicializa a câmera para capturar a foto
        Serial.println("Falha ao inicializar a câmera!");  // Caso ocorra falha, exibe mensagem de erro
      } else {
        Serial.println("ESP32-CAM AI-Thinker iniciada com sucesso.");
        delay(500);  // Pequeno delay para evitar erro na captura

        camera_fb_t* foto = capturarFoto();  // Captura uma nova foto

        if (foto != nullptr) {  // Se a foto foi capturada com sucesso
          Serial.println("Nova foto capturada! Enviando...");
          enviarFoto(foto);            // Envia a foto para o servidor
          esp_camera_fb_return(foto);  // Libera a memória utilizada pela foto
        } else {
          Serial.println("Falha ao capturar nova foto.");  // Se a captura falhar, exibe erro
        }

        Serial.println("Desativando câmera...");
        esp_camera_deinit();  // Desativa a câmera para economizar memória
        delay(100);           // Pequeno delay para estabilizar antes de continuar
      }
    }

    delay(2000);                 // Mantém o LED ligado por 2 segundos
    digitalWrite(LED_PIN, LOW);  // Apaga o LED indicando que a captura foi finalizada
    Serial.println("LED apagado");
    delay(10000);  // Aguarda 10 segundos antes de permitir outra detecção
    Serial.println("Aguardando nova detecção...");
    estadoSensor = false;  // Reseta o estado do sensor para permitir novas capturas
  }
}
