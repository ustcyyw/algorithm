#include<bits/stdc++.h>

using namespace std;

const int n = 10000;
vector<int> prime;
int init = []() {
    vector<int> isPrime(n + 1, 1);
    for(int i = 2; i <= n; i++){
        if(isPrime[i] == 0) continue; // 不是素数 跳过
        if((long)i * i >= LONG_LONG_MAX) continue;
        for(int j = i + i; j <= n; j += i) // 将素数的所有倍数标记成合数
            isPrime[j] = 0;
    }
    for(int i = 2; i <= n; i++)
        if(isPrime[i] == 1) prime.push_back(i);
    return 0;
}();

class Solution {
public:

};

int main() {
    vector<int> arr1 = {1,2,1};
    vector<int> arr3 = {7, 19, 19, 20, 33};
    vector<int> w = {6, 6, 3, 9, 3, 5, 1};
    vector<string> arr2 = {"000", "000"};
    vector<string> arr5 = {"cd", "bcd", "xyz"};
    vector<vector<int>> arr4 = {{-2,3},{2,3},{2,1}};
    vector<vector<int>> arr6 = {{0,0}};
    Solution s;
    cout << prime.size() << "\n";
}
