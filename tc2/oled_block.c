#include "oled_block.h"
#include "app_globals.h"
#include "ssd1306.h"
#include "ssd1306_fonts.h"
#include "ai_block.h"
#include <stdio.h>

void OLED_Init_Block(void)
{
    ssd1306_Init();
}

void OLED_Update_Block(int8_t label_idx)
{
    char buf[15];
    char *labels[3] = { "Cold", "Warm", "Hot" };

    ssd1306_Fill(Black);

    ssd1306_SetCursor(2, 2);
    ssd1306_WriteString("M2", Font_7x10, White);

    ssd1306_SetCursor(2, 10);
    ssd1306_WriteString("Temperature", Font_11x18, White);

    snprintf(buf, 15, "%0.1f", my_temperature);
    ssd1306_SetCursor(32, 30);
    ssd1306_WriteString(buf, Font_11x18, White);

    ssd1306_SetCursor(30, 46);
    ssd1306_WriteString(labels[label_idx], Font_11x18, White);

    ssd1306_UpdateScreen();
}
