
class CircularBuffer:

    def __init__(self, capacidad):
        self.capacidad = capacidad
        self.buffer = [None] * capacidad
        self.indice = 0
        self.lleno = False

    def agregar(self, dato):
        self.buffer[self.indice] = dato

        self.indice = (self.indice + 1) % self.capacidad

        if self.indice == 0:
            self.lleno = True

    def obtener(self):
        if not self.lleno:
            return self.buffer[:self.indice]

        return self.buffer[self.indice:] + self.buffer[:self.indice]
