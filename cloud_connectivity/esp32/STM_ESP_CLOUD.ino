#include "driver/spi_slave.h"
#include "driver/gpio.h"
#include <string.h>
#include <SPI.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

#define PIN_MISO 19
#define PIN_MOSI 23
#define PIN_SCLK 18
#define PIN_CS 5

const char* ssid = "Tej";
const char* password = "123456789";

const char* apiUrl =
"https://i28ep61oy8.execute-api.ap-south-1.amazonaws.com/prod/sensor";
WiFiClientSecure client;
spi_slave_transaction_t t;
uint8_t rxBuf[4];

void setup()
{
  Serial.begin(115200);
   WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");

  client.setInsecure(); // testing only
  Serial.println("ESP32 SPI SLAVE READY");

  spi_bus_config_t buscfg = {
    .mosi_io_num = PIN_MOSI,
    .miso_io_num = PIN_MISO,
    .sclk_io_num = PIN_SCLK,
    .quadwp_io_num = -1,
    .quadhd_io_num = -1
  };

  spi_slave_interface_config_t slvcfg = {
    .spics_io_num = PIN_CS,
    .flags = 0,
    .queue_size = 1,
    .mode = 0,
    .post_setup_cb =NULL,
    .post_trans_cb =NULL
  };

  gpio_set_pull_mode((gpio_num_t)PIN_MOSI, GPIO_PULLUP_ONLY);
  gpio_set_pull_mode((gpio_num_t)PIN_SCLK, GPIO_PULLUP_ONLY);
  gpio_set_pull_mode((gpio_num_t)PIN_CS, GPIO_PULLUP_ONLY);

  spi_slave_initialize(VSPI_HOST, &buscfg, &slvcfg, SPI_DMA_DISABLED);
}

void loop()
{
 memset(rxBuf, 0, sizeof(rxBuf));

t.length = 8 * sizeof(rxBuf);
t.rx_buffer = rxBuf;
t.tx_buffer = NULL;

spi_slave_transmit(VSPI_HOST, &t, portMAX_DELAY);

float temperature ;//= rxBuf[0];
//Serial.print("rxBuf: ");
// Serial.println(rxBuf[0]);
memcpy(&temperature, rxBuf, sizeof(float));
Serial.println("start");/*
for (int i = 0; i < 4; i++) {
    Serial.println(rxBuf[i]);  
  }*/
Serial.print("Temperature: ");
Serial.println(temperature) ;
delay(3);
postTemperature(temperature);
}
void postTemperature(float temp) {
  HTTPClient http;
  http.begin(client, apiUrl);
  http.addHeader("Content-Type", "application/json");

  String json = "{";
  json += "\"deviceId\":\"stm32_01\",";
  json += "\"temperature\":" + String(temp, 2);
  json += "}";

  int code = http.POST(json);

  
  if (code > 0) {
    String response = http.getString();
    Serial.println("Server response:");
    Serial.println(response);
  }else {
    Serial.println("POST failed");
  }

  http.end();
}