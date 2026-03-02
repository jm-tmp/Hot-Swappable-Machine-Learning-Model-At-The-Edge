#include "uart_block.h"
#include "app_globals.h"

int _write(int file, char *ptr, int len)
{
    HAL_UART_Transmit(&huart5, (uint8_t*)ptr, len, 1000);
    return len;
}


