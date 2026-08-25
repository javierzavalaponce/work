```{=latex}
\clearpage
```


## Ejercicio 2: Analisis espectral


Este es el ejercicio, construir un detector de frecuencias
tengo una señal wav de audio de tres segundos generada por un programa en C:


```c
#include "wav.h"
#include <math.h>
#include <stdlib.h>

#define SAMPLE_RATE 44100
#define DURATION_SEC 3
#define FREQUENCY_HZ 180.0
#define FREQUENCYB_HZ 234.0
#define FREQUENCYC_HZ 360.0

#define AMPLITUDE 16000 // Out of maximum 32767 for signed 16-bit

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

int main(void) {
    const char* filename = "comb_lineal.wav";
    uint32_t total_samples = SAMPLE_RATE * DURATION_SEC;
    
    // Allocate space for mono track buffer
    int16_t* buffer = malloc(total_samples * sizeof(int16_t));
    if (!buffer) {
        printf("Memory allocation error.\n");
        return 1;
    }

    // Mathematically generate a smooth sine wave
    for (uint32_t i = 0; i < total_samples; i++) {
        double time = (double)i / SAMPLE_RATE;
        buffer[i] =  (int16_t)(0.63*AMPLITUDE * sin(2.0 * M_PI * FREQUENCY_HZ * time));
        buffer[i] += (int16_t)(0.72*AMPLITUDE * sin(2.0 * M_PI * FREQUENCYB_HZ * time));
        buffer[i] += (int16_t)(0.14*AMPLITUDE * sin(2.0 * M_PI * FREQUENCYC_HZ * time));
    }

    // Stream generation components via our library
    FILE* wav_file = wav_open_write(filename, SAMPLE_RATE, 1); // 1 = Mono
    if (!wav_file) {
        printf("Failed to create file: %s\n", filename);
        free(buffer);
        return 1;
    }

    // Push buffer items and clean resource links
    wav_write_samples(wav_file, buffer, total_samples);
    wav_close(wav_file);
    free(buffer);

    printf("Successfully generated '%s' (%d seconds)!\n", filename, DURATION_SEC);
    return 0;
}


```

La frecuencia de muestreo es 44100 Hz

```{=latex}
\[
x(t)=10080sin(2 \pi 180t)+11520sin(2 \pi 234t) + 2240sin(2 \pi 360t)
\]
```

Si solamente me dan $x(t)$, ¿cómo puedo descubrir $x_1 ,x_2 y x_3$ ?

Arduino $F_s$ a 1000Hz


Entonces ya no vamos a trabajar directamente con $x(t)$, sino con:

$x[n] = x(nT_s)$

con $T_s = \frac{1}{1000} = 0.001s$

nota $180 \less 500$, $234 \less 500$, $360 \less 500$

Por tanto, las tres componentes pueden ser muestreadas.

Hasta aquí todo perfecto.

```{=latex}
\[
x[n]=10080sin(2 \pi 180 \frac{n}{1000})+11520sin(2 \pi 234 \frac{n}{1000}) + 2240sin(2 \pi 360 \frac{n}{1000})
\]
```

Vamos a construir un detector de 180 Hz.


ayuda. es un ejercicio para practicar y aprender fft y dft, por favor ayudame 
quiero procesar esto en un arduino con isr a 1Kilihert
me interesa aprender
y de ser posible vincular con lo que he estado viendo de analisis funcional

quiero saber como calcular senos en arduino de la manera mas eficiente tipo industria DSP . busco aprender al maximo ilumina mi camino


8484: neta?
Quieres extraer la componente de 180 Hz. Esto es un proyector en un espacio de Hilbert:

