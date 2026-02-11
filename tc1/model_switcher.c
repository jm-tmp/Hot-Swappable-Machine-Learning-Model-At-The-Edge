/*
 * model_switcher.c
 *
 *  Created on: Jan 28, 2026
 *      Author: desd
 */

#include "main.h"
#include "model_switcher.h"

inline Model_Switcher_StatusTypedef switch_model(uint32_t app_address) {
	// start_switch_indication();

	typedef void (*resetHandlerPtr)(void);
	resetHandlerPtr reset_handler;

	uint32_t msp_val = (*(uint32_t *)app_address);
	__set_MSP(msp_val);

	/* Relocate vector table */
	SCB->VTOR = (uint32_t)app_address;

	reset_handler = (resetHandlerPtr)(*(uint32_t *)(app_address+4U));

	reset_handler();

	return SWITCH_ERR;

}

inline void start_switch_indication() {
	for(uint8_t i=0; i<15; i++) {
		HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_14);
		HAL_Delay(250);
	}
}

inline void model_init_indication() {
	for(uint8_t i=0; i<32; i++) {
		HAL_GPIO_TogglePin(GPIOD, ( GPIO_PIN_12 << (i%4) ));
		HAL_Delay(100);
	}
}
