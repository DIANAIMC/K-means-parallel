#!/bin/bash

# Definir los tamaños de entrada
tamanios_entrada=(100000 200000 300000 400000 600000 800000 1000000)

# Inicializar el archivo CSV con encabezados
echo "tamaño, promedio" > resultados_serial.csv
echo "tamaño, promedio" > resultados_paralelo.csv

for tam in "${tamanios_entrada[@]}"; do
    suma=0
    # Ejecutar el programa 10 veces
    for i in {1..10}; do
        # Ejecutar el programa y almacenar el resultado en la variable "resultado_actual"
        resultado_actual=$(.\serial.exe $tam)

        # Sumar el resultado actual a la suma total
        suma=$((suma + resultado_actual))
    done

    # Calcular el promedio de los resultados
    promedio=$((suma / 10))

    # Agregar el resultado al archivo CSV
    echo "$tam,$promedio" >> resultados_serial.csv
done

for tam in "${tamanios_entrada[@]}"; do
    suma=0
    # Ejecutar el programa 10 veces
    for i in {1..10}; do
        # Ejecutar el programa y almacenar el resultado en la variable "resultado_actual"
        resultado_actual=$(.\paralelo.exe $tam)

        # Sumar el resultado actual a la suma total
        suma=$((suma + resultado_actual))
    done

    # Calcular el promedio de los resultados
    promedio=$((suma / 10))

    # Agregar el resultado al archivo CSV
    echo "$tam,$promedio" >> resultados_paralelo.csv
done

#• Número de hilos
# {1, (número de cores virtuales)/2, número de cores virtuales, número de cores virtuales*2}
# Calcular speedup