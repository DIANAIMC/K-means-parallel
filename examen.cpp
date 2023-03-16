#include <omp.h>
#include <iostream>
#include <time.h>
using namespace std; 

int main(){
    int clientes_malos_serial = 0;
    int clientes_buenos_serial = 0;
    int clientes_malos_paralelo = 0;
    int clientes_buenos_paralelo = 0;
    double start_serial = 0.0;
    double start_paralelo = 0.0;
    // indica el tamaño de la cartera de clientes
    long long int numero_clientes = 100000000;

    // crea la cartera de clientes
    int* scores_crediticios {new int[numero_clientes]{}};

    // cambia la semilla para generar diferentes números aleatorios
    srand(time(NULL));

    // Crea aleatoriamente los scores crediticios de la cartera de clientes
    for (long long int i=0; i<numero_clientes; i++){
        scores_crediticios[i]=rand()%100+1;
    }
    // Mi código serial
    start_serial = omp_get_wtime();
    for (long long int i=0; i<numero_clientes; i++){
         if (scores_crediticios[i] > 50){
            clientes_buenos_serial++;
        } else {
            clientes_malos_serial++;
            }
    }
    cout << "tiempo de ejecución serial: " <<  omp_get_wtime() - start_serial <<"\n";
    cout << clientes_buenos_serial << " clientes buenos" << "\n";
    cout << clientes_malos_serial << " clientes malos" << "\n";

    // Mi código paralelo
    start_paralelo = omp_get_wtime();
    /*
    #pragma omp parallel for
	for (long long int i=0; i<numero_clientes; i++){
        if (scores_crediticios[i] > 50){
            #pragma omp atomic
            clientes_buenos_paralelo++;
        } else {
            #pragma omp atomic
            clientes_malos_paralelo++;
            }
    }
    */
    #pragma omp for schedule(static, 2)
	for (long long int i=0; i<numero_clientes; i++){
        if (scores_crediticios[i] > 50){
            clientes_buenos_paralelo++;
        } else {
            clientes_malos_paralelo++;
            }
    }
    cout << "tiempo de ejecución paralelo: " <<  omp_get_wtime() - start_paralelo <<"\n";
    cout << clientes_buenos_paralelo << " clientes buenos" << "\n";
    cout << clientes_malos_paralelo << " clientes malos" << "\n";

    delete[] scores_crediticios;
}