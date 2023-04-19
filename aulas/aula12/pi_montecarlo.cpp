#include<iostream>
#include<random>
#include<chrono>
#include<math.h>
#include<omp.h>
using namespace std;


// Uso de critical não paraleliza esse problema, pois cada thread irá esperar outra acabar para começar. Logo
// é o mesmo que fazer de forma sequencial.
int main(){
    float time = omp_get_wtime();
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    int sum = 0;
    int n = 100000000;
    float x;
    float y;

    //não funciona! (nao paraleliza)
    #pragma omp parallel for reduction(+:sum)
    for(int i = 0; i < n; i++){
        #pragma omp critical
        {
            x = distribution(generator);
            y = distribution(generator); 
        }
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