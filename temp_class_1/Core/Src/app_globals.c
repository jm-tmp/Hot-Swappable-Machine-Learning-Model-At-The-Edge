#include "app_globals.h"
#include "main.h"
#include "ai_platform.h"
#include "temp_classifier_data.h"
#include "dht11.h"

/* Peripheral handles */

CRC_HandleTypeDef hcrc;
I2C_HandleTypeDef hi2c1;
SPI_HandleTypeDef hspi1;
TIM_HandleTypeDef htim2;
UART_HandleTypeDef huart5;

/* AI memory */
ai_u8 activations[AI_TEMP_CLASSIFIER_DATA_ACTIVATIONS_SIZE];

/* Define the buffers based on what's available */
#if defined(AI_TEMP_CLASSIFIER_IN_1_SIZE_BYTES)
    ai_u8 in_data[AI_TEMP_CLASSIFIER_IN_1_SIZE_BYTES];
    ai_u8 out_data[AI_TEMP_CLASSIFIER_OUT_1_SIZE_BYTES];
#elif defined(AI_TEMP_CLASSIFIER_IN_1_SIZE)
    /* Calculate byte size from element size */
    ai_u8 in_data[AI_TEMP_CLASSIFIER_IN_1_SIZE * sizeof(ai_float)];
    ai_u8 out_data[AI_TEMP_CLASSIFIER_OUT_1_SIZE * sizeof(ai_float)];
#else
    /* Default fallback */
    #define TEMP_INPUT_SIZE  (1 * 1 * 1)
    #define TEMP_OUTPUT_SIZE (1 * 1 * 3)
    ai_u8 in_data[TEMP_INPUT_SIZE * sizeof(ai_float)];
    ai_u8 out_data[TEMP_OUTPUT_SIZE * sizeof(ai_float)];
#endif

ai_buffer *ai_input;
ai_buffer *ai_output;

/* Sensor + SPI */
DHT11_struct Dstruct;
float my_temperature = 0.0f;
uint8_t humidity = 0;

uint8_t spi_tx_buf[4];
uint8_t spi_rx_dummy[4];
