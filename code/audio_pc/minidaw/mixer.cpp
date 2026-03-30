#include <iostream>
#include <vector>
#include <cmath>
#include <sndfile.h>
#include <portaudio.h>
#include <termios.h>
#include <unistd.h>

// guardar configuración original
struct termios orig_termios;

// restaurar terminal al salir
void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
}

// activar modo raw
void enableRawMode() {
    tcgetattr(STDIN_FILENO, &orig_termios);

    struct termios raw = orig_termios;

    // desactivar modo canónico y echo
    raw.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}





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
    float gains_dry[4]   = {0.3f, 0.0f, 0.3, 0.3f}; // volumen por pista - dry
    float gains_sends[4] = {0.0f, 0.0f, 0.0f, 0.0f}; // volumen por pista - send
    float sends_on_off[4] = {0.0f, 0.0f, 0.0f, 0.0f};
    float dries_on_off[4] = {0.0f, 0.0f, 0.0f, 0.0f};
    


    size_t pos = 0;

    // ---- saturación suave (mejor que clip duro) ----
    inline float softclip(float x) {
        return std::tanh(x);
    }



    // ---- delay state (bus global) ----
const int SAMPLE_RATE = 44100;
const float DELAY_MS = 450.0f;     // ajusta al gusto
const float FEEDBACK = 0.6f;       // 0–1

size_t delaySamples = (size_t)(SAMPLE_RATE * DELAY_MS / 1000.0f);

std::vector<float> delayBuffer(delaySamples, 0.0f);
size_t delayPos = 0;


float FX_echo_delay(float input) {

    // leer el pasado (eco)
    float delayed = delayBuffer[delayPos];

    // escribir nuevo valor en buffer (input + feedback)
    delayBuffer[delayPos] = input + delayed * FEEDBACK;

    // avanzar buffer circular
    delayPos = (delayPos + 1) % delaySamples;

    // salida SOLO el eco (100% wet)
    return delayed;
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
                    //mix += wavs[j].data[p] * gains_dry[j];
                    mix += wavs[j].data[p] * gains_dry[j] * dries_on_off[j];
                    mix += FX_echo_delay(wavs[j].data[p] * gains_sends[j] * sends_on_off[j]);
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

    enableRawMode();
    std::cout << "Modo RAW activo. Presiona 'q' para salir.\n";

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

    while (true) {
        char c;
        ssize_t n = read(STDIN_FILENO, &c, 1);

        if (n > 0) {
            std::cout << "Tecla: " << c << " (ASCII: " << (int)c << ")\n";

            if (c == 'q') break;
            if (c == '8') {sends_on_off[0] = (sends_on_off[0]>0.0)?0.0:1.0;}
            if (c == '5') {sends_on_off[2] = (sends_on_off[2]>0.0)?0.0:1.0;}
            if (c == '2') {sends_on_off[3] = (sends_on_off[3]>0.0)?0.0:1.0;}
            
            if (c == '7') {if(gains_sends[0] == 0); else gains_sends[0] -= 0.1; }
            if (c == '9') {if(gains_sends[0] == 1); else gains_sends[0] += 0.1; }
            
            if (c == '4') {if(gains_sends[2] == 0); else gains_sends[2] -= 0.1; }
            if (c == '6') {if(gains_sends[2] == 1); else gains_sends[2] += 0.1; }

            if (c == '1') {if(gains_sends[3] == 0); else gains_sends[3] -= 0.1; }
            if (c == '3') {if(gains_sends[3] == 1); else gains_sends[3] += 0.1; }

            //------------

            if (c == 'e') {dries_on_off[0] = (dries_on_off[0]>0.0)?0.0:1.0;}
            if (c == 's') {dries_on_off[2] = (dries_on_off[2]>0.0)?0.0:1.0;}
            if (c == 'x') {dries_on_off[3] = (dries_on_off[3]>0.0)?0.0:1.0;}
            
            if (c == 'w') {if(gains_dry[0] == 0); else gains_dry[0] -= 0.1; }
            if (c == 'r') {if(gains_dry[0] == 1); else gains_dry[0] += 0.1; }
            
            if (c == 'a') {if(gains_dry[2] == 0); else gains_dry[2] -= 0.1; }
            if (c == 'd') {if(gains_dry[2] == 1); else gains_dry[2] += 0.1; }

            if (c == 'z') {if(gains_dry[3] == 0); else gains_dry[3] -= 0.1; }
            if (c == 'c') {if(gains_dry[3] == 1); else gains_dry[3] += 0.1; }

        }
    }

    disableRawMode();

        Pa_StopStream(stream);
        Pa_CloseStream(stream);
        Pa_Terminate();

        return 0;
    }