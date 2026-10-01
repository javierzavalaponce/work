from manim import *
import numpy as np

class PenduloSimple(Scene):
    def construct(self):
        # ─── Parámetros físicos ───
        L = 2.0
        g = 9.81
        theta0 = 60 * DEGREES
        omega0 = 0.0
        t_max = 10.0
        dt = 0.02
        
        # ─── Ecuación de movimiento ───
        def derivadas(estado):
            theta, omega = estado
            return np.array([omega, -(g / L) * np.sin(theta)])
        
        def rk4(estado, dt):
            k1 = derivadas(estado)
            k2 = derivadas(estado + dt/2 * k1)
            k3 = derivadas(estado + dt/2 * k2)
            k4 = derivadas(estado + dt * k3)
            return estado + (dt/6) * (k1 + 2*k2 + 2*k3 + k4)
        
        # ─── Trayectoria ───
        tiempos = np.arange(0, t_max, dt)
        estados = [np.array([theta0, omega0])]
        for _ in tiempos[1:]:
            estados.append(rk4(estados[-1], dt))
        thetas = np.array(estados)[:, 0]
        
        # ─── Elementos visuales ───
        origen = UP * 2.5
        
        soporte = Line(LEFT * 3, RIGHT * 3, color=GRAY).move_to(origen + UP * 0.2)
        hatch = VGroup(*[
            Line(LEFT * 0.15, RIGHT * 0.15, color=GRAY)
            .rotate(-PI/4)
            .move_to(soporte.get_start() + RIGHT * i * 0.3 + UP * 0.1)
            for i in range(20)
        ])
        pivote = Dot(origen, radius=0.08, color=WHITE)
        
        # ✅ CLAVE: definir self.theta ANTES de always_redraw
        self.theta = thetas[0]
        
        varilla = always_redraw(
            lambda: Line(
                origen,
                origen + L * np.array([np.sin(self.theta), -np.cos(self.theta), 0]),
                color=WHITE,
                stroke_width=4
            )
        )
        masa = always_redraw(
            lambda: Dot(
                origen + L * np.array([np.sin(self.theta), -np.cos(self.theta), 0]),
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
                angle=self.theta,
                color=YELLOW,
                stroke_width=3
            ).move_arc_center_to(origen)
        )
        etiqueta_theta = always_redraw(
            lambda: MathTex(r"\theta", color=YELLOW).move_to(
                origen + 1.1 * np.array([
                    np.sin(self.theta/2),
                    -np.cos(self.theta/2),
                    0
                ])
            )
        )
        
        titulo = Text("Péndulo Simple", font_size=32).to_corner(UL)
        lagrangiano = MathTex(
            r"\mathcal{L} = \frac{1}{2}mL^2\dot{\theta}^2 + mgL\cos\theta",
            font_size=28
        ).next_to(titulo, DOWN, aligned_edge=LEFT, buff=0.3)
        eom = MathTex(
            r"\ddot{\theta} = -\frac{g}{L}\sin\theta",
            font_size=28
        ).next_to(lagrangiano, DOWN, aligned_edge=LEFT, buff=0.2)
        
        self.add(soporte, hatch, pivote, varilla, masa, traza,
                 arco_angulo, etiqueta_theta, titulo, lagrangiano, eom)
        self.wait(0.5)
        
        for theta in thetas:
            self.theta = theta
            self.wait(dt)

