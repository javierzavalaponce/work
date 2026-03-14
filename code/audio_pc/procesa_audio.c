#include <stdio.h>
#include <stdint.h>

int main() {
    int16_t sample; // cada sample PCM16 es 2 bytes

    // Leer todos los samples que lleguen por stdin
    while (fread(&sample, sizeof(sample), 1, stdin) == 1) {
        // Aquí puedes manipular el sample
        printf("Sample recibido: %d\n", sample);
    }
    return 0;
}

