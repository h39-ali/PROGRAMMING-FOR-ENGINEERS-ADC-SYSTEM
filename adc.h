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

typedef struct {
    double max_voltage;
    double min_voltage;
    double mean_voltage;
    double std_dev_voltage;
    double sample_count;
} ChannelStats;

 typedef struct {
     int overvoltage_count;
     int undervoltage_count;
     int sensor_fault_count;
     int total_fault_count;
 } FaultStats;

 void detects_faults(const ADCsample *samples, uint32_t count, uint8_t channel, FaultStats *out);
#endif // ADC_H
