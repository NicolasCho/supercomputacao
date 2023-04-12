#include <iostream>
#include <math.h>  
#include <omp.h>
using namespace std;

int main(){
    clock_t start, end;
    start = clock();

    int n = 1000000000;
    float sum = 0;

    omp_set_num_threads(1);
    #pragma omp parallel shared(sum)
    {   
        int id, i, nthreads, istart, iend;
        id = omp_get_thread_num();
        nthreads = omp_get_num_threads();
        istart = id*n /nthreads;
        iend =(id+1) * n/nthreads;
        if (id == nthreads - 1) iend = n;
        for (i = istart; i < iend; i++){
            sum += pow(-1, i)/(2*i + 1);
        }
    }

    end = clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);

    cout << sum *4 << endl;
    cout << "time taken: " << time_taken << endl;

    return 0;
}