#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <iostream>
#include <chrono>
#include <thrust/extrema.h>

using namespace std;

int main(){
    int n = 2518;
    thrust::host_vector<double> vcpu(n);

    auto start = std::chrono::system_clock::now();

    for(int i=0;i<n;i++)
       std::cin>>vcpu[i];

    auto end = std::chrono::system_clock::now();
    auto elapsed = end - start;
    cout << "Alocação:" << elapsed.count() << '\n';


    start = std::chrono::system_clock::now();
    thrust::device_vector<double> vgpu(vcpu);
    end = std::chrono::system_clock::now();
    elapsed = end - start;
    cout << "Cópia:" << elapsed.count() << '\n';

    double sum_total = thrust::reduce(vgpu.begin(), vgpu.end(), (double) 0, thrust::plus<double>());

    cout << "Preço médio: " << sum_total/n << endl;

    double sum_ly = thrust::reduce(vgpu.end()-365, vgpu.end(), (double) 0, thrust::plus<double>());

    cout << "Preço médio ano último ano: " << sum_ly/365 << endl;

    double max_total = thrust::reduce(vgpu.begin(), vgpu.end(), (double) 0, thrust::maximum<double>());
    double min_total = thrust::reduce(vgpu.begin(), vgpu.end(), (double) 1000000, thrust::minimum<double>());

    double max_ly = thrust::reduce(vgpu.end()-365, vgpu.end(), (double) 0, thrust::maximum<double>());
    double min_ly = thrust::reduce(vgpu.end()-365, vgpu.end(), (double) 1000000, thrust::minimum<double>());

    cout << "max total: " << max_total << endl;
    cout << "min total: " << min_total << endl;
    cout << "max ano: " << max_ly << endl;
    cout << "min ano: " << min_ly << endl;
    return 0;
}