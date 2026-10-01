class Pendulo:

    def __init__(self, longitud, theta):
        self.longitud=longitud
        self.theta=theta
        
    def mostrar(self):
        print("longitud:", self.longitud)
        print("theta:", self.theta)


p1 = Pendulo(2.0, 60)
p2 = Pendulo(1.0, 30)
p1.theta = 90

p1.mostrar()
p2.mostrar()

