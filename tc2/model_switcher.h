/*
 * model_switcher.h
 *
 *  Created on: Jan 28, 2026
 *      Author: desd
 */

#ifndef INC_MODEL_SWITCHER_H_
#define INC_MODEL_SWITCHER_H_

#include <stdint.h>
#include "main.h"

#define MODEL_1_ADDRESS 0x08000000u
#define MODEL_2_ADDRESS 0x08020000u

typedef enum {
	SWITCH_OK,
	SWITCH_ERR
} Model_Switcher_StatusTypedef;

void start_switch_indication();
void model_init_indication();
Model_Switcher_StatusTypedef switch_model();

#endif /* INC_MODEL_SWITCHER_H_ */
