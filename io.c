//
// Created by hamz0 on 02/07/2026.

#include "io.h"
#include <stdlib.h>

int read_header(FILE *file, FileHeader *header) {
    size_t success = 1;
    success &= fread(&header->magic, sizeof(header->magic), 1, file);
    success &= fread(&header->version, sizeof(header->version), 1, file);
    success &= fread(&header->channel_count, sizeof(header->channel_count), 1, file);
    success &= fread(&header->record_count, sizeof(header->record_count), 1, file);
    success &= fread(&header->sample_rate_hz, sizeof(header->sample_rate_hz), 1, file);
    success &= fread(&header->reserved, sizeof(header->reserved), 1, file);
    if (!success) {
        fprintf(stderr, "Error: Unable to read file header\n");
        return 0;
    }
    if (header->magic != FILE_MAGIC) {
        fprintf(stderr, "Error: Invalid magic number\n", header->magic, FILE_MAGIC);
        return 0;
    }
    if (header->version != 1) {
        fprintf(stderr, "Warning: Unexpected file version\n", header->version);
    }
    if (header->channel_count != 4) {
        fprintf(stderr, "Warning: Unexpected channel count\n", header->channel_count);
    }
    return 1;
}
int read_data(FILE *file, RawRecord * records, uint32_t count) {
    for (uint32_t i = 0; i < count; i++) {
        size_t success = 1;
        success &= fread(&records[i].timestamp, sizeof(records[i].timestamp), 1, file);
        success &= fread(&records[i].channel_id, sizeof(records[i].channel_id), 1, file);
        success &= fread(&records[i].raw_value, sizeof(records[i].raw_value), 1, file);
        success &= fread(&records[i].temperature, sizeof(records[i].temperature), 1, file);
        success &= fread(&records[i].status_flags, sizeof(records[i].status_flags), 1, file);
        success &= fread(&records[i].sequence_number, sizeof(records[i].sequence_number), 1, file);
        success &= fread(&records[i].reserved, sizeof(records[i].reserved), 1, file);
if (!success) {
    fprintf(stderr, "Error: Unable to read record\n");
    return 0;
}
    }
return 1;
    void voltage_conversion(const RawRecord *raw, ADCsample *sample) {
        const float VREF = 3.3f;

        sample->timestamp = raw->timestamp;
        sample->channel_id = raw->channel_id;
        sample->raw_value = raw->raw_value;
        sample->voltage = (raw->raw_value / 4095.0f) * VREF;
        sample->temperature = raw->temperature;
        sample->status_flags = raw->status_flags;
        sample->sequence_number = raw->sequence_number;
    }
}
void write_results(const char *filename, ChannelStats channel_stats[4], FaultStats fault_stats[4],IntegrityCheck integrity_stats[4]) {
    FILE *out = fopen(filename, "w");
    if (out == NULL) {
        fprintf(stderr, "Error: Unable to open %s to write results\n", filename);
        return;
    }
fprintf(out, "ADC RESULTS\n");
    for (int ch = 0; ch < 4; ch++) {
        fprintf(out, "Channel %d\n", ch);
        fprintf(out, "Samples: %.3f\n", channel_stats[ch].sample_count);
        fprintf(out, "Max voltage: %.3f\n", channel_stats[ch].max_voltage);
        fprintf(out, "Min voltage: %.3f\n", channel_stats[ch].min_voltage);
        fprintf(out, "Mean voltage: %.3f\n", channel_stats[ch].mean_voltage);
        fprintf(out, "Standard deviation: %.3f\n", channel_stats[ch].std_dev_voltage);
        fprintf(out, "Overvoltage: %d\n", fault_stats[ch].overvoltage_count);
        fprintf(out, "Undervoltage: %d\n", fault_stats[ch].undervoltage_count);
        fprintf(out, "Sensor faults: %d\n", fault_stats[ch].sensor_fault_count);
        fprintf(out, "Total faults: %d\n", fault_stats[ch].total_fault_count);
        fprintf(out, "Sequence gaps: %d\n", integrity_stats[ch].gap_count);
        fprintf(out, "Total faults: %d\n", integrity_stats[ch].out_of_order_count);
    }
fclose(out);
    printf("Results successfully written to %s\n", filename);
}
