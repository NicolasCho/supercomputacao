#include <iostream>
#include <math.h>  
#include <omp.h>
using namespace std;

int main(){
    double time = omp_get_wtime();

    int n = 1000000000;
    float sum = 0;

    omp_set_num_threads(8);
    #pragma omp parallel for reduction(+:sum) 
    for (int i = 0; i < n; i++){
        sum += pow(-1, i)/(2*i + 1);
    }
    

    time = omp_get_wtime() - time;

    cout << sum *4 << endl;
    cout << "time taken: " << time << endl;

    return 0;
}