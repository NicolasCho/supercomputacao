#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <chrono>
#include <cstdlib>
#include <algorithm>
//INSIRA AS IMPORTACOES NECESSARIAS DA THRUST
#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/functional.h>
#include <thrust/transform.h>
#include <cmath>
#include <random>

using namespace std::chrono;

void reportTime(const char* msg, steady_clock::duration span) {
    auto ms = duration_cast<milliseconds>(span);
    std::cout << msg << " - levou - " <<
    ms.count() << " milisegundos" << std::endl;
}

// CRIE UMA FUNCTOR PARA CALCULAR A SQUARE
struct square
{    
    __device__
    float operator()(const float& x) {   //x e y são os vetores
           return (x*x);  
    }
};



// IMPLEMENTE O CALCULO DA MAGNITUDE COM THRUST
float magnitude(thrust::device_vector<float> &v) {
    float result;
    // ... add Thrust calls
    // AQUI VAO AS CHAMADAS THRUST 
    result = std::sqrt(thrust::transform_reduce(v.begin(), v.end(), square(), 0, thrust::plus<float>())); 
    return result;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << argv[0] << ": numero invalido de argumentos\n"; 
        std::cerr << "uso: " << argv[0] << "  tamanho do vetor\n"; 
        return 1;
    }
    int n = std::atoi(argv[1]); //numero de elementos
    steady_clock::time_point ts, te;

    // Faça um  vector em thrust 
    thrust::host_vector<float> v_cpu(n);


    // inicilize o  vector
    ts = steady_clock::now();

    thrust::generate(v_cpu.begin(), v_cpu.end(), rand);

    thrust::device_vector<float> v_gpu(v_cpu);

    te = steady_clock::now();
    reportTime("Inicializacao", te - ts);

    // Calcule a magnitude do vetor
    ts = steady_clock::now();
    float len = magnitude(v_gpu);
    te = steady_clock::now();
    reportTime("Tempo para calculo", te - ts);


    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Magnitude : " << len << std::endl;
}