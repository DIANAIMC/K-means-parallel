# K-means-parallel

Descripción del código y estrategia de paralelización
Nuestro código en serial.cpp en primera instancia implementa el algoritmo de k-means de manera serial. La aproximación que hicimos al algoritmo fue darle primero a cada punto un cluster aleatorio, para después entrar a un while de donde sólo se puede salir si el algoritmo ya convergió, es decir, los puntos y los centroides ya no se mueven, o si se alcanzó el número máximo de iteraciones especificadas en los parámetros. 
Después, creamos los centroides y los ponemos en unas coordenadas aleatorias, para poder empezar a distribuir todos los puntos en centroides también de forma aleatoria. Una vez con los centroides creados actualizamos la posición del centroide al centro de todos los puntos que le pertenecen. 
Ya con todos los puntos distribuidos por centroide, ahora medimos su distancia mínima con todos los centroides y lo reubicamos al centroide correspondiente de ser necesario el cambio. Para cuando salgan del while, los puntos deberían estar divididos correctamente por su tipo de cluster.
En paralelo.cpp hacemos algo similar, pero con los for paralelizados que consideramos necesarios para acelerar el proceso y maximizar el speed up.
El archivo de graficas_speed.py lo usamos para graficar los clusters y asegurarnos de que el resultado que estábamos obteniendo era el deseado. 
Por último, el main.bat automatiza nuestro experimento para mandar todos los resultados directamente a un csv del cual pudiéramos graficar e interpretar resultados.

Estrategia de paralelización
Nuestra estrategia para paralelizar consistió en primero analizar el código serial poco a poco y poder notar las partes paralelizables, identificar el tipo de for paralelizado que podíamos usar y aplicarlo. Eventualmente el resultado fue:
•	#pragma omp parallel for para asignar cada punto a un cluster aleatorio al principio del algoritmo.
•	#pragma omp parallel for reduction (&&:all_stable) para reducir el tiempo que toman los for en donde calculamos las distancias de los puntos a cada centroide y los cambiamos de centroide de ser necesario.
En conclusión, paralelizamos las partes donde había la mayor cantidad de instrucciones (cuando usábamos el size completo de los puntos) y donde paralelizar implicaba una gran mejora en el tiempo de ejecución, fuimos cuidadosas de no paralelizar todo, para evitar condiciones de carrera y para evitar paralelizar donde hacerlo no implicaba mejor performance.

Descripción de la evaluación experimental de desempeño
Explicación detallada de la definición del experimento.
Para realizar nuestro experimento, lo dividimos en 2 partes y cambiamos algunos parámetros:
•	Para cada tamaño de datos (desde 100 mil hasta un millón) hicimos 10 veces cada uno y promediamos.
•	Después para cada número de cores que escogimos (entre 2 y 16) repetimos el ciclo anterior, es decir, para cada número de cores hacemos los 10 tamaños distintos.

Descripción del equipo donde se ejecutaron los experimentos en términos de hardware y software.
La computadora en la que ejecutamos el experimento es una Huawei Matebook 14 D14 de 11ava generación.
•	Intel Core i7 
•	16gb de RAM
•	512 gb de memoria
•	Windows 11
Lo hicimos todo en Visual Studio Code en cuestión de software.

Interpretación y análisis de resultados.
Debido a nuestros resultados llegamos a varias conclusiones.
•	Cuando aumentamos el número de hilos, sí disminuye el tiempo de ejecución pero sólo hasta cierto punto, a partir de 8 hilos baja en rendimiento, pero siempre manteniéndose más rápido que el serial.
•	El mejor tiempo de ejecución que encontramos fue cuando utilizábamos 4 hilos.
•	El mejor speedup que encontramos (con los mismos 4 hilos mencionados anteriormente) fue de: 3.267
