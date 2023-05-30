#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <iostream>
#include <fstream>
#include <iostream>
using namespace std;
int main(){
  // Ler os dados do arquivo de entrada
  //N = numero de filmes;  M = numero de categorias
  int N = 0;
  int M = 0;

  cin >> N >> M;

   // Vetores cpu
  thrust::host_vector<int> start_times_dev(N);
  thrust::host_vector<int> end_times_dev(N);
  thrust::host_vector<int> categories_dev(M);

  // Preencher vetor de categorias
  int n_filmes_categoria;
  for (int i = 0; i < M; i++){
      cin >> n_filmes_categoria;
      categories_dev.push_back(n_filmes_categoria);
  }

  // Preencher vetores de horarios (inicio e fim)
  int inicio, fim;
  for (int i = 0; i < N; i++){
      cin >> inicio;
      cin >> fim;
      start_times_dev.push_back(inicio);
      end_times_dev.push_back(fim);
  }

  // Carregar os dados do arquivo de entrada na memória da GPU
  thrust::device_vector<int> start_times(start_times_dev);
  thrust::device_vector<int> end_times(end_times_dev);
  thrust::device_vector<int> categories(categories_dev);

  // Criar a matriz de programação dinâmica
  thrust::device_vector<int> dp((N+1) * (M+1), 0);

  // Inicializar a primeira linha da matriz com zeros
  thrust::fill(dp.begin(), dp.begin() + M + 1, 0);

  // Preencher a matriz com as soluções para subproblemas menores
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= M; j++) {
      // Encontrar o número máximo de filmes que podem ser assistidos até o filme i e categoria j
      int max_count = 0;
      for (int k = 0; k < i; k++) {
        if (categories[k] == j && end_times[k] <= start_times[i] && dp[(k*(M+1)) + j-1] + 1 <= categories[j-1]) {
          max_count = max(max_count, dp[(k*(M+1)) + j-1] + 1);
        } else {
          max_count = max(max_count, dp[(k*(M+1)) + j]);
        }
      }
      dp[(i*(M+1)) + j] = max_count;
    }
  }

  // Encontrar o número máximo de filmes que podem ser assistidos
  int max_count = 0;
  for (int j = 1; j <= M; j++) {
    max_count = max(max_count, dp[(N*(M+1)) + j]);
  }

  // Escrever o resultado no arquivo de saída
  ofstream outputFile;
  string result_file = "resultado.txt";  // Caminho relativo ao script que chama a heuristica
  outputFile.open(result_file, ios::app);
  string result = to_string(max_count);
  outputFile << result << endl;
  return 0;

}
