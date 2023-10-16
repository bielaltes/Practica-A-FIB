import csv
import matplotlib.pyplot as plt
import sys
import numpy as np
from scipy import stats

def main():

    k = int(sys.argv[1])

    n = []
    standard = []
    relaxed = []
    squarish = []

    num = 1000;

    csv_file = f'out{k}.csv'

    with open(csv_file, 'r') as archivo_csv:
        lector_csv = csv.reader(archivo_csv, delimiter=';')

        for fila in lector_csv:
            st, _, r, _, sq, _ = fila
            n.append(np.log(float(num)))
            standard.append(np.log(float(st)))
            relaxed.append(np.log(float(r)))
            squarish.append(np.log(float(sq)))
            num += 1000

    slope_standard, intercept_standard, _, _, _ = stats.linregress(n, standard)
    slope_relaxed, intercept_relaxed, _, _, _ = stats.linregress(n, relaxed)
    slope_squarish, intercept_squarish, _, _, _ = stats.linregress(n, squarish)

    plt.figure(figsize=(10,6))

    # Especifica un color para las líneas discontinuas y ajusta la transparencia (alfa)
    color_standard = 'b'
    color_relaxed = 'g'
    color_squarish = 'r'
    alpha_discontinua = 0.5  # Cambia el valor alfa

    plt.plot(n, standard, label="standard", color=color_standard)
    plt.plot(n, relaxed, label="relaxed", color=color_relaxed)
    plt.plot(n, squarish, label="squarish", color=color_squarish)

    # Trazar líneas ajustadas con el mismo color y transparencia
    plt.plot(n, np.array(n) * slope_standard + intercept_standard, '--', label=f"Linea Ajustada (standard)", color=color_standard)
    plt.plot(n, np.array(n) * slope_relaxed + intercept_relaxed, '--', label=f"Linea Ajustada (relaxed)", color=color_relaxed, alpha=alpha_discontinua)
    plt.plot(n, np.array(n) * slope_squarish + intercept_squarish, '--', label=f"Linea Ajustada (squarish)", color=color_squarish, alpha=alpha_discontinua)

    plt.xlabel('n')
    plt.ylabel('C(n)')
    plt.title(f'Búsqueda del más cercano con k = {k}')
    
    # Agrega etiquetas personalizadas con fuente 10 y más a la derecha
    x_offset = 3  # Ajusta la posición horizontal
    fontsize = 10

    plt.text(n[0] + x_offset, np.array(n)[0] * slope_standard + intercept_standard, f'standard: y = {slope_standard:.4f}x + {intercept_standard:.4f}', fontsize=fontsize, verticalalignment='top', ha='left')
    plt.text(n[0] + x_offset, np.array(n)[0] * slope_relaxed + intercept_relaxed, f'relaxed: y = {slope_relaxed:.4f}x + {intercept_relaxed:.4f}', fontsize=fontsize, verticalalignment='top', ha='left')
    plt.text(n[0] + x_offset, np.array(n)[0] * slope_squarish + intercept_squarish, f'squarish: y = {slope_squarish:.4f}x + {intercept_squarish:.4f}', fontsize=fontsize, verticalalignment='top', ha='left')

    # Posiciona la leyenda manualmente
    plt.legend()

    plt.show()

if __name__ == '__main__':
    main()

