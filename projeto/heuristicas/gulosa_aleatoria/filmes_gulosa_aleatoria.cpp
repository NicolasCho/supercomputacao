#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
using namespace std;




int main(){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

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

    int n_filmes_categoria;
    for (int i = 0; i < c; i++){
        cin >> n_filmes_categoria;
        categorias.push_back(n_filmes_categoria);
    }

    filmes.reserve(n); // reserva o espaço na memoria

    int inicio, fim, categoria;
    for (int i = 0; i < n; i++){
        cin >> inicio;
        cin >> fim;
        cin >> categoria;
        filmes.push_back({i, inicio, fim, fim - inicio, categoria});
    }

    // Ordena por ordem crescente de hora de fim (GULOSA)
    sort(filmes.begin(), filmes.end(), [](auto& i, auto& j){return i.fim < j.fim;}); 

    // Vetor de horários
    vector<int> horarios (24, 0);

    int i = 0;
    bool disponivel;
    for(auto& el : filmes){
        disponivel = true;
        // 25% de chance de pegar outro filme (ALEATORIEDADE)
        if(distribution(generator) > 0.75 && i < n){
            std::uniform_int_distribution<int> distributionInt(i, n-1);
            int p  = distributionInt(generator);

            if(categorias[filmes[p].categoria-1] != 0){    // Verificação de categoria disponível
                for(int hora = filmes[p].inicio; hora <= filmes[p].fim; hora++){   // Verificação de horário disponível
                    if (horarios[hora] == 1){
                        disponivel = false;
                        break;
                    }
                }
                if(disponivel){
                    lista_filmes.push_back(filmes[p]);
                    categorias[filmes[p].categoria-1] -= 1; 
                    for(int hora = filmes[p].inicio; hora <= filmes[p].fim; hora++){ 
                        horarios[hora] = 1;
                    }
                    filmes.erase(filmes.begin()+p-1);
                    n = n - 1;
                }
            } 
        }
        else{
            if(categorias[el.categoria-1] != 0){    // Verificação de categoria disponível
                for(int hora = el.inicio; hora <= el.fim; hora++){   // Verificação de horário disponível
                    if (horarios[hora] == 1){
                        disponivel = false;
                        break;
                    }
                }
                if(disponivel){
                    lista_filmes.push_back(el);
                    categorias[el.categoria-1] -= 1; 
                    for(int hora = el.inicio; hora <= el.fim; hora++){ 
                        horarios[hora] = 1;
                    }
                }
            } 
        }
        i += 1;   
    }

    for(auto& el:lista_filmes){
        cout << el.id << " ";
    }
    
    cout << endl;
    return 0;
}