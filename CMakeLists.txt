cmake_minimum_required(VERSION 3.21)
project(adc_sensor_processor C)

set(CMAKE_C_STANDARD 99)

add_executable(adc_sensor_processor
        main.c
        adc.h
        io.h
        stats.h
        adc.c
        io.c
        stats.c
        )
target_link_libraries(adc_sensor_processor m)