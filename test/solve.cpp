#include<bits/stdc++.h>

using namespace std;
const int N = 1e5 + 5;

const int n = 1000000;
vector<int> prime;
int init = []() {
    vector<int> isPrime(n + 1, 1);
    for (int i = 2; i <= n; ++i) {
        if (isPrime[i] == 1) prime.push_back(i);
        for (int j = 0; j < prime.size() && i * prime[j] <= n; ++j) {
            isPrime[i * prime[j]] = 0;
            if (i % prime[j] == 0)
                break;
        }
    }
    return 0;
}();

class Solution {
public:

};

int main() {
    vector<int> arr1 = {14,-1,-1,46};
    vector<int> arr3 = {7, 19, 19, 20, 33};
    vector<int> w = {6, 6, 3, 9, 3, 5, 1};
    vector<string> arr2 = {"000", "000"};
    vector<string> arr5 = {"cd", "bcd", "xyz"};
    vector<vector<int>> arr4 = {{-2,3},{2,3},{2,1}};
    vector<vector<int>> arr6 = {{0,0}};
    Solution s;
    cout << prime.size();
}
