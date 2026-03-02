#include "ai_block.h"
#include "app_globals.h"
#include "temp_classifier.h"
#include "temp_classifier_data.h"
#include <stdio.h>

static ai_handle temp_classifier = AI_HANDLE_NULL;
static ai_network_report report;

void AI_Init_Block(void)
{
    ai_error err;
    const ai_handle acts[] = { activations };

    err = ai_temp_classifier_create_and_init(&temp_classifier, acts, NULL);
    if (err.type != AI_ERROR_NONE)
    {
        printf("ai init_and_create error\n");
        return;
    }

    ai_temp_classifier_get_report(temp_classifier, &report);

    ai_input  = &report.inputs[0];
    ai_output = &report.outputs[0];

    ai_input->data  = AI_HANDLE_PTR(in_data);
    ai_output->data = AI_HANDLE_PTR(out_data);

    printf("Model name      : %s\n", report.model_name);
    printf("Model signature : %s\n", report.model_signature);
}

int8_t AI_Run_Block(void)
{
    float temp_norm = my_temperature / 50.0f;
    ((ai_float *)in_data)[0] = temp_norm;

    ai_i32 nbatch = ai_temp_classifier_run(
        temp_classifier,
        ai_input,
        ai_output
    );

    if (nbatch == 1)
    {
        float *pred = (float *)out_data;
        char *labels[] = {"Cold", "Warm", "Hot"};

        int idx = 0;
        float max = pred[0];
        for (int i = 1; i < 3; i++)
        {
            if (pred[i] > max)
            {
                max = pred[i];
                idx = i;
            }
        }

        printf("DHT11: %.1f°C -> %s (%.2f)\r\n\r\n",
               my_temperature, labels[idx], max);

        return idx;
    }

    return -1;
}


int label_temperature_norm(float temp)
{
    temp = temp * 50.0;
    if (temp < 20) return 0;
    else if (temp <= 30) return 1;
    else return 2;
}
