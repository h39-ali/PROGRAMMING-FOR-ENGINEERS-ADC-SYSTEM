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
    int16_t temperature;
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
void calc_channel_stats(const ADCsample *samples, uint32_t count, uint8_t channel, ChannelStats *out);
 typedef struct {
     int overvoltage_count;
     int undervoltage_count;
     int sensor_fault_count;
     int total_fault_count;
 } FaultStats;
 void detect_faults(const ADCsample *samples, uint32_t count, uint8_t channel, FaultStats *out);

 typedef struct{
     int gap_count;
     int out_of_order_count;
 } IntegrityCheck;
 void check_integrity(const ADCsample *samples, uint32_t count, IntegrityCheck *out);


#endif // ADC_H
