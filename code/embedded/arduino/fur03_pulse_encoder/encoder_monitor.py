#!/usr/bin/env python3
import serial
from textual.app import App, ComposeResult
from textual.widgets import Header, Footer, Static
from textual.reactive import reactive
from textual.containers import Container

# ─── Configuración serial ───────────────────────────────────────────
PORT = "/dev/ttyACM0"
BAUDRATE = 115200
TIMEOUT = 0.1

# ─── Conversión de cuentas a grados ─────────────────────────────────
PULSES_PER_REV = 600
PULSES_TO_DEGREES = 360 / PULSES_PER_REV   # 0.6 °/cuenta

# ─── Rango visible (basado en tu captura real de ±134 cuentas) ──────
MIN_ANGLE = -90.0
MAX_ANGLE = 90.0

# Invierte el sentido si el ángulo va al lado contrario
SIGN = 1

# Carácter de los puntos de la gráfica
PLOT_CHAR = "+"


class LinePlot(Static):
    """Gráfica de línea con escala fija, guías etiquetadas y cursor."""

    data = reactive([])
    current = reactive(0.0)
    max_points = 500

    MIN_ANGLE = MIN_ANGLE
    MAX_ANGLE = MAX_ANGLE

    def render(self) -> str:
        height = self.size.height
        width = self.size.width

        if height <= 0 or width <= 0:
            return ""

        rango = self.MAX_ANGLE - self.MIN_ANGLE
        if rango == 0:
            return "\n" * height

        canvas = [[' ' for _ in range(width)] for _ in range(height)]

        def y_for(value: float) -> int:
            return height - int((value - self.MIN_ANGLE) * (height - 1) / rango) - 1

        # ── Datos ──────────────────────────────────────────────────
        if self.data:
            step_x = max(1, len(self.data) // width)
            scaled = [y_for(y) for y in self.data[-width * step_x:][::step_x]]
            for x, y in enumerate(scaled[:width]):
                y = min(max(0, y), height - 1)
                canvas[y][x] = PLOT_CHAR

        # ── Líneas guía con etiqueta ───────────────────────────────
        guias = [
            (self.MAX_ANGLE, f"+{int(self.MAX_ANGLE)}"),
            (0.0, "0"),
            (self.MIN_ANGLE, f"{int(self.MIN_ANGLE)}"),
        ]
        for val, label in guias:
            y = y_for(val)
            if 0 <= y < height:
                for x in range(width):
                    if canvas[y][x] == ' ':
                        canvas[y][x] = '─'
                # Escribir etiqueta al inicio de la línea
                for i, ch in enumerate(label):
                    if i < width:
                        canvas[y][i] = ch

        # ── Cursor vertical en la posición actual ──────────────────
        y_cur = y_for(self.current)
        if 0 <= y_cur < height:
            for yy in range(height):
                if yy != y_cur and canvas[yy][0] == ' ':
                    canvas[yy][0] = '│'
            canvas[y_cur][0] = '▶'

        return "\n".join(''.join(row) for row in canvas)

    def add_data(self, value: float) -> None:
        new_data = self.data + [value]
        if len(new_data) > self.max_points:
            new_data = new_data[-self.max_points:]
        self.data = new_data
        self.current = value


class EncoderMonitor(App):
    """Monitor de encoder en tiempo real con Textual."""

    BINDINGS = [("q", "quit", "Salir")]

    # ⬇️ AQUÍ ESTÁ LA MAGIA: Damos altura fija a los widgets ⬇️
    CSS = """
    #status {
        height: 1;
        background: $surface;
        color: $text;
    }
    #plot {
        height: 1fr;  /* 1fr significa "ocupa todo el espacio sobrante" */
        border: solid green; /* Opcional: borde para ver los límites */
    }
    #info {
        height: 3;
        background: $surface;
        color: $text;
    }
    """

    def compose(self) -> ComposeResult:
        yield Header()
        yield Container(
            Static(id="status"),
            LinePlot(id="plot"),
            Static(id="info"),
        )
        yield Footer()

    def on_mount(self) -> None:
        self.title = "Monitor de Encoder FUR03"
        self.sub_title = f"{PORT} @ {BAUDRATE} baudios"
        self.ser = None
        self.last_ms = None
        self.last_degrees = None
        self.offset = None
        self._open_serial()
        self.set_interval(0.05, self.read_serial)

    # ── Serial ─────────────────────────────────────────────────────
    def _open_serial(self) -> None:
        try:
            self.ser = serial.Serial(PORT, BAUDRATE, timeout=TIMEOUT)
            self.update_status("[green]Puerto abierto[/]")
        except serial.SerialException as e:
            self.ser = None
            self.update_status(f"[red]Error al abrir puerto: {e}[/]")

    def read_serial(self) -> None:
        if self.ser is None:
            self._open_serial()
            return

        try:
            while self.ser.in_waiting:
                line = self.ser.readline().decode(errors='ignore').strip()
                if not line:
                    continue

                if line.startswith("D:"):
                    event = line[2:].strip()
                    self.update_status(f"[dim]Evento: {event}[/]")
                    if event == "rst":
                        self.offset = None
                    continue

                if "," not in line:
                    continue

                parts = line.split(",")
                if len(parts) != 2:
                    continue

                try:
                    ms = float(parts[0])
                    counts = float(parts[1])
                except ValueError:
                    continue

                degrees_raw = SIGN * counts * PULSES_TO_DEGREES

                if self.offset is None:
                    self.offset = degrees_raw

                degrees = degrees_raw - self.offset

                speed = 0.0
                if self.last_ms is not None and self.last_degrees is not None:
                    dt = (ms - self.last_ms) / 1000.0
                    if dt > 0:
                        speed = (degrees - self.last_degrees) / dt

                self.last_ms = ms
                self.last_degrees = degrees

                self.update_info(degrees, abs(speed))
                self.query_one(LinePlot).add_data(degrees)

        except serial.SerialException as e:
            self.ser = None
            self.update_status(f"[red]Error serial: {e}[/]")

    # ── UI ─────────────────────────────────────────────────────────
    def update_status(self, message: str) -> None:
        self.query_one("#status", Static).update(message)

    def update_info(self, degrees: float, speed: float) -> None:
        offset_txt = f"{self.offset:+.1f}°" if self.offset is not None else "—"
        self.query_one("#info", Static).update(
            f"[b]Ángulo:[/] {degrees:+.2f}°\n"
            f"[b]Velocidad:[/] {speed:.1f}°/s\n"
            f"[dim]Offset reset: {offset_txt}  "
            f"Rango: {MIN_ANGLE}° … {MAX_ANGLE}°[/]"
        )


if __name__ == "__main__":
    EncoderMonitor().run()