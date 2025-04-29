#ifndef HTTP_POST_H
#define HTTP_POST_H

#include <WiFi.h>        // Biblioteca para conexão WiFi
#include <HTTPClient.h>  // Biblioteca para requisições HTTP
#include "config.h"      // Importa as configurações do servidor e WiFi

/**
 * @brief Envia uma foto para o servidor via HTTP POST.
 * 
 * A imagem é enviada no formato `multipart/form-data`, junto com os dados do sensor.
 * 
 * @param foto Ponteiro para `camera_fb_t`, que contém a imagem capturada.
 */
void enviarFoto(camera_fb_t* foto) {
  // Verifica se a foto capturada é válida
  if (foto == nullptr) {
    Serial.println("Erro: Foto inválida.");
    return;  // Sai da função sem enviar nada
  }

  // Verifica se o WiFi está conectado antes de tentar enviar a imagem
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi desconectado. Tentando reconectar...");
    WiFi.reconnect();  // Tenta reconectar ao WiFi
    delay(3000);
    if (WiFi.status() != WL_CONNECTED) {  // Se ainda estiver desconectado, cancela o envio
      Serial.println("Falha ao reconectar. Cancelando envio.");
      return;
    }
  }

  // Criação do objeto HTTP para enviar a requisição
  HTTPClient http;
  WiFiClient client;

  // Testa a conexão com o servidor antes de enviar os dados
  Serial.println("Testando conexão com o servidor...");
  if (!client.connect(SERVER_HOST, SERVER_PORT)) {
    Serial.println("Erro: Não foi possível conectar ao servidor!");
    return;
  }
  Serial.println("Conectado ao servidor!");

  // Inicializa a conexão HTTP
  Serial.println("Iniciando envio da imagem...");
  if (!http.begin(client, SERVER_URL)) {
    Serial.println("Falha ao iniciar a conexão HTTP.");
    return;
  }

  // Define o boundary do multipart/form-data
  String boundary = "----ESP32Boundary";

  // Cabeçalho da requisição HTTP com os campos do formulário
  String head = "--" + boundary + "\r\n";
  head += "Content-Disposition: form-data; name=\"sensor_id\"\r\n\r\n1\r\n";
  head += "--" + boundary + "\r\n";
  head += "Content-Disposition: form-data; name=\"mensagem\"\r\n\r\nMovimento detectado\r\n";
  head += "--" + boundary + "\r\n";
  head += "Content-Disposition: form-data; name=\"imagem\"; filename=\"foto.jpg\"\r\n";
  head += "Content-Type: image/jpeg\r\n\r\n";

  // Rodapé da requisição HTTP
  String tail = "\r\n--" + boundary + "--\r\n";

  // Calcula o tamanho total da requisição HTTP (cabeçalho + imagem + rodapé)
  int contentLength = head.length() + foto->len + tail.length();
  Serial.printf("Tamanho total da requisição: %d bytes\n", contentLength);

  // Verifica se a imagem é muito grande para ser enviada
  if (contentLength > 150000) {
    Serial.println("Erro: Foto muito grande para envio!");
    esp_camera_fb_return(foto);  // Libera a memória da imagem
    return;
  }

  // Define os cabeçalhos da requisição HTTP
  http.addHeader("Content-Type", "multipart/form-data; boundary=" + boundary);
  http.addHeader("Content-Length", String(contentLength));

  Serial.println("Enviando foto...");

  // Monta e envia a requisição completa (cabeçalho + imagem + rodapé)
  int httpResponseCode = http.POST(head + String((char*)foto->buf, foto->len) + tail);

  // Verifica a resposta do servidor
  if (httpResponseCode > 0) {
    Serial.println("Resposta do servidor: " + http.getString());
  } else {
    Serial.printf("Erro ao enviar a imagem. Código HTTP: %d\n", httpResponseCode);
  }

  // Encerra a conexão HTTP
  http.end();
  Serial.println("Envio finalizado.");
}

#endif  // HTTP_POST_H
