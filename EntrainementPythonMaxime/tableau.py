import numpy as np

# Créer un tableau 2D de 10x10 rempli de zéros
tableau = np.zeros((10, 10), dtype=int)


for i in range(10):
    for j in range(10):
        tableau[i][j] = (i*10) + (j+1)

for i in range(10):
    for j in range(10):
        print(tableau[i][j], end = " ")
    print()


