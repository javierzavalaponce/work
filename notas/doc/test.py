from manim import *

class ProductoPunto(Scene):
    def construct(self):
        titulo = Text("Producto punto", font_size=48).to_edge(UP)
        self.play(Write(titulo))
        
        axes = Axes(
            x_range=[-1, 3, 1],
            y_range=[-1, 3, 1],
            x_length=6,
            y_length=6,
            axis_config={"include_numbers": True, "color": GRAY}
        )
        self.play(Create(axes))
        
        # u = (1, 1)  y  v = (1, 0)
        u = Arrow(axes.c2p(0, 0), axes.c2p(1, 1), buff=0, color=BLUE)
        v = Arrow(axes.c2p(0, 0), axes.c2p(1, 0), buff=0, color=RED)
        
        label_u = MathTex(r"\vec{u} = (1, 1)", color=BLUE).next_to(u, LEFT)
        label_v = MathTex(r"\vec{v} = (1, 0)", color=RED).next_to(v, DOWN)
        
        self.play(GrowArrow(u), GrowArrow(v))
        self.play(Write(label_u), Write(label_v))
        self.wait(1)
        
        formula = MathTex(
            r"\vec{u} \cdot \vec{v} = u_1 v_1 + u_2 v_2"
        ).to_edge(DOWN)
        self.play(Write(formula))
        self.wait(1)
        
        sustitucion = MathTex(
            r"\vec{u} \cdot \vec{v} = (1)(1) + (1)(0) = 1"
        ).to_edge(DOWN)
        self.play(Transform(formula, sustitucion))
        self.wait(2)





