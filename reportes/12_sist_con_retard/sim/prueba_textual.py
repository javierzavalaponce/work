
from textual.app import App, ComposeResult
from textual.widgets import Header, Footer, Static, Input
from tf2ss import tf2ss


class PruebaTextual(App):
    def compose(self) -> ComposeResult:
        yield Header()

        yield Static("Coeficientes del numerador:")
        yield Input(
            placeholder="Ejemplo: 1",
            id="numerador"
        )

        yield Static("Coeficientes del denominador:")
        yield Input(
            placeholder="Ejemplo: 1, -3, 2",
            id="denominador"
        )

        yield Static("", id="resultado")
        yield Footer()

    def on_input_submitted(self, event: Input.Submitted) -> None:
        numerador_texto = self.query_one("#numerador", Input).value
        denominador_texto = self.query_one("#denominador", Input).value

        resultado = self.query_one("#resultado", Static)

        try:
            numerador = [
                float(p.strip())
                for p in numerador_texto.split(",")
            ]

            denominador = [
                float(p.strip())
                for p in denominador_texto.split(",")
            ]

            A, B, C, D = tf2ss(numerador, denominador)

            resultado.update(
            f"Numerador: {numerador}\n"
            f"Denominador: {denominador}\n\n"
            f"A =\n{A}\n\n"
            f"B =\n{B}\n\n"
            f"C =\n{C}\n\n"
            f"D =\n{D}"
            )

        except ValueError:
            resultado.update(
                "Error: introduce números separados por comas."
            )


if __name__ == "__main__":
    PruebaTextual().run()




