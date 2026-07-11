//
// Created by hamz0 on 02/07/2026.
//

#include "stats.h"
#include <math.h>

double calc_mean(const double *values, int count) {
    double sum = 0.0;
    for (int i = 0; i < count; i++) {
        sum += values[i];
    }
    return sum / count;
}
double calc_min(const double *values, int count) {
    double min = values[0];
    for (int i = 1; i < count; i++) {
        if (values[i] < min) {
            min = values[i];
        }
    }
    return min;
}
    double calc_max(const double *values, int count) {
        double max = values[0];
        for (int i = 1; i < count; i++) {
            if (values[i] > max) {
                max = values[i];
            }
        }
        return max;
    }
        double calc_std_dev(const double *values, int count, double mean) {
            double sum_squared_diff = 0.0;
            for (int i = 0; i < count; i++) {
                double diff = values[i] - mean;
                sum_squared_diff += diff * diff;
            }
            return sqrt(sum_squared_diff / count);
        }