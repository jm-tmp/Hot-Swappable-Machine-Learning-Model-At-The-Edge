#ifndef APP_GLOBALS_H
#define APP_GLOBALS_H

#include "main.h"
#include "ai_platform.h"
#include "temp_classifier_data.h"
#include "dht11.h"

/* Peripheral handles */
extern CRC_HandleTypeDef hcrc;
extern I2C_HandleTypeDef hi2c1;
extern SPI_HandleTypeDef hspi1;
extern TIM_HandleTypeDef htim2;
extern UART_HandleTypeDef huart5;

/* AI buffers */
extern ai_u8 activations[AI_TEMP_CLASSIFIER_DATA_ACTIVATIONS_SIZE];

/* Check what's actually defined in temp_classifier_data.h and use those */
/* Common patterns: */
/* AI_TEMP_CLASSIFIER_IN_1_SIZE or AI_TEMP_CLASSIFIER_IN_1_SIZE_BYTES */
/* AI_TEMP_CLASSIFIER_OUT_1_SIZE or AI_TEMP_CLASSIFIER_OUT_1_SIZE_BYTES */

/* Try one of these approaches: */
#if defined(AI_TEMP_CLASSIFIER_IN_1_SIZE_BYTES)
    extern ai_u8 in_data[AI_TEMP_CLASSIFIER_IN_1_SIZE_BYTES];
    extern ai_u8 out_data[AI_TEMP_CLASSIFIER_OUT_1_SIZE_BYTES];
#elif defined(AI_TEMP_CLASSIFIER_IN_1_SIZE)
    /* Calculate byte size from element size */
    extern ai_u8 in_data[AI_TEMP_CLASSIFIER_IN_1_SIZE * sizeof(ai_float)];
    extern ai_u8 out_data[AI_TEMP_CLASSIFIER_OUT_1_SIZE * sizeof(ai_float)];
#else
    /* Default fallback - adjust based on your model */
    #define TEMP_INPUT_SIZE  (1 * 1 * 1)    /* 1x1x1 tensor for single temperature value */
    #define TEMP_OUTPUT_SIZE (1 * 1 * 3)    /* 1x1x3 tensor for 3 classes */
    extern ai_u8 in_data[TEMP_INPUT_SIZE * sizeof(ai_float)];
    extern ai_u8 out_data[TEMP_OUTPUT_SIZE * sizeof(ai_float)];
#endif

extern ai_buffer *ai_input;
extern ai_buffer *ai_output;

/* Sensor + SPI */
extern DHT11_struct Dstruct;
extern float my_temperature;
extern uint8_t humidity;

extern uint8_t spi_tx_buf[4];
extern uint8_t spi_rx_dummy[4];

#endif
