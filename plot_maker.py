import csv
import matplotlib.pyplot as plt

n = []
standard = []
relaxed = []
squarish = []

num = 1000;

with open('out.csv', 'r') as archivo_csv:
    lector_csv = csv.reader(archivo_csv, delimiter=';')

    for fila in lector_csv:
        st, _, r, _, sq, _ = fila
        n.append(float(num))
        standard.append(float(st))
        relaxed.append(float(r))
        squarish.append(float(sq))
        num += 1000

plt.figure(figsize=(10,6))
plt.plot(n, standard, label="standard")
plt.plot(n, relaxed, label="relaxed")
plt.plot(n, squarish, label="squarish")

plt.xlabel('n')
plt.ylabel('C(n)')
plt.title('Nearest neighbor search')
plt.legend()

plt.show()

