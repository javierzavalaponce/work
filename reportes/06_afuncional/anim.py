from manim import *
import numpy as np


class Graficas(Scene):

    def construct(self):

        # --------------------------------------------------
        # Cortinilla inicial
        # --------------------------------------------------

        titulo = Text(
            "ESIME CULHUACAN",
            font_size=56
        )

        self.play(
            FadeIn(titulo, shift=UP),
            run_time=1.5
        )

        self.wait(2)

        self.play(
            FadeOut(titulo, shift=DOWN),
            run_time=1.5
        )


        # --------------------------------------------------
        # Ejes
        # --------------------------------------------------

        axes = Axes(
            x_range=[-2 * PI, 2 * PI, PI],
            y_range=[-2, 2, 1],
            x_length=12,
            y_length=6,
            axis_config={"include_numbers": False},
        )

        self.play(Create(axes))

        # --------------------------------------------------
        # 1. cos(t) en naranja
        # --------------------------------------------------

        coseno = axes.plot(
            lambda t: np.cos(t),
            x_range=[-2 * PI, 2 * PI],
            color=ORANGE,
        )

        etiqueta_cos = MathTex(
            r"\cos(t)",
            color=ORANGE
        ).to_corner(UR)

        self.play(Create(coseno))
        self.play(Write(etiqueta_cos))
        self.wait(3)

        # --------------------------------------------------
        # 2. sin(t) en azul
        # --------------------------------------------------

        seno = axes.plot(
            lambda t: np.sin(t),
            x_range=[-2 * PI, 2 * PI],
            color=BLUE,
        )

        etiqueta_sen = MathTex(
            r"\sin(t)",
            color=BLUE
        ).to_corner(UL)

        self.play(Create(seno))
        self.play(Write(etiqueta_sen))
        self.wait(3)

        # --------------------------------------------------
        # 3. h(t) = sin(t) + alpha (cos(t) - sin(t))
        # --------------------------------------------------

        alpha = ValueTracker(0)

        h = always_redraw(
            lambda: axes.plot(
                lambda t: (
                    np.sin(t)
                    + alpha.get_value() * (
                        np.cos(t) - np.sin(t)
                    )
                ),
                x_range=[-2 * PI, 2 * PI],
                color=GREEN,
            )
        )

        self.add(h)

        # --------------------------------------------------
        # Expresión de h(t), centrada arriba
        # --------------------------------------------------

        etiqueta_h = MathTex(
            r"h(t)=\sin(t)+\alpha\left(\cos(t)-\sin(t)\right)",
            color=GREEN
        ).to_edge(UP)

        self.play(Write(etiqueta_h))

        # --------------------------------------------------
        # Barra de alpha debajo de los ejes
        # --------------------------------------------------

        barra = Line(
            axes.c2p(-2 * PI, -2.5),
            axes.c2p(2 * PI, -2.5),
        )

        punto_alpha = always_redraw(
            lambda: Dot(
                barra.point_from_proportion(alpha.get_value())
            )
        )

        etiqueta_alpha = always_redraw(
            lambda: MathTex(
                rf"\alpha = {alpha.get_value():.2f}"
            ).next_to(punto_alpha, UP)
        )

        self.add(
            barra,
            punto_alpha,
            etiqueta_alpha
        )

        # --------------------------------------------------
        # Animación de alpha: 0 -> 1
        # --------------------------------------------------

        self.play(
            alpha.animate.set_value(1),
            run_time=5,
            rate_func=linear,
        )

        self.wait(3)


