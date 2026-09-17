from itertools import product

# --- Producto de dos listas ---
A = [1, 2]
B = ['a', 'b']

resultado = list(product(A, B))
print(resultado)
# Salida: [(1, 'a'), (1, 'b'), (2, 'a'), (2, 'b')]

resultado = [(x, y) for x in A for y in B]
print(resultado)
# Salida: [(1, 'a'), (1, 'b'), (2, 'a'), (2, 'b')]

resultado = []
for x in A:
    for y in B:
        resultado.append((x, y))

print(resultado)
# Salida: [(1, 'a'), (1, 'b'), (2, 'a'), (2, 'b')]