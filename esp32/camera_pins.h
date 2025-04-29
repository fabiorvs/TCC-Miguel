#ifndef CAMERA_PINS_H
#define CAMERA_PINS_H

// Definição do modelo de câmera utilizado
#define CAMERA_MODEL_AI_THINKER  // Define que estamos usando a ESP32-CAM AI-Thinker

// Definição dos pinos para o modelo AI-Thinker
#define PWDN_GPIO_NUM 32   // Pino de desligamento da câmera (não utilizado, pode ser -1)
#define RESET_GPIO_NUM -1  // Pino de reset da câmera (não utilizado, pode ser -1)
#define XCLK_GPIO_NUM 0    // Clock do sensor de imagem
#define SIOD_GPIO_NUM 26   // Barramento I2C (SDA)
#define SIOC_GPIO_NUM 27   // Barramento I2C (SCL)

#define Y9_GPIO_NUM 35  // Dados da imagem (D0)
#define Y8_GPIO_NUM 34  // Dados da imagem (D1)
#define Y7_GPIO_NUM 39  // Dados da imagem (D2)
#define Y6_GPIO_NUM 36  // Dados da imagem (D3)
#define Y5_GPIO_NUM 21  // Dados da imagem (D4)
#define Y4_GPIO_NUM 19  // Dados da imagem (D5)
#define Y3_GPIO_NUM 18  // Dados da imagem (D6)
#define Y2_GPIO_NUM 5   // Dados da imagem (D7)

#define VSYNC_GPIO_NUM 25  // Sinal de sincronização vertical
#define HREF_GPIO_NUM 23   // Sinal de referência horizontal
#define PCLK_GPIO_NUM 22   // Clock do pixel (sincroniza a captura da imagem)

// Definição do LED embutido da ESP32-CAM
// Pode ser 4 para o flash LED ou 33 para um LED normal
#define LED_GPIO_NUM 4

#endif  // CAMERA_PINS_H
