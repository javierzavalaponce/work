#include <iostream>
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

int main() {
    enableRawMode();

    std::cout << "Modo RAW activo. Presiona 'q' para salir.\n";

    while (true) {
        char c;
        ssize_t n = read(STDIN_FILENO, &c, 1);

        if (n > 0) {
            std::cout << "Tecla: " << c << " (ASCII: " << (int)c << ")\n";

            if (c == 'q') break;
        }
    }

    disableRawMode();
    std::cout << "Modo RAW desactivado.\n";

    return 0;
}


