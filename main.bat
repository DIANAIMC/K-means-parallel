@echo off

rem Definir los tamaños de entrada
set tamanios_entrada=100000 200000 300000 400000 600000 800000 1000000
set cores=2 4 8 16

rem Inicializar el archivo CSV con encabezados
echo cores,tamano,tiempo > resultados.csv
echo EMPEZAMOS

::serial
for %%t in (%tamanios_entrada%) do (
    set suma_serial=0
    rem Ejecutar el programa 10 veces
    for /l %%i in (0, 1, 11) do (
        rem Crear el archivo temporal con los argumentos de entrada
        serial.exe %%t > temp.txt
        python decimales.py %%t 1
    )
)

::paralelo
for %%c in (%cores%) do (
    for %%t in (%tamanios_entrada%) do (
        set suma_paralelo=0
        rem Ejecutar el programa 10 veces
        for /l %%i in (1, 1, 10) do (
            paralelo.exe %%t %%c > temp.txt
            python decimales.py %%t %%c
        )
    )
)

rem Eliminar el archivo temporal
del tmp.txt
