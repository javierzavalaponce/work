#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define BUFFER_FRAMES 1024 // cantidad de frames por buffer
#define CHANNELS 2         // estéreo

// Función de ejemplo: bypass (no hace nada)
static inline int16_t bypass(int16_t sample) {
    return sample;
}

// Función de ejemplo: inversión de fase
static inline int16_t proc(int16_t sample) {
    return -sample;
}

int main() {
    int16_t buffer[BUFFER_FRAMES * CHANNELS]; // buffer para L+R
    size_t read_frames;

    while ((read_frames = fread(buffer, sizeof(int16_t) * CHANNELS, BUFFER_FRAMES, stdin)) > 0) {
        for (size_t i = 0; i < read_frames * CHANNELS; i++) {
            // Aplica tu función de procesamiento a cada sample
            buffer[i] = proc(buffer[i]); // o bypass(buffer[i])
        }

        // Escribir el buffer procesado a stdout
        fwrite(buffer, sizeof(int16_t) * CHANNELS, read_frames, stdout);
        fflush(stdout); // asegura que el audio salga rápido
    }

    return 0;
}

