#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

int main(){
    // obtain a seed from the system clock:
    unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
    auto shuffler = std::default_random_engine {};
    std::default_random_engine generator (seed1);
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    struct item{
        int id;
        int peso;
        int valor;
    };

    int n = 0;
    int w = 0;

    vector<item> itens_shuffled;
    vector<item> itens_shuffled_batch;
    vector<item> mochila;

    cin >> n >> w;
    itens_shuffled.reserve(n); // reserva o espaço na memoria

    //Cria os itens
    int peso, valor;
    for (int i = 0; i < n; i++)
    {
        cin >> peso;
        cin >> valor;
        itens_shuffled.push_back({i, peso, valor});
        itens_shuffled_batch.push_back({i, peso, valor});
    }

    vector<item> best_knapsack;
    int best_value = 0;
    for (int e = 0; e < 10; e++){
        // mistura 
        shuffle(itens_shuffled_batch.begin(), itens_shuffled_batch.end(),shuffler);

        //Solução inicial aleatória
        peso = 0;
        valor = 0;
        int i = 0;
        for(auto& el : itens_shuffled_batch){
            if(distribution(generator) > 0.5){
                if(el.peso + peso <= w){
                    mochila.push_back(el);
                    peso += el.peso;
                    valor += el.valor;
                    itens_shuffled_batch.erase(itens_shuffled_batch.begin()+i);
                    i-=1;
                }
            }
            i+=1;
        }  

        //Põe em ordem e checa por novos itens
        sort(itens_shuffled_batch.begin(), itens_shuffled_batch.end(), [](auto& i, auto& j){return i.valor > j.valor;});
        for(auto& el : itens_shuffled_batch){
            if(el.peso + peso <= w){
                mochila.push_back(el);
                peso += el.peso;
                valor += el.valor;
            }
        } 

        if( valor > best_value){
            best_knapsack = mochila;
        }
        mochila.clear();
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