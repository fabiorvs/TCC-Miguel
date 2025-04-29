#ifndef CAMERA_H
#define CAMERA_H

// Inclusão das bibliotecas necessárias
#include <esp_camera.h>   // Biblioteca da câmera ESP32
#include "camera_pins.h"  // Definição dos pinos para o modelo AI-Thinker

/**
 * @brief Configura a câmera ESP32-CAM.
 * 
 * Define os pinos, resolução, qualidade da imagem e inicializa a câmera.
 * 
 * @return Retorna `true` se a inicialização for bem-sucedida, `false` caso contrário.
 */
bool setupCamera() {
  // Estrutura de configuração da câmera
  camera_config_t config;

  // Configuração do PWM do clock da câmera
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;

  // Mapeamento dos pinos do sensor da câmera OV2640
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sccb_sda = SIOD_GPIO_NUM;
  config.pin_sccb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;    // Power Down (não utilizado na maioria das placas)
  config.pin_reset = RESET_GPIO_NUM;  // Reset (pode ser -1 se não for usado)

  // Frequência do clock da câmera (20 MHz)
  config.xclk_freq_hz = 20000000;

  // Define o formato da imagem capturada (JPEG é melhor para streaming e envio)
  config.pixel_format = PIXFORMAT_JPEG;

  // Modo de captura de frame
  config.grab_mode = CAMERA_GRAB_WHEN_EMPTY;  // Captura apenas quando o buffer estiver vazio

  // Localização do buffer de frame (PSRAM economiza RAM interna)
  config.fb_location = CAMERA_FB_IN_PSRAM;

  // Configuração do tamanho da imagem capturada
  config.frame_size = FRAMESIZE_QVGA;  // 320x240 (pequena, economiza memória)

  // Define a qualidade da compressão JPEG (0 = melhor qualidade, 63 = pior qualidade)
  config.jpeg_quality = 12;  // Qualidade balanceada (arquivos menores, mas boa imagem)

  // Número de buffers para capturas múltiplas (maior = melhor performance, mas usa mais RAM)
  config.fb_count = 1;  // Apenas um buffer para evitar alto consumo de memória

  // Inicializa a câmera com as configurações definidas
  esp_err_t err = esp_camera_init(&config);

  // Retorna `true` se a inicialização for bem-sucedida, `false` caso contrário
  return err == ESP_OK;
}

/**
 * @brief Captura uma foto usando a ESP32-CAM.
 * 
 * @return Retorna um ponteiro para `camera_fb_t`, que contém os dados da imagem.
 */
camera_fb_t *capturarFoto() {
  return esp_camera_fb_get();  // Captura a imagem da câmera e retorna
}

#endif
