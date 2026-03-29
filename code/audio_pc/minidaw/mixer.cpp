#include <iostream>
#include <vector>
#include <sndfile.h>
#include <portaudio.h>

struct AudioFile {
    std::vector<float> data;
    sf_count_t frames;
};

AudioFile loadWav(const char* path) {
    SF_INFO info;
    SNDFILE* file = sf_open(path, SFM_READ, &info);

    if (!file) {
        std::cerr << "Error opening file: " << path << std::endl;
        exit(1);
    }

    std::vector<float> buffer(info.frames);
    sf_read_float(file, buffer.data(), info.frames);
    sf_close(file);

    return {buffer, info.frames};
}

// ---- global state ----
AudioFile wavs[4];
size_t pos = 0;

// ---- audio callback ----
static int audioCallback(const void* input,
                         void* output,
                         unsigned long framesPerBuffer,
                         const PaStreamCallbackTimeInfo* timeInfo,
                         PaStreamCallbackFlags statusFlags,
                         void* userData) {

    float* out = (float*)output;

    for (unsigned int i = 0; i < framesPerBuffer; i++) {
        float sample = 0.0f;

        for (int j = 0; j < 4; j++) {
            if (pos < wavs[j].frames) {
                sample += wavs[j].data[pos];
            }
        }

        out[i] = sample * 0.25f; // evitar clipping
        pos++;
    }

    return paContinue;
}

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
                         1,          // output channels (mono)
                         paFloat32,  // formato
                         44100,      // sample rate
                         256,        // buffer size
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


