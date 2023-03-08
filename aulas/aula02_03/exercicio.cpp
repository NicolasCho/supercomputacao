#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool my_compare(float a, float b);
float calc_mean(vector<float>& v);

int main(){
    float x;
    vector<float> v;

    while (cin >> x){
        v.push_back(x);
    }
    
    sort(v.begin(), v.end(), my_compare);

    cout << "menor:" << v[0] <<endl;
    cout << "maior:" << v.back() <<endl;

    cout << "media:" << calc_mean(v) << endl;

    return 0;
}

bool my_compare(float a, float b){
    return a < b;
}

float calc_mean(vector<float>& v){
    float sum (0);
    for(auto& e:v){
        sum += e;
    }
    return sum/v.size();
}