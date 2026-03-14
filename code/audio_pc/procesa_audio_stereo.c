#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define SAMPLE_RATE 44100
#define CHANNELS 2
#define DELAY_MS 100

int main() {
    int16_t *buffer[CHANNELS];
    size_t delay_samples = (SAMPLE_RATE * DELAY_MS) / 1000;
    size_t pos = 0;

    // Reservar buffer circular por canal
    for (int c = 0; c < CHANNELS; c++) {
        buffer[c] = (int16_t*)calloc(delay_samples, sizeof(int16_t));
        if (!buffer[c]) {
            fprintf(stderr, "No se pudo reservar memoria\n");
            return 1;
        }
    }

    int16_t sample[CHANNELS];

    while (fread(sample, sizeof(int16_t), CHANNELS, stdin) == CHANNELS) {
        int16_t out[CHANNELS];

        // Leer del buffer de delay
        for (int c = 0; c < CHANNELS; c++) {
            out[c] = buffer[c][pos];
        }

        // Guardar muestra actual en buffer
        for (int c = 0; c < CHANNELS; c++) {
            buffer[c][pos] = sample[c];
        }

        // Escribir al stdout
        fwrite(out, sizeof(int16_t), CHANNELS, stdout);

        // Avanzar posición circular
        pos = (pos + 1) % delay_samples;
    }

    for (int c = 0; c < CHANNELS; c++) free(buffer[c]);
    return 0;
}

