#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>   // <-- para strerror()
#include <errno.h>

#define SAMPLE_RATE 44100
#define CHANNELS 2

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Uso: %s <delay_ms> <feedback>\n", argv[0]);
        return 1;
    }

    size_t delay_ms = atoi(argv[1]);
    double feedback = atof(argv[2]);

    if (feedback < 0 || feedback > 1) {
        fprintf(stderr, "Feedback debe estar entre 0 y 1\n");
        return 1;
    }

    size_t delay_samples = (SAMPLE_RATE * delay_ms) / 1000;
    int16_t *buffer[CHANNELS];
    size_t pos = 0;

    for (int c = 0; c < CHANNELS; c++) {
        buffer[c] = (int16_t*)calloc(delay_samples, sizeof(int16_t));
        if (!buffer[c]) {
            fprintf(stderr, "No se pudo reservar memoria: %s\n", strerror(errno));
            return 1;
        }
    }

    int16_t sample[CHANNELS];

    while (fread(sample, sizeof(int16_t), CHANNELS, stdin) == CHANNELS) {
        int16_t out[CHANNELS];

        for (int c = 0; c < CHANNELS; c++) {
            out[c] = buffer[c][pos];
            buffer[c][pos] = sample[c] + buffer[c][pos] * feedback;
        }

        fwrite(out, sizeof(int16_t), CHANNELS, stdout);
        pos = (pos + 1) % delay_samples;
    }

    for (int c = 0; c < CHANNELS; c++) free(buffer[c]);
    return 0;
}

