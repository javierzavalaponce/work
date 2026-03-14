#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define CHANNELS 2
#define SAMPLE_RATE 44100
#define DELAY_MS 100
#define FEEDBACK 0.5  // factor de atenuación del eco (0.0 a 1.0)
#define WAV_HEADER_SIZE 44

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Uso: %s input.wav output.wav\n", argv[0]);
        return 1;
    }

    FILE *fin = fopen(argv[1], "rb");
    FILE *fout = fopen(argv[2], "wb");
    if (!fin || !fout) {
        perror("Error al abrir archivos");
        return 1;
    }

    // Copiar header al archivo de salida
    uint8_t header[WAV_HEADER_SIZE];
    fread(header, 1, WAV_HEADER_SIZE, fin);
    fwrite(header, 1, WAV_HEADER_SIZE, fout);

    size_t delay_samples = (SAMPLE_RATE * DELAY_MS) / 1000;
    int16_t *buffer[CHANNELS];
    for (int c = 0; c < CHANNELS; c++) {
        buffer[c] = (int16_t*)calloc(delay_samples, sizeof(int16_t));
        if (!buffer[c]) {
            fprintf(stderr, "No se pudo reservar memoria\n");
            return 1;
        }
    }

    int16_t sample[CHANNELS];
    size_t pos = 0;

    while (fread(sample, sizeof(int16_t), CHANNELS, fin) == CHANNELS) {
        int16_t out[CHANNELS];
        for (int c = 0; c < CHANNELS; c++) {
            // Mezclar la muestra actual con la del buffer atenuada
            out[c] = sample[c] + (int16_t)(buffer[c][pos] * FEEDBACK);

            // Guardar la nueva muestra en el buffer para futuros ecos
            buffer[c][pos] = out[c];
        }

        fwrite(out, sizeof(int16_t), CHANNELS, fout);
        pos = (pos + 1) % delay_samples;
    }

    for (int c = 0; c < CHANNELS; c++) free(buffer[c]);
    fclose(fin);
    fclose(fout);

    return 0;
}

