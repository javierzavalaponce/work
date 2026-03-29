#include <iostream>
#include <vector>
#include <cmath>
#include <sndfile.h>
#include <portaudio.h>

struct AudioFile {
    std::vector<float> data; // SIEMPRE mono
    sf_count_t frames;
};

// ---- cargar wav (y convertir a mono) ----
AudioFile loadWav(const char* path) {
    SF_INFO info;
    SNDFILE* file = sf_open(path, SFM_READ, &info);

    if (!file) {
        std::cerr << "Error opening file: " << path << std::endl;
        exit(1);
    }

    std::cout << "Loaded: " << path
              << " | SR: " << info.samplerate
              << " | Channels: " << info.channels << std::endl;

    std::vector<float> buffer(info.frames * info.channels);
    sf_read_float(file, buffer.data(), buffer.size());
    sf_close(file);

    // ---- convertir a mono ----
    std::vector<float> mono(info.frames);

    for (sf_count_t i = 0; i < info.frames; i++) {
        float sum = 0.0f;
        for (int ch = 0; ch < info.channels; ch++) {
            sum += buffer[i * info.channels + ch];
        }
        mono[i] = sum / info.channels;
    }

    return {mono, info.frames};
}

// ---- global state ----
AudioFile wavs[4];
float gains[4] = {0.3f, 0.6f, 0.4f, 0.7f}; // volumen por pista - dry

size_t pos = 0;

// ---- saturación suave (mejor que clip duro) ----
inline float softclip(float x) {
    return std::tanh(x);
}

// ---- audio callback ----
static int audioCallback(const void* input, 
                         void* output,
                         unsigned long framesPerBuffer,
                         const PaStreamCallbackTimeInfo* timeInfo,
                         PaStreamCallbackFlags statusFlags,
                         void* userData) {

    float* out = (float*)output;

    for (unsigned int i = 0; i < framesPerBuffer; i++) {

        float mix = 0.0f;

        for (int j = 0; j < 4; j++) {
            if (wavs[j].frames > 0) {
                size_t p = pos % wavs[j].frames; // LOOP
                mix += wavs[j].data[p] * gains[j];
            }
        }

        // evitar clipping feo
        out[i] = softclip(mix * 0.5f);

        pos++;
    }

    return paContinue;
}

// ---- main ----
int main() {

    // ---- cargar archivos ----
    wavs[0] = loadWav("kick.wav");
    wavs[1] = loadWav("kick2.wav");
    wavs[2] = loadWav("hh.wav");
    wavs[3] = loadWav("snare.wav");

    // ---- init PortAudio ----
    Pa_Initialize();

    PaStream* stream;

    Pa_OpenDefaultStream(&stream,
                         0,          // input channels
                         1,          // output mono
                         paFloat32,
                         44100,
                         256,
                         audioCallback,
                         NULL);

    Pa_StartStream(stream);

    std::cout << "Playing... Press Enter to stop\n";
    std::cin.get();

    Pa_StopStream(stream);
    Pa_CloseStream(stream);
    Pa_Terminate();

    return 0;
}