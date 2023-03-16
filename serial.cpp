#include <omp.h>
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

using namespace std;

// SERIAL

/*
    points = matriz de arreglos, cada row es un punto y cada punto contiene, 
        coordenadas y cluster al que pertenece
    n_clusters = número de clusters
    size = número de puntos
    max_iterations
*/
void kmeans(float** points, int n_clusters, long long int size, int max_iterations) {
    // Initialize cluster assignments randomly
    for (long long int i=0; i < size; i++) {
        //aquí le estamos asignando aleatoriamente a los puntos sus clusters.
        points[i][2] = rand() % n_clusters;
    } 

    // Main loop: iterau hasta que ningun punto cambie de cluster
    bool all_stable = false;
    int iteration = 0;
    while (!all_stable && iteration < max_iterations) {
        all_stable = true;
        iteration++;
        // Inicializamos los centroides de los clusters
        //centroids es un arreglo del mismo tamaño que el número de clusters
        float** centroids = new float*[n_clusters];
        //counts es un arreglo de ints del del número de puntos en el centroide del cluser
        //es un arreglo con el tamaño del número de centroides
        int* counts = new int[n_clusters];
        // Inicializamos los centroides de los clusters
        for (int i=0; i < n_clusters; i++) {
            //inicializamos los centroides en coordenadas aleatorias entre 0 y 1
            centroids[i] = new float[2]{(float)rand()/RAND_MAX, (float)rand()/RAND_MAX};
            //counts de ese mismo valor es 0
            counts[i] = 0;
        }
        // Actualiza los centroides basados en la asignación actual de los clusters
        //de cero a la longitud de nuestros puntos
        for (long long int i=0; i < size; i++) {
            //cluster es igual al valor en la tercera columna de points
            int cluster = (int) points[i][2];
            //añadimos cada punto a su centroide correspondiente
            //centroids contendrá la suma de las coordenadas de todos los puntos asignados a cada cluster
            // x
            centroids[cluster][0] += points[i][0];
            // y
            centroids[cluster][1] += points[i][1];
            //contamos cuantos puntos tenemos por cluster en ese centroide
            counts[cluster]++;
        }
        //esta sección actualiza los centroides de cada clúster para que estén 
        //en el centro de todos los puntos asignados a ese clúster.
        for (int i=0; i < n_clusters; i++) {
            if (counts[i] > 0) {
                // x
                centroids[i][0] /= counts[i];
                // y
                centroids[i][1] /= counts[i];
            }
        }

        //desde i=0 hasta el size de nuestros puntos
        for (long long int i=0; i < size; i++) {
            //que la minima distancia sea lo más grande posible
            float min_distance = INFINITY;
            int min_cluster = -1;
            //desde cero hasta nuestro número de clusters
            for (int j=0; j < n_clusters; j++) {
            //calculamos la distancia de cada punto al centroide
                float dx = points[i][0] - centroids[j][0];
                float dy = points[i][1] - centroids[j][1];
            //la definición oficial de la distancia según kmeans
                float distance = sqrt(dx*dx + dy*dy);
            //si la distancia con el centroide es menor que la "menor distancia"
            //entonces la menor distancia cambia y el min_cluster también
                if (distance < min_distance) {
                    min_distance = distance;
                    min_cluster = j;
                }
            }
            //si el min_cluster es distinto de al cluster al que pertenezco, entonces cambio de cluster
            if (min_cluster != points[i][2]) {
                points[i][2] = min_cluster;
                all_stable = false;
            }
        }

        // Clean up centroids and counts
        for (int i=0; i < n_clusters; i++) {
            delete[] centroids[i];
        }
        delete[] centroids;
        delete[] counts;
    
    }
    //cout << "El numero de iteraciones fueron: " << iteration << "\n";
}

void load_CSV(string file_name, float** points, long long int size) {
    ifstream in(file_name);
    if (!in) {
        cerr << "Couldn't read file: " << file_name << "\n";
    }
    long long int point_number = 0; 
    while (!in.eof() && (point_number < size)) {
        char* line = new char[12];
        streamsize row_size = 12;
        in.read(line, row_size);
        string row = line;
        if (row.size() < 12) {
            continue;
        }
        points[point_number][0] = stof(row.substr(0, 5));
        points[point_number][1] = stof(row.substr(6, 5));
        point_number++;
    }
}

void save_to_CSV(string file_name, float** points, long long int size) {
    fstream fout;
    fout.open(file_name, ios::out);
    for (long long int i = 0; i < size; i++) {
        fout << points[i][0] << ","
             << points[i][1] << ","
             << points[i][2] << "\n";
    }
}

int main(int argc, char** argv) {
    if(argc < 2) {
        cerr << "Error: el tamanio de los datos debe ser un argumento de linea de comando.\n";
        return 1;
    }
    const long long int size = atoll(argv[1]);
    double start_serial = 0.0;
    const int n_clusters = 5;
    const string input_file_name = "datos\\" + to_string(size)+"_data.csv";
    const string output_file_name_serial = "datos\\" + to_string(size)+"_results_serial.csv";       
    float** serial = new float*[size];

    for(long long int i = 0; i < size; i++) {
        serial[i] = new float[3]{0.0, 0.0, -1}; 
        // index 0: position x
        // index 1: position y 
        // index 2: cluster
    }

    load_CSV(input_file_name, serial, size);

    start_serial = omp_get_wtime();
    kmeans(serial, n_clusters, size, 20); 
    double tiempo_ejecucion_serial = omp_get_wtime() - start_serial;
    cout <<  tiempo_ejecucion_serial;
    save_to_CSV(output_file_name_serial, serial, size);

    for(long long int i = 0; i < size; i++) {
        delete[] serial[i];
    }
    delete[] serial;
    return tiempo_ejecucion_serial;
}