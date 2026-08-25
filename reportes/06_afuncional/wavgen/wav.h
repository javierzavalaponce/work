#ifndef WAV_H
#define WAV_H

#include <stdint.h>
#include <stdio.h>

// Standard 44-byte RIFF WAV header structure
typedef struct {
    char     riff_id[4];      // "RIFF"
    uint32_t riff_size;    // File size minus 8 bytes
    char     wave_id[4];      // "WAVE"
    char     fmt_id[4];       // "fmt "
    uint32_t fmt_size;     // Size of fmt chunk (16 for PCM)
    uint16_t audio_format;  // 1 for uncompressed PCM
    uint16_t num_channels;  // 1 = Mono, 2 = Stereo
    uint32_t sample_rate;   // e.g., 44100
    uint32_t byte_rate;     // sample_rate * num_channels * (bits_per_sample/8)
    uint16_t block_align;   // num_channels * (bits_per_sample/8)
    uint16_t bits_per_sample;// 16 bits
    char     data_id[4];      // "data"
    uint32_t data_size;     // Total bytes of raw audio data
} WavHeader;

// Opens a file and writes the initial WAV header placeholder
FILE* wav_open_write(const char* filename, uint32_t sample_rate, uint16_t num_channels);

// Writes a batch of 16-bit signed PCM samples to the file
size_t wav_write_samples(FILE* file, const int16_t* samples, size_t num_samples);

// Computes final data sizes, overwrites the header, and closes the file
void wav_close(FILE* file);

#endif // WAV_H



