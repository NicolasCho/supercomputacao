%%writefile paralelismo_gpu.cu
#include <iostream>
#include <vector>
#include <algorithm>
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/functional.h>
#include <omp.h>
#include <fstream>
using namespace std;
struct filme {
    int id;
    int inicio;
    int fim;
    int duracao;
    int categoria;
};

int main(int argc, char *argv[]){
    clock_t start, end;
    start = clock();

    //Recebe o nome da variavel testada e o nome do arquivo
    string variavel = argv[1]; 
    string arquivo = argv[2];


    int N, M;
    std::cin >> N >> M;

    thrust::host_vector<int> categories(N);
    thrust::host_vector<int> start_times(N);
    thrust::host_vector<int> end_times(N);
    thrust::host_vector<int> L(M);

    for (int i = 0; i < M; i++) {
        std::cin >> L[i];
    }

    for (int i = 0; i < N; i++) {
        std::cin >> start_times[i] >> end_times[i] >> categories[i];
    }


     thrust::device_vector<int> dp((N + 1) * (M + 1), 0);

     for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            int max_count = 0;
            for (int k = 0; k < i; k++) {
                if (categories[k] == j && end_times[k] <= start_times[i] &&
                    dp[(k * (M + 1)) + j - 1] + 1 <= L[j - 1]) {
                    max_count = thrust::max(max_count, thrust::raw_reference_cast<int>(dp[(k * (M + 1)) + j - 1]) + 1);
                } else {
                    max_count = thrust::max(max_count, thrust::raw_reference_cast<int>(dp[(k * (M + 1)) + j]));
                }
            }
            dp[(i * (M + 1)) + j] = max_count;
        }
    }

    int max_count = *thrust::max_element(dp.begin() + N * (M + 1) + 1, dp.begin() + (N + 1) * (M + 1));

    //std::cout << "Número máximo de filmes que podem ser assistidos: " << max_count << std::endl;


    end = clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);


    // Escreve novo resultado no csv
    // Métricas: número de filmes alocados, quantidade de horas ocupadas, tempo de execução
    ofstream outputFile;
    string result_file = "results.csv";  // Caminho relativo ao script que chama a heuristica
    outputFile.open(result_file, ios::app);
    string result = variavel + "," + to_string(max_count) + "," + "0" + 
        "," + to_string(time_taken) + "," + arquivo;
    outputFile << result << endl;
    return 0;
}