#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/functional.h>
#include <thrust/transform.h>
#include <iostream>
#include <chrono>
#include <algorithm>

int main(){
    int n = 2518;
    thrust::host_vector<double> AAPL(n);
    thrust::host_vector<double> MSFT(n);
    for(int i = 0; i < n; i++){
        std::cin >> AAPL[i];
        std::cin >> MSFT[i];
    }

    thrust::device_vector<double> AAPL_G(AAPL);
    thrust::device_vector<double> MSFT_G(MSFT);
    thrust::device_vector<double> diff(n);

    thrust::transform(AAPL_G.begin(), AAPL_G.end(), MSFT_G.begin(), diff.begin(), thrust::minus<double>());
    double media = thrust::reduce(diff.begin(),diff.end(), (double)0, thrust::plus<double>())/n;

    std::cout << "Média da diferenca = " << media << std::endl;

    thrust::device_vector<double> medias(n);
    thrust::device_vector<double> quad_diff(n);
    thrust::fill(medias.begin(), medias.end(), media);

    auto sum_func = [] __device__ (int a, int b) { return (a-b)*(a-b); };

    thrust::transform(diff.begin(), diff.end(), medias.begin(), quad_diff.begin(), 
                        sum_func);
    
    double variancia = thrust::reduce(quad_diff.begin(),quad_diff.end(), (double)0, thrust::plus<double>())/n;

    std::cout << "variancia: " << variancia << std::endl;    

    return 0;
}