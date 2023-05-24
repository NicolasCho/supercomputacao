#include <iostream>
#include <vector>
#include <algorithm>
#include <omp.h>
using namespace std;

struct filme{
        int id;
        int inicio;
        int fim;
        int duracao;
        int categoria;
};

struct resultado{
    int alocacao_total;
    bool reultado_otimo;
};

resultado maior_valor(vector<filme> filmes, vector<filme>& assistidos, vector<filme>& melhor, vector<int> categorias, vector<int> horarios){
    vector<filme> filmes2 = filmes; 
    vector<int> horarios2 = horarios;
    int duracao = 0;
    resultado com_item = {0,false};
    bool disponivel = true;

    if (horarios.back() == 0){
        return resultado{24, true};
    }
    if(filmes.empty()){
        return resultado{0, false};
    }

    if(categorias[filmes[0].categoria-1] != 0){    // Verificação de categoria disponível
        for(int hora = filmes[0].inicio; hora <= filmes[0].fim; hora++){   // Verificação de horário disponível
            if (horarios[hora] == 1){
                disponivel = false;
                break;
            }
        }
        if(disponivel){
            duracao = filmes[0].duracao;
            categorias[filmes[0].categoria-1] -= 1; 
            for(int hora = filmes[0].inicio; hora <= filmes[0].fim; hora++){ 
                horarios[hora] = 1;
                horarios.back() -= 1;
            }
            assistidos.push_back(filmes[0]);
            filmes.erase(filmes.begin());
            com_item = maior_valor(filmes, assistidos, melhor, categorias, horarios);  
            if(com_item.reultado_otimo){
                return com_item;
            }
        }
    } 
    filmes2.erase(filmes2.begin());
    resultado sem_item = maior_valor(filmes2, assistidos, melhor, categorias, horarios2); 
    if(sem_item.reultado_otimo){
        return sem_item;
    }

    int valor_atual = 0;
    int valor_melhor = 0;
    for(auto& el:assistidos){
        valor_atual += el.duracao;
    }
    for(auto& el:melhor){
        valor_melhor += el.duracao;
    }
    if(valor_atual > valor_melhor){
        melhor = assistidos;
    }
    assistidos.clear();
    return resultado{ max(sem_item.alocacao_total, duracao + com_item.alocacao_total + 1), false};
}

int main(){//int argc, char *argv[]){
    float time = omp_get_wtime();

    //Recebe o nome da variavel testada e o nome do arquivo
    // string variavel = argv[1]; 
    // string arquivo = argv[2];

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

    resultado maior_tempo_tela = maior_valor(filmes, assistidos, melhor, categorias, horarios);

    time = omp_get_wtime()-time;
    cout << "Tempo em segundos :" << time << endl;

    cout << "Melhor alocação: " << maior_tempo_tela.alocacao_total << endl;

    cout << "Número de filmes alocados: " << melhor.size() << endl;

    sort(melhor.begin(), melhor.end(), [](auto& i, auto& j){return i.id < j.id;});
    for(auto& el:melhor){
        cout << el.id << " ";
    }
    cout << endl;

    return 0;
}
