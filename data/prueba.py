import csv
import matplotlib.pyplot as plt
import sys
import math

def main():
    k = int(sys.argv[1])

    n = []
    standard = []
    relaxed = []
    squarish = []
    std_standard = []
    std_relaxed = []
    std_squarish = []

    num = 1000

    csv_file = f'out{k}.csv'

    with open(csv_file, 'r') as archivo_csv:
        lector_csv = csv.reader(archivo_csv, delimiter=';')

        for fila in lector_csv:
            st, st_var, r, r_var, sq, sq_var = fila
            n.append(float(num))
            standard.append(float(st))
            relaxed.append(float(r))
            squarish.append(float(sq))
            std_standard.append(2 * math.sqrt(float(st_var)))  # Desviación estándar = raíz cuadrada de la varianza
            std_relaxed.append(2 * math.sqrt(float(r_var)))
            std_squarish.append(2 * math.sqrt(float(sq_var)))
            num += 1000

    plt.figure(figsize=(10, 6))
    #plt.errorbar(n, standard, yerr=std_standard, label="standard", capsize=5)
    #lt.errorbar(n, relaxed, yerr=std_relaxed, label="relaxed", capsize=5, color='green')
    plt.errorbar(n, squarish, yerr=std_squarish, label="squarish", capsize=5, color = 'red')

    plt.xlabel('n')
    plt.ylabel('C(n)')
    plt.title(f'Búsqueda del más cercano con k = {k}')
    plt.legend(loc='upper left')

    plt.show()

if __name__ == '__main__':
    main()

