#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sndfile.h>   // Librería para WAV

#define SAMPLE_RATE 44100
#define CHANNELS 2

int main(int argc, char *argv[]) {
    if (argc < 5) {
        fprintf(stderr, "Uso: %s <input.wav> <output.wav> <delay_ms> <feedback>\n", argv[0]);
        return 1;
    }

    const char *infile = argv[1];
    const char *outfile = argv[2];
    size_t delay_ms = atoi(argv[3]);
    double feedback = atof(argv[4]);

    if (feedback < 0 || feedback > 1) {
        fprintf(stderr, "Feedback debe estar entre 0 y 1\n");
        return 1;
    }

    SF_INFO sfinfo;
    SNDFILE *in = sf_open(infile, SFM_READ, &sfinfo);
    if (!in) {
        fprintf(stderr, "Error abriendo %s: %s\n", infile, sf_strerror(NULL));
        return 1;
    }

    if (sfinfo.channels != CHANNELS) {
        fprintf(stderr, "El archivo debe ser estéreo (2 canales)\n");
        sf_close(in);
        return 1;
    }

    size_t delay_samples = (sfinfo.samplerate * delay_ms) / 1000;
    int16_t *buffer[CHANNELS];
    size_t pos = 0;

    for (int c = 0; c < CHANNELS; c++) {
        buffer[c] = (int16_t*)calloc(delay_samples, sizeof(int16_t));
        if (!buffer[c]) {
            fprintf(stderr, "No se pudo reservar memoria: %s\n", strerror(errno));
            sf_close(in);
            return 1;
        }
    }

    SNDFILE *out = sf_open(outfile, SFM_WRITE, &sfinfo);
    if (!out) {
        fprintf(stderr, "Error creando %s: %s\n", outfile, sf_strerror(NULL));
        sf_close(in);
        return 1;
    }

    int16_t sample[CHANNELS];
    while (sf_readf_short(in, sample, 1) == 1) {
        int16_t out_sample[CHANNELS];

        for (int c = 0; c < CHANNELS; c++) {
            out_sample[c] = buffer[c][pos];
            buffer[c][pos] = sample[c] + buffer[c][pos] * feedback;
        }

        sf_writef_short(out, out_sample, 1);
        pos = (pos + 1) % delay_samples;
    }

    for (int c = 0; c < CHANNELS; c++) free(buffer[c]);
    sf_close(in);
    sf_close(out);

    printf("Procesamiento completado: %s -> %s\n", infile, outfile);
    return 0;
}

