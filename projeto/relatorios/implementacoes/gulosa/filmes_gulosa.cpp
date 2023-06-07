#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>
using namespace std;

int main(int argc, char *argv[]){
    //Recebe o nome da variavel testada e o nome do arquivo
    string variavel = argv[1]; 
    string arquivo = argv[2];

    clock_t start, end;
    start = clock();
    
    struct filme{
        int id;
        int inicio;
        int fim;
        int duracao;
        int categoria;
    };

    int n = 0;
    int c = 0;


    vector<filme> filmes;
    vector<int> categorias;
    vector<filme> lista_filmes;

    //n = numero de filmes;  c = numero de categorias
    cin >> n >> c;

    //Vetor de categorias
    int n_filmes_categoria;
    for (int i = 0; i < c; i++){
        cin >> n_filmes_categoria;
        categorias.push_back(n_filmes_categoria);
    }

    filmes.reserve(n); // reserva o espaço na memoria

    //Vetor de filmes
    int inicio, fim, categoria;
    for (int i = 0; i < n; i++){
        cin >> inicio;
        cin >> fim;
        cin >> categoria;
        if (inicio > fim){
            continue;
        }
        if (inicio == fim){
            fim += 1; 
        }
        filmes.push_back({i, inicio, fim, fim - inicio, categoria});
    }

    // Ordena por ordem crescente de hora de fim
    sort(filmes.begin(), filmes.end(), [](auto& i, auto& j){return i.fim < j.fim;}); 
    int i = 0;
    for(auto& el : filmes){
        if(i == 0){
            lista_filmes.push_back(el);
            i += 1;
        }
        //Verifica se horário é válido e se a categoria permite adição a lista
        if(el.inicio >= lista_filmes[i-1].fim && categorias[el.categoria-1] != 0){
            lista_filmes.push_back(el);
            categorias[el.categoria-1] -= 1; 
            i += 1;
        }
    }

    end = clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);

    int duracao_total = 0;
    for(auto& el:lista_filmes){
        duracao_total += el.duracao;
        std::cout << el.id << " ";
    }
    std::cout << std::endl;
    
    // Escreve novo resultado no csv
    // Métricas: número de filmes alocados, quantidade de horas ocupadas, tempo de execução
    ofstream outputFile;
    string result_file = "../heuristicas/gulosa/results.csv";  // Caminho relativo ao script que chama a heuristica
    outputFile.open(result_file, ios::app);
    string result = variavel + "," + to_string(lista_filmes.size()) + "," + to_string(duracao_total) + 
        "," + to_string(time_taken) + "," + arquivo;
    outputFile << result << endl;
    return 0;
}