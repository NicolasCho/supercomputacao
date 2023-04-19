#include<iostream>
#include<random>
#include<chrono>
#include<math.h>
#include<omp.h>
using namespace std;


//SEGUNDA TENTATIVA: 
int main(){
    float time = omp_get_wtime();

    int sum = 0;
    int n = 100000000;
    float x;
    float y;


    #pragma omp parallel reduction(+:sum)
    {
        int id, i, nthreads, istart, iend;
        id = omp_get_thread_num();
        nthreads = omp_get_num_threads();
        istart = id*n/nthreads;
        iend = (id+1)*n/nthreads;
        if(id==nthreads-1) iend = n;
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine generator (seed);
        std::uniform_real_distribution<double> distribution(0.0, 1.0);

        for(i = istart; i<iend; i++){
            x = distribution(generator);
            y = distribution(generator); 
            if (pow(x,2)+pow(y,2) <= 1){
                sum+=1;
            }
        }
    }
    float pi = (float)4*sum/n;
    cout << "pi = " << pi << endl;

    time = omp_get_wtime()-time;
    cout << "Tempo em segundos :" << time << endl;
    return 0;
}