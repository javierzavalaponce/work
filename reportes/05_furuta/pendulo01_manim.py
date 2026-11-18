
from manim import *
import numpy as np


class PenduloSimple(Scene):
    def construct(self):

        # --------------------------------------------------
        # CORTINILLA INICIAL
        # --------------------------------------------------

        titulo = Text(
            "ESIME CULHUACAN",
            font_size=56
        )

        self.play(FadeIn(titulo, shift=UP), run_time=1.0)
        self.wait(1)
        self.play(FadeOut(titulo, shift=DOWN), run_time=0.7)

        # --------------------------------------------------
        # FORMULACION DE LAGRANGE
        # --------------------------------------------------

        titulo_lag = Text(
            "Formulación de Lagrange (Péndulo Simple)",
            font_size=40
        )

        self.play(FadeIn(titulo_lag, shift=UP))
        self.wait(0.5)
        self.play(titulo_lag.animate.to_edge(UP))

        # 1. Energia cinetica

        sub1 = Text(
            "1. Energía cinética",
            font_size=28,
            color=BLUE
        )

        eq_T = MathTex(
            r"T = \frac{1}{2}mR^2\dot{\theta}^2",
            font_size=36
        )

        sub1.next_to(
            titulo_lag, DOWN, buff=0.5
        ).to_edge(LEFT, buff=1)

        eq_T.next_to(
            sub1, DOWN, aligned_edge=LEFT, buff=0.2
        )

        self.play(FadeIn(sub1), Write(eq_T))
        self.wait(1)

        # 2. Energia potencial

        sub2 = Text(
            "2. Energía potencial",
            font_size=28,
            color=GREEN
        )

        eq_V = MathTex(
            r"V = -mgR\cos\theta",
            font_size=36
        )

        sub2.next_to(
            eq_T, DOWN, buff=0.4
        ).to_edge(LEFT, buff=1)

        eq_V.next_to(
            sub2, DOWN, aligned_edge=LEFT, buff=0.2
        )

        self.play(FadeIn(sub2), Write(eq_V))
        self.wait(1)

        # 3. Lagrangiano

        sub3 = Text(
            "3. Lagrangiano  L = T - V",
            font_size=28,
            color=YELLOW
        )

        eq_L = MathTex(
            r"\mathcal{L} = "
            r"\frac{1}{2}mR^2\dot{\theta}^2"
            r" + mgR\cos\theta",
            font_size=36
        )

        sub3.next_to(
            eq_V, DOWN, buff=0.4
        ).to_edge(LEFT, buff=1)

        eq_L.next_to(
            sub3, DOWN, aligned_edge=LEFT, buff=0.2
        )

        self.play(FadeIn(sub3), Write(eq_L))
        self.wait(1)

        # 4. Euler-Lagrange con fuerzas no conservativas

        sub4 = Text(
            "4. Euler-Lagrange con fuerzas externas",
            font_size=28,
            color=RED
        )

        eq_EL = MathTex(
            r"\frac{d}{dt}\left("
            r"\frac{\partial\mathcal{L}}{\partial\dot{\theta}}"
            r"\right)"
            r"-\frac{\partial\mathcal{L}}{\partial\theta}"
            r"=",
            r"\underbrace{-k\dot{\theta}}_{\text{fricción}}"
            r"+"
            r"\underbrace{\tau}_{\text{torque externo}}",
            font_size=30
        )

        sub4.next_to(
            eq_L, DOWN, buff=0.4
        ).to_edge(LEFT, buff=1)

        eq_EL.next_to(
            sub4, DOWN, aligned_edge=LEFT, buff=0.2
        )

        self.play(FadeIn(sub4), Write(eq_EL))
        self.wait(2)

        # Despedida de las ecuaciones

        self.play(
            FadeOut(
                VGroup(
                    titulo_lag,
                    sub1, eq_T,
                    sub2, eq_V,
                    sub3, eq_L,
                    sub4, eq_EL
                )
            )
        )

        # --------------------------------------------------
        # PARAMETROS FISICOS
        # --------------------------------------------------

        R = 2.0                  # Longitud del pendulo (m)
        m = 1.0                  # Masa (kg)
        g = 9.81                 # Gravedad (m/s²)

        k = 1.5                  # Amortiguamiento viscoso (visible en ~3 ciclos)
        tau = 12.0               # Torque del pulso (N·m)
        t_pulso = 0.8            # Duración del pulso (s)

        theta0 = 0.0             # Reposo: péndulo colgando recto
        omega0 = 0.0             # Sin velocidad inicial

        t_max = 20.0
        dt = 0.01

        # --------------------------------------------------
        # ECUACION DE MOVIMIENTO
        # --------------------------------------------------

        def derivadas(estado, t):

            theta, omega = estado
            tau_t = tau if t < t_pulso else 0.0

            aceleracion = (
                -(g / R) * np.sin(theta)
                - (k / (m * R**2)) * omega
                + (tau_t / (m * R**2))
            )

            return np.array([
                omega,
                aceleracion
            ])

        # --------------------------------------------------
        # INTEGRADOR RUNGE-KUTTA DE CUARTO ORDEN
        # --------------------------------------------------

        def rk4(estado, dt, t):

            k1 = derivadas(estado, t)
            k2 = derivadas(estado + dt/2 * k1, t + dt/2)
            k3 = derivadas(estado + dt/2 * k2, t + dt/2)
            k4 = derivadas(estado + dt * k3,   t + dt)

            return estado + (dt/6) * (
                k1 + 2*k2 + 2*k3 + k4
            )

        # --------------------------------------------------
        # TRAYECTORIA
        # --------------------------------------------------

        tiempos = np.arange(0, t_max, dt)

        estados = [
            np.array([theta0, omega0])
        ]

        for i, t in enumerate(tiempos[1:]):
            estados.append(rk4(estados[-1], dt, t))

        thetas = np.array(estados)[:, 0]

        # --------------------------------------------------
        # ELEMENTOS VISUALES
        # --------------------------------------------------

        origen = UP * 2.5

        soporte = Line(
            LEFT * 3,
            RIGHT * 3,
            color=GRAY
        ).move_to(origen + UP * 0.2)

        hatch = VGroup(*[
            Line(
                LEFT * 0.15,
                RIGHT * 0.15,
                color=GRAY
            )
            .rotate(-PI/4)
            .move_to(
                soporte.get_start()
                + RIGHT * i * 0.3
                + UP * 0.1
            )
            for i in range(20)
        ])

        pivote = Dot(
            origen,
            radius=0.08,
            color=WHITE
        )

        self.theta = thetas[0]

        varilla = always_redraw(
            lambda: Line(
                origen,
                origen + R * np.array([
                    np.sin(self.theta),
                    -np.cos(self.theta),
                    0
                ]),
                color=WHITE,
                stroke_width=4
            )
        )

        masa = always_redraw(
            lambda: Dot(
                origen + R * np.array([
                    np.sin(self.theta),
                    -np.cos(self.theta),
                    0
                ]),
                radius=0.18,
                color=BLUE
            )
        )

        traza = TracedPath(
            masa.get_center,
            stroke_color=YELLOW,
            stroke_width=2,
            stroke_opacity=0.6
        )

        arco_angulo = always_redraw(
            lambda: Arc(
                radius=0.8,
                start_angle=-PI/2,
                angle=self.theta if abs(self.theta) > 0.001 else 0.001,
                color=YELLOW,
                stroke_width=3
            ).move_arc_center_to(origen)
        )

        etiqueta_theta = always_redraw(
            lambda: MathTex(
                r"\theta",
                color=YELLOW
            ).move_to(
                origen + 1.1 * np.array([
                    np.sin(self.theta/2),
                    -np.cos(self.theta/2),
                    0
                ])
            )
        )

        # --------------------------------------------------
        # INFORMACION FISICA EN PANTALLA
        # --------------------------------------------------

        titulo = Text(
            "Con torque inicial (pulso)",
            font_size=32
        ).to_corner(UL)

        lagrangiano = MathTex(
            r"\mathcal{L} = "
            r"\frac{1}{2}mR^2\dot{\theta}^2"
            r" + mgR\cos\theta",
            font_size=25
        ).next_to(
            titulo, DOWN, aligned_edge=LEFT, buff=0.3
        )

        eom = MathTex(
            r"\ddot{\theta} = "
            r"-\frac{g}{R}\sin\theta"
            r"-\frac{k}{mR^2}\dot{\theta}"
            r"+\frac{\tau}{mR^2}",
            font_size=25
        ).next_to(
            lagrangiano, DOWN, aligned_edge=LEFT, buff=0.2
        )

        coeficiente = MathTex(
            r"k = 1.5",
            font_size=25,
            color=YELLOW
        ).next_to(
            eom, DOWN, aligned_edge=LEFT, buff=0.2
        )

        torque = MathTex(
            r"\tau = 12\ \mathrm{N\,m}\ \text{(pulso 0.8\,s)}",
            font_size=25,
            color=ORANGE
        ).next_to(
            coeficiente, DOWN, aligned_edge=LEFT, buff=0.2
        )

        self.add(
            soporte,
            hatch,
            pivote,
            varilla,
            masa,
            traza,
            arco_angulo,
            etiqueta_theta,
            titulo,
            lagrangiano,
            eom,
            coeficiente,
            torque
        )

        self.wait(0.5)

        # --------------------------------------------------
        # ANIMACION
        # --------------------------------------------------

        def actualizar(mob, alpha):

            indice = alpha * (len(thetas) - 1)

            self.theta = np.interp(
                indice,
                np.arange(len(thetas)),
                thetas
            )

        self.play(
            UpdateFromAlphaFunc(
                pivote,
                actualizar
            ),
            run_time=14,
            rate_func=linear
        )

        self.wait(2)
