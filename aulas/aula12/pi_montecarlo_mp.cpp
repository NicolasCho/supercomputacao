#include<iostream>
#include<random>
#include<chrono>
#include<math.h>
#include<omp.h>
using namespace std;


//PRIMEIRA TENTATIVA: O resultado gerado não é aleatório. O valor de pi será sempre o mesmo para todas as execuções,pois
//a seed utilizada é i, logo é fixa para para todas as execuções do programa.
int main(){
    float time = omp_get_wtime();

    int sum = 0;
    int n = 100000000;
    float x;
    float y;


    #pragma omp parallel for reduction(+:sum)
    for(int i = 0; i < n; i++){
        //unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine generator (i);
        std::uniform_real_distribution<double> distribution(0.0, 1.0);

        x = distribution(generator);
        y = distribution(generator); 
        if (pow(x,2)+pow(y,2) <= 1){
            sum+=1;
        }
    }
    

    float pi = (float)4*sum/n;
    cout << "pi = " << pi << endl;

    time = omp_get_wtime()-time;
    cout << "Tempo em segundos :" << time << endl;
    return 0;
}