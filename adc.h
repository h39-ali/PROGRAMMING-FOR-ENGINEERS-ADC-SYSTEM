//
// Created by hamz0 on 02/07/2026.
//

#ifndef ADC_H
#define ADC_H
#include <stdint.h>

typedef struct {
    float timestamp;
    uint8_t channel_id;
    uint16_t raw_value;
    float voltage;
    uint16_t temperature;
    uint8_t status_flags;
    uint32_t sequence_number;
} ADCsample;

#endif // ADC_H
