#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct item{
        int id;
        int peso;
        int valor;
};

int maior_valor(vector<item> itens, vector<item>& usados, vector<item>& melhor, int capacidade, vector<item> mochila){
    vector<item> itens2 = itens; 
    int valor = 0;
    int peso = 0;
    int com_item = 0;
    if(itens.empty() || (capacidade == 0)){
        return 0;
    }
    if(itens[0].peso <= capacidade){
        usados.push_back(itens[0]);
        valor = itens[0].valor;
        peso = itens[0].peso;
        itens.erase(itens.begin());
        com_item = maior_valor(itens, usados, melhor, capacidade - peso, mochila);  
    }
    itens2.erase(itens2.begin());
    int sem_item = maior_valor(itens2, usados, melhor, capacidade, mochila); 

    int valor_atual = 0;
    int valor_melhor = 0;
    for(auto& el:usados){
        valor_atual += el.valor;
    }
    for(auto& el:melhor){
        valor_melhor += el.valor;
    }
    if(valor_atual > valor_melhor){
        melhor = usados;
    }
    usados.clear();
    return max(sem_item, valor + com_item);
}

int main(){
    int n = 0;
    int w = 0;

    vector<item> itens, usados, melhor;
    vector<item> mochila;

    cin >> n >> w;
    itens.reserve(n); // reserva o espaço na memoria

    //Cria os itens
    int peso, valor;
    for (int i = 0; i < n; i++)
    {
        cin >> peso;
        cin >> valor;
        itens.push_back({i, peso, valor});
    }
    
    int melhor_valor_mochila = maior_valor(itens, usados, melhor, w, mochila);

    cout << "Melhor valor mochilha: " << melhor_valor_mochila << endl;
    sort(melhor.begin(), melhor.end(), [](auto& i, auto& j){return i.id < j.id;});
        for(auto& el:melhor){
            cout << el.id << " ";
        }
    return 0;
}