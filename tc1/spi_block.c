#include "spi_block.h"
#include "app_globals.h"
#include <string.h>

void SPI_Send_Temperature_Block(void)
{
    memcpy(spi_tx_buf, &my_temperature, sizeof(float));

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
    HAL_Delay(1);

    HAL_SPI_TransmitReceive(
        &hspi1,
        spi_tx_buf,
        spi_rx_dummy,
        sizeof(spi_tx_buf),
        HAL_MAX_DELAY
    );

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
}
