//
// Created by hamz0 on 02/07/2026.
//

#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <stdint.h>
#include "adc.h"

typedef struct {
    uint32_t magic;
    uint16_t version;
    uint16_t channel_count;
    uint32_t record_count;
    uint32_t sample_rate_hz;
    uint8_t reserved[8];
} FileHeader;

typedef struct {
    float timestamp;
    uint8_t channel_id;
    uint16_t raw_value;
    int16_t temperature;
    uint8_t status_flags;
    uint32_t sequence_number;
    uint8_t reserved[2];
} RawRecord;

#define FILE_MAGIC 0xADC1BEEFu

int read_header(FILE *file, FileHeader *header);
int read_data(FILE *file, RawRecord *records, uint32_t count);
void voltage_conversion(const RawRecord *raw, ADCsample *sample);

void write_results(const char *filename, ChannelStats channel_stats[4], FaultStats fault_stats[4], IntegrityCheck integrity_stats);

#endif //IO_H
