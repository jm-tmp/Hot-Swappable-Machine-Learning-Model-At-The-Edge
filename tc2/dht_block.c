#include "dht_block.h"
#include "app_globals.h"
#include "dht11.h"
#include <stdio.h>

uint8_t DHT_Read_And_Print(void)
{
    uint8_t status = DHT11_rawread();

    if (status == 1)
    {
        my_temperature = DHT11_temp();
        humidity = DHT11_rh();

        printf("=== DHT11 Data ===\r\n");
        printf("Temperature: %.1f C\r\n", my_temperature);
        printf("Humidity: %d %%\r\n", humidity);
        printf("=================\r\n\r\n");
    }

    return status;
}
