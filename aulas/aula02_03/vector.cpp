#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
bool my_compare(float a, float b);

int main(){
    vector<float> nums;
    nums.push_back(10.5);
    nums.push_back(4.0);
    for(auto& e:nums){
        cout << e << "\t";
    }
    cout << endl;

    sort(nums.begin(), nums.end(), my_compare);

    for(auto& e:nums){
        cout << e << "\t";
    }
    cout << endl;
    return 0;
}

bool my_compare(float a, float b){
    return a < b;
}