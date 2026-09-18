from manim import *
import numpy as np


class ProductoInterno(Scene):

    def construct(self):

        # -------------------------
        # Ejes coordenados
        # -------------------------
        axes = Axes(
            x_range=[-1, 5, 1],
            y_range=[-1, 5, 1],
            x_length=6,
            y_length=6,
            axis_config={"include_numbers": True},
        )

        self.add(axes)

        # -------------------------
        # Vectores
        # -------------------------
        x = axes.c2p(1, 2)
        y = axes.c2p(3, 4)
        origen = axes.c2p(0, 0)

        vector_x = Arrow(
            origen,
            x,
            buff=0,
            stroke_width=6,
        )

        vector_y = Arrow(
            origen,
            y,
            buff=0,
            stroke_width=6,
        )

        # Etiquetas
        label_x = MathTex(r"\mathbf{x}=(1,2)")
        label_y = MathTex(r"\mathbf{y}=(3,4)")

        label_x.next_to(vector_x.get_end(), LEFT)
        label_y.next_to(vector_y.get_end(), RIGHT)

        # -------------------------
        # Ángulo entre los vectores
        # -------------------------

        theta = Angle(
            vector_x,
            vector_y,
            radius=0.7,
        )

        theta_label = MathTex(r"\theta")
        theta_label.move_to(
            theta.point_from_proportion(0.5)
        )

        # -------------------------
        # Mostrar todo
        # -------------------------

        self.play(Create(vector_x))
        self.play(Write(label_x))

        self.play(Create(vector_y))
        self.play(Write(label_y))

        self.play(Create(theta))
        self.play(Write(theta_label))

        self.wait(3)


        