#include<iostream>
#include<omp.h>
using namespace std;

int main(){
    int a = 0;
    double time = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp critical
        cout << "tid = " << omp_get_thread_num() << endl;
        a = a + omp_get_thread_num();
    }

    time = omp_get_wtime() - time;

    cout << a << endl;
    cout<<time <<endl;
    return 0;
}