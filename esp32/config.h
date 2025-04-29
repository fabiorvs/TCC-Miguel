#ifndef CONFIG_H
#define CONFIG_H

// Configurações de WiFi
const char* WIFI_SSID = "AP03";            // Nome da rede WiFi
const char* WIFI_PASSWORD = "123";  // Senha do WiFi

// Configuração da API (Servidor HTTP)
const char* SERVER_HOST = "192.168.15.42";                      // IP do servidor
const int SERVER_PORT = 8080;                                   // Porta do servidor
const char* SERVER_URL = "http://192.168.15.42:8080/api/logs";  // URL da API

#endif  // CONFIG_H
