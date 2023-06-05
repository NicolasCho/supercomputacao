#include <iostream>
#include <vector>
#include <algorithm>
#include <omp.h>
#include <iostream>
#include <fstream>
using namespace std;

struct filme{
        int id;
        int inicio;
        int fim;
        int duracao;
        int categoria;
};

int maior_valor(vector<filme> filmes, vector<filme>& assistidos, vector<filme>& melhor, vector<int> categorias, vector<int> horarios){
    vector<filme> filmes2 = filmes; 
    vector<int> horarios2 = horarios;
    int adiciona = 0;
    int com_item = 0;
    bool disponivel = true;


    if(filmes.empty() || horarios.back() == 0){
        return 0;
    }

    if(categorias[filmes[0].categoria-1] != 0){    // Verificação de categoria disponível
        for(int hora = filmes[0].inicio; hora <= filmes[0].fim; hora++){   // Verificação de horário disponível
            if (horarios[hora] == 1 && hora != filmes[0].fim){
                disponivel = false;
                break;
            }
        }
        if(disponivel){
            categorias[filmes[0].categoria-1] -= 1; 
            for(int hora = filmes[0].inicio; hora < filmes[0].fim; hora++){ 
                horarios[hora] = 1;
                horarios.back() -= 1;
            }
            assistidos.push_back(filmes[0]);
            filmes.erase(filmes.begin());
            com_item = maior_valor(filmes, assistidos, melhor, categorias, horarios);  
            adiciona += 1;
        }
    } 
    filmes2.erase(filmes2.begin());

    int sem_item = maior_valor(filmes2, assistidos, melhor, categorias, horarios2);

    int valor_atual = assistidos.size();
    int valor_melhor = melhor.size();
    if(valor_atual > valor_melhor){
        melhor = assistidos;
    }
    assistidos.clear();
    return max(sem_item, adiciona+com_item);
}

int main(int argc, char *argv[]){
    float time = omp_get_wtime();

    // Recebe o nome da variavel testada e o nome do arquivo
    string variavel = argv[1]; 
    string arquivo = argv[2];

    int n = 0;
    int c = 0;

    // Vetor de horários
    vector<int> horarios (24, 0);
    horarios.push_back(24);  //Última posição do vetor como soma da quantidade de zeros (horas disponíveis)
    vector<filme> assistidos;
    vector<filme> filmes;
    vector<int> categorias;
    vector<filme> melhor;   //Resposta

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

    maior_valor(filmes, assistidos, melhor, categorias, horarios);

    time = omp_get_wtime()-time;
    

    int duracao_total = 0;
    for(auto& el:melhor){
        duracao_total += el.duracao;
    }

    // Escreve novo resultado no csv
    // Métricas: número de filmes alocados, quantidade de horas ocupadas, tempo de execução
    ofstream outputFile;
    string result_file = "../heuristicas/exaustiva/results.csv";  // Caminho relativo ao script que chama a heuristica
    outputFile.open(result_file, ios::app);
    string result = variavel + "," + to_string(melhor.size()) + "," + to_string(duracao_total) + 
        "," + to_string(time) + "," + arquivo;
    outputFile << result << endl;

    return 0;
}
