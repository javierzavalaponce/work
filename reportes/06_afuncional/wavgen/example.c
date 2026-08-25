#include "wav.h"
#include <math.h>
#include <stdlib.h>

#define SAMPLE_RATE 44100
#define DURATION_SEC 3
#define FREQUENCY_HZ 180.0
#define FREQUENCYB_HZ 234.0
#define FREQUENCYC_HZ 360.0

#define AMPLITUDE 16000 // Out of maximum 32767 for signed 16-bit

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

int main(void) {
    const char* filename = "comb_lineal.wav";
    uint32_t total_samples = SAMPLE_RATE * DURATION_SEC;
    
    // Allocate space for mono track buffer
    int16_t* buffer = malloc(total_samples * sizeof(int16_t));
    if (!buffer) {
        printf("Memory allocation error.\n");
        return 1;
    }

    // Mathematically generate a smooth sine wave
    for (uint32_t i = 0; i < total_samples; i++) {
        double time = (double)i / SAMPLE_RATE;
        buffer[i] =  (int16_t)(0.63*AMPLITUDE * sin(2.0 * M_PI * FREQUENCY_HZ * time));
        buffer[i] += (int16_t)(0.72*AMPLITUDE * sin(2.0 * M_PI * FREQUENCYB_HZ * time));
        buffer[i] += (int16_t)(0.14*AMPLITUDE * sin(2.0 * M_PI * FREQUENCYC_HZ * time));
    }

    // Stream generation components via our library
    FILE* wav_file = wav_open_write(filename, SAMPLE_RATE, 1); // 1 = Mono
    if (!wav_file) {
        printf("Failed to create file: %s\n", filename);
        free(buffer);
        return 1;
    }

    // Push buffer items and clean resource links
    wav_write_samples(wav_file, buffer, total_samples);
    wav_close(wav_file);
    free(buffer);

    printf("Successfully generated '%s' (%d seconds)!\n", filename, DURATION_SEC);
    return 0;
}




