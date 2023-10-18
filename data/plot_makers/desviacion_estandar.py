import csv
import matplotlib.pyplot as plt
import sys
import numpy as np

def main():
    k = int(sys.argv[1])

    n = []
    standard = []
    relaxed = []
    squarish = []
    st_var = []
    r_var = []
    sq_var = []

    num = 1000

    csv_file = f'../datos_csv/out{k}.csv'

    with open(csv_file, 'r') as archivo_csv:
        lector_csv = csv.reader(archivo_csv, delimiter=';')

        for fila in lector_csv:
            st, v1, r, v2, sq, v3 = map(float, fila)
            n.append(num)
            standard.append(st)
            relaxed.append(r)
            squarish.append(sq)
            st_var.append(v1)
            r_var.append(v2)
            sq_var.append(v3)
            num += 1000

    # Calcular la desviación estándar
    st_sigma = np.sqrt(st_var)
    r_sigma = np.sqrt(r_var)
    sq_sigma = np.sqrt(sq_var)

    plt.figure(figsize=(10, 6))
    #plt.plot(n, standard, label="standard")
    #plt.plot(n, relaxed, label="relaxed", color = "green")
    plt.plot(n, squarish, label="squarish", color = "red")

    # Agregar barras de error para la desviación estándar
    #plt.errorbar(n, standard, yerr=1*st_sigma, fmt='none', label="Standard Error", color='blue', alpha=0.6)
    #plt.errorbar(n, relaxed, yerr=1*r_sigma, fmt='none', label="Relaxed Error", color='green', alpha=0.6)
    plt.errorbar(n, squarish, yerr=1*sq_sigma, fmt='none', label="Squarish Error", color='red', alpha=0.6)

    plt.xlabel('n')
    plt.ylabel('C(n)')
    plt.title(f'Búsqueda del más cercano con k = {k}')
    plt.legend(loc='upper left')

    plt.grid();
    plt.show()

if __name__ == '__main__':
    main()

