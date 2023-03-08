#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    struct item{
        int id;
        int peso;
        int valor;
    };

    int n = 0;
    int w = 0;

    vector<item> itens;
    vector<item> mochila;

    cin >> n >> w;
    itens.reserve(n); // reserva o espaço na memoria


    int peso, valor;
    for (int i = 0; i < n; i++)
    {
        cin >> peso;
        cin >> valor;
        itens.push_back({i, peso, valor});
    }
    // ordena 
    sort(itens.begin(), itens.end(), [](auto& i, auto& j){return i.valor > j.valor;}); //func de uma linha
    peso = 0;
    valor = 0;

    for(auto& el: itens){
        if(el.peso + peso <= w){
            mochila.push_back(el);
            peso += el.peso;
            valor += el.valor;
        }
    }   

    sort(mochila.begin(), mochila.end(), [](auto& i, auto& j){return i.id < j.id;});
    for(auto& el:mochila){
        cout << el.id << " ";
    }
    cout << endl <<"Valor da mochila: "<<valor << endl;
    return 0;
    
}
/*
Fazer tudo que for possivel por referencias
Alocar toda memoria que voce sabe que vai usar para evitar realocamento
*/