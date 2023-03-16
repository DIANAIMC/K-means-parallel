import pandas as pd
import matplotlib.pyplot as plt
import os

"""
FALTA GRÁFICA DE SPEED-UP
"""

if __name__ == "__main__":
    directorio_actual = os.getcwd()
    os.chdir(f'{directorio_actual}/datos')
    # Leer los archivos CSV
    df_serial = pd.read_csv("resultados_serial.csv")
    df_paralelo = pd.read_csv("resultados_paralelo.csv")

    # Graficar los resultados de modo serial
    plt.figure(figsize=(10, 6))
    for tam in df_serial["tamaño"].unique():
        df_tam = df_serial[df_serial["tamaño"] == tam]
        plt.plot(df_tam["cores"], df_tam["promedio"], label=f"tamaño {tam}")
    plt.xlabel("cores")
    plt.ylabel("promedio")
    plt.title("Modo serial")
    plt.legend()
    plt.show()

    # Graficar los resultados de modo paralelo
    plt.figure(figsize=(10, 6))
    for tam in df_paralelo["tamaño"].unique():
        df_tam = df_paralelo[df_paralelo["tamaño"] == tam]
        plt.plot(df_tam["cores"], df_tam["promedio"], label=f"tamaño {tam}")
    plt.xlabel("cores")
    plt.ylabel("promedio")
    plt.title("Modo paralelo")
    plt.legend()
    plt.show()
