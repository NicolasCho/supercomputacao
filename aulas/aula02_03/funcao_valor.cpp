#include <iostream>
using namespace std;

int sqrt_it(int& x);


int main(){
    int t = 10;
    cout << "endereco de t:" << &t << endl;
    cout << sqrt_it(t) << endl;
    cout << "valor de t:" << t << endl;
    return 0;
}

int sqrt_it(int& x){
    cout << "endereco de x:" << &x << endl;
    x = x*x;
    return x;
}