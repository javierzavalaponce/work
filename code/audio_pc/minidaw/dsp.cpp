#include <iostream>
#include <cmath>
#include <thread>
#include <atomic>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

std::atomic<float> volume(0.2f);

// ===== UDP THREAD =====
void udp_listener() {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9000);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(sock, (struct sockaddr*)&addr, sizeof(addr));

    char buffer[1024];

    while (true) {
        int len = recv(sock, buffer, sizeof(buffer) - 1, 0);
        if (len > 0) {
            buffer[len] = '\0';

            float val;
            if (sscanf(buffer, "/volume %f", &val) == 1) {
                volume = val;
                std::cout << "Volume: " << val << std::endl;
            }
        }
    }
}

// ===== AUDIO THREAD (simple) =====
void audio_loop() {
    const int sample_rate = 44100;
    float phase = 0.0f;
    float freq = 440.0f;

    while (true) {
        float sample = sin(phase) * volume;

        // salida cruda (para probar, puedes redirigir a ALSA luego)
        write(1, &sample, sizeof(float));

        phase += 2.0f * M_PI * freq / sample_rate;
        if (phase > 2.0f * M_PI) phase -= 2.0f * M_PI;
    }
}

int main() {
    std::thread t1(udp_listener);
    std::thread t2(audio_loop);

    t1.join();
    t2.join();
}

