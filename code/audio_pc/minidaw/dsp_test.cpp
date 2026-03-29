#include <iostream>
#include <thread>
#include <atomic>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

std::atomic<float> volume(0.2f);

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
                std::cout << "Nuevo volumen: " << val << std::endl;
            }
        }
    }
}

int main() {
    std::thread t(udp_listener);
    t.join();
}

