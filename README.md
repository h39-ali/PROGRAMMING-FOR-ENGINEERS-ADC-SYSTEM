#ADC Data Processor
A C99 program that reads a binary ADC sensor log file, calculates voltage statistics, pinpoints any faults in voltage, sensors or sewuence integrity. The program then prints results to 'results.txt'.

##How to Build and Run in Clion
1. Open this folder in Clion as a new project.
2. Click on the run tab -> Edit Configurations then change 'Program arguments' to the path of the binary log file.
3. Click 'Build' (Hammer Icon) then 'Run' (Green Play button).

##How to Build and Run using gcc cCrommand line
gcc -std=c99 -wall -o adc_sensor_processor main.c stats.c io.c adc.c -lm ./adc_sensor_processor data/adc_sensor_log.bin

##Output
The program will output full results for every channel to 'results.txt'.

##GitHub Repository
https://github.com/h39-ali/PROGRAMMING-FOR-ENGINEERS-ADC-SYSTEM