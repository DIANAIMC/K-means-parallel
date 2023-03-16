import sys
puntos = int(sys.argv[1])
hilos = int(sys.argv[2])

def procesar_archivo(nombre_archivo):
    with open(nombre_archivo, 'r') as archivo:
        primera_linea = archivo.readline()
        numero = float(primera_linea.strip())
    return numero

nombre_archivo = 'temp.txt'
resultado = procesar_archivo(nombre_archivo)
res = f"{hilos},{puntos},{resultado}"

with open('resultados.csv', 'a') as archivo:
    # Escribe la línea en el archivo CSV
    archivo.write(res + '\n')