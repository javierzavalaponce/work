#include "wav.h"
#include <string.h>

FILE* wav_open_write(const char* filename, uint32_t sample_rate, uint16_t num_channels) {
    FILE* file = fopen(filename, "wb");
    if (!file) return NULL;

    WavHeader header;
    
    // Copy magic identifiers safely without trailing null terminators
    memcpy(header.riff_id, "RIFF", 4);
    memcpy(header.wave_id, "WAVE", 4);
    memcpy(header.fmt_id,  "fmt ", 4);
    memcpy(header.data_id, "data", 4);

    // Set format attributes
    header.fmt_size = 16; 
    header.audio_format = 1; // PCM linear fixed-point
    header.num_channels = num_channels;
    header.sample_rate = sample_rate;
    header.bits_per_sample = 16;
    
    // Calculate data rates
    header.block_align = num_channels * (header.bits_per_sample / 8);
    header.byte_rate = sample_rate * header.block_align;

    // Temporary values for sizes; updated during wav_close()
    header.data_size = 0;
    header.riff_size = 36; 

    // Write out the initial/empty header block
    if (fwrite(&header, sizeof(WavHeader), 1, file) != 1) {
        fclose(file);
        return NULL;
    }

    return file;
}

size_t wav_write_samples(FILE* file, const int16_t* samples, size_t num_samples) {
    if (!file || !samples) return 0;
    return fwrite(samples, sizeof(int16_t), num_samples, file);
}

void wav_close(FILE* file) {
    if (!file) return;

    // Determine the absolute total size of the written file
    long file_size = ftell(file);
    if (file_size >= (long)sizeof(WavHeader)) {
        uint32_t data_size = (uint32_t)(file_size - sizeof(WavHeader));
        uint32_t riff_size = (uint32_t)(file_size - 8);

        // Seek back to patch sizing fields
        fseek(file, 4, SEEK_SET);
        fwrite(&riff_size, sizeof(uint32_t), 1, file);

        fseek(file, 40, SEEK_SET);
        fwrite(&data_size, sizeof(uint32_t), 1, file);
    }

    fclose(file);
}


