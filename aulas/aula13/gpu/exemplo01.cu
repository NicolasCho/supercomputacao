#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <iostream>

using namespace std;

int main(){
    thrust::host_vector<double> host(5,0);
    host[4] = 35;
    thrust::device_vector<double> dev(host);
    host[2] = 12;

    printf("host:");
    for(auto i=host.begin(); i != host.end(); i++){
        cout << *i << " ";
    }

    printf("\n");

    printf("host:");
    for(auto i=dev.begin(); i != dev.end(); i++){  //OPERAÇÃI LENTA (não recomenda-se fazer operação sequencial em gpu)
        cout << *i << " ";
    }
    return 0;
}