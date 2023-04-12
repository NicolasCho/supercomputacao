#include <iostream>
#include <math.h>  
using namespace std;

int main(){
    clock_t start, end;
    start = clock();

    int n = 1000000000;
    float sum = 0;
    for (int i = 0; i < n; i++){
        sum += pow(-1, i)/(2*i + 1);
    }

    end = clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);

    cout << sum *4 << endl;
    cout << "time taken: " << time_taken << endl;

    return 0;
}