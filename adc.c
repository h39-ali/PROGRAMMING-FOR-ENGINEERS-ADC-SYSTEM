//
// Created by hamz0 on 02/07/2026.
//

#include "adc.h"
#include "stats.h"
#include <stdlib.h>

void calc_channel_stats(const ADCsample *samples, uint32_t count, uint8_t channel, ChannelStats *out) {
int n = 0;

for (uint32_t i = 0; i < count; i++) {
    if (samples[i].channel_id == channel) {
        voltages[n] = samples[i].voltage;
        n++;
    }
}
if (n == 0) {
    out->max_voltage = 0.0;
out->min_voltage = 0.0;
out->mean_voltage = 0.0;
out->std_dev_voltage = 0.0;
out->sample_count = 0.0;
free(voltages);
return;
}
out->max_voltage = calc_max(voltages, n);
out->min_voltage = calc_min(voltages, n);
out->mean_voltage = calc_mean(voltages, n);
out->std_dev_voltage = calc_std_dev(voltages, n);
out->sample_count = n;
free(voltages);
}
