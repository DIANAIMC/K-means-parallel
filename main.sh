#!/bin/bash

# Definir los tamaños de entrada
tamanios_entrada=(100000 200000 300000 400000 600000 800000 1000000)
cores=(2 4 8 16)

# Inicializar el archivo CSV con encabezados
echo "cores,tamaño,promedio" > datos/resultados_serial.csv
echo "cores,tamaño,promedio" > datos/resultados_paralelo.csv
echo "EMPEZAMOS"

for tam in "${tamanios_entrada[@]}"; do
    suma_serial=0
    # Ejecutar el programa 10 veces
    for i in {0..11}; do
        # Ejecutar el programa y almacenar el resultado en la variable "resultado_actual"
        resultado_serial=$(./serial.exe $tam $cores)
        # Sumar el resultado actual a la suma total
        suma_serial=$((suma_serial + resultado_serial))
    done

    # Calcular el promedio de los resultados
    promedio_serial=$((suma_serial / 10))
    # Agregar el resultado al archivo CSV
    echo "1,$tam,$promedio_serial" >> datos/resultados_serial.csv
done

for cores in "${cores[@]}"; do
    for tam in "${tamanios_entrada[@]}"; do
        suma_paralelo=0
        # Ejecutar el programa 10 veces
        for i in {1..10}; do
            # Ejecutar el programa y almacenar el resultado en la variable "resultado_actual"
            resultado_paralelo=$(./paralelo.exe $tam $cores)
            # Sumar el resultado actual a la suma total
            suma_paralelo=$((suma_paralelo + resultado_paralelo))
        done
        # Calcular el promedio de los resultados
        promedio_paralelo=$((suma_paralelo / 10))
        # Agregar el resultado al archivo CSV
        echo "$cores,$tam,$promedio_paralelo" >> datos/resultados_paralelo.csv
    done
done


#• Número de hilos
# {1, (número de cores virtuales)/2, número de cores virtuales, número de cores virtuales*2}
# Calcular speedup

##### PRUEBAS1:
#   DATOS   SERIAL  CORRECTO    PARALELO    CORRECTO
#   100000  0.388   NO          0.139       NO
#   200000  0.0769  SI          0.026       SI
#   300000  0.132   SI          0.0869      SI
#   400000  1.085   NO          0.0369      SI
#   600000  0.207   SI          0.137       SI
#   800000  9.648   NO          0.195       SI
#  1000000  0.411   SI          0.783       NO          


# TEORÍA: A veces no funciona por donde se inicializan los centroides,
# pero siempre falla en el mismo número de datos