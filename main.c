#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "adc.h"

int main(int argc, char *argv[]) {
    if (argc !=2) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }
    FILE *file = fopen(argv[1], "rb");
    if (file == NULL) {
        fprintf(stderr, "Error: Unable to open file %s\n", argv[1]);
        return 1;
    }
    FileHeader header;
    if (!read_header(file, &header)) {
        fclose(file);
        return 1;
    }
    RawRecord *rawRecord = malloc(header.record_count * sizeof(RawRecord));
    if (rawRecord == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory");
        fclose(file);
        return 1;
    }
    if (!read_data(file, rawRecord, header.record_count)) {
        free(rawRecord);
        fclose(file);
        return 1;
    }
    printf("File read successfully");

    ADCsample *samples = malloc(header.record_count * sizeof(ADCsample));
    if (samples == NULL) {
        fprintf(stderr, "Error: Unable to allocate memory for samples\n");
        free(rawRecord);
        fclose(file);
        return 1;
    }

    for (uint32_t i = 0; i <header.record_count; i ++) {
        voltage_conversion(&rawRecord[i], &samples[i]);
    }
    printf("Records read and converted successfully\n");
ChannelStats channel_stats[4];
for (uint8_t ch = 0; ch < 4; ch++) {
    calc_channel_stats(samples, header.record_count, ch, &channel_stats[ch]);
}
for (int ch = 0; ch < 4; ch++) {
    printf("Channel %d: max=%.3fV min=%.3fV mean=%.3fV standard deviation=%.3fV (n=%.0f)\n", ch, channel_stats[ch].max_voltage, channel_stats[ch].min_voltage, channel_stats[ch].mean_voltage, channel_stats[ch].std_dev_voltage, channel_stats[ch].sample_count);
}
FaultStats fault_stats[4];
for (uint8_t ch = 0; ch < 4; ch++) {
detect_faults(samples, header.record_count, ch, &fault_stats[ch]);
}
    IntegrityCheck integrity_stats;
        check_integrity(samples, header.record_count, &integrity_stats);

    write_results("results.txt", channel_stats, fault_stats, integrity_stats);
free(samples);
free(rawRecord);
fclose(file);

    return 0;
}