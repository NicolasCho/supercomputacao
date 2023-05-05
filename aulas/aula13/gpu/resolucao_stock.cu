#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/functional.h>
#include <thrust/transform.h>
#include <iostream>
#include <chrono>
#include <algorithm>

int main(){
    int n = 2518;
    thrust::host_vector<double> vcpu(n);
    for(int i = 0; i < n; i++){
        std::cin >> vcpu[i];
    }
    thrust::device_vector<double> vgpu(vcpu);

    double media = thrust::reduce(vgpu.begin(),vgpu.end(), (double)0, thrust::plus<double>())/n;

    std::cout << "Média dos elementos = " << media << std::endl;

    thrust::device_vector<double>::iterator last_365 = vgpu.end()-365;
    double media365 = thrust::reduce(last_365,vgpu.end(), (double)0, thrust::plus<double>())/365;

    std::cout << "Média dos últimos 365 elementos = " << media365 << std::endl;
    
    thrust::device_vector<double>::iterator max_elem = thrust::max_element(vgpu.begin(),vgpu.end()); 
    //max_elem é um iterator ("ponteiro")
    thrust::device_vector<double>::iterator min_elem = thrust::min_element(vgpu.begin(),vgpu.end()); 

    std::cout << "Maior elemento = " << *max_elem << std::endl;
    std::cout << "Menor elemento = " << *min_elem << std::endl;

    thrust::device_vector<double>::iterator max_elem365 = thrust::max_element(vgpu.end()-365,vgpu.end()); 
    //max_elem é um iterator ("ponteiro")
    thrust::device_vector<double>::iterator min_elem365 = thrust::min_element(vgpu.end()-365,vgpu.end()); 

    std::cout << "Maior elemento 365 = " << *max_elem365 << std::endl;
    std::cout << "Menor elemento 365 = " << *min_elem365 << std::endl;
    return 0;
}