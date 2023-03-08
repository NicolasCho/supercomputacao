#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
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

    // Ordena por ordem crescente de hora de fim
    sort(filmes.begin(), filmes.end(), [](auto& i, auto& j){return i.fim < j.fim;}); 

    int i = 0;
    for(auto& el : filmes){
        if(i == 0){
            lista_filmes.push_back(el);
            i += 1;
        }
        else if(el.inicio >= lista_filmes[i-1].fim && categorias[el.categoria-1] != 0){
            lista_filmes.push_back(el);
            categorias[el.categoria-1] -= 1; 
            i += 1;
        }
        else{
            continue;
        }
    }

    for(auto& el:lista_filmes){
        cout << el.id << " ";
    }
    cout << endl;
    return 0;
}