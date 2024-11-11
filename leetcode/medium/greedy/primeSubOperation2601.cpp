/**
 * @Time : 2023/3/27-3:13 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
const int n = 1005;
vector<int> prime;
int init = []() {
    vector<int> isPrime(n + 1, 1);
    for(int i = 2; i <= n; i++){
        if(isPrime[i] == 0) continue; // 不是素数 跳过
        if((long)i * i >= INT_MAX) continue;
        for(int j = i * i; j <= n; j += i) // 将素数的所有倍数标记成合数
            isPrime[j] = 0;
    }
    for(int i = 2; i <= n; i++)
        if(isPrime[i] == 1) prime.push_back(i);
    return 0;
}();

class Solution {
public:
    bool primeSubOperation(vector<int>& nums) {
        for(int i = 0, pre = 0; i < nums.size(); i++){
            int t = lower_bound(prime.begin(), prime.end(), nums[i] - pre) - prime.begin();
            if(t == 0 && nums[i] <= pre) return false;
            pre = t > 0 ? nums[i] - prime[t - 1] : nums[i];
        }
        return true;
    }
};

int main(){
    Solution s;
    vector<int> arr = {18,12,14,6};
    s.primeSubOperation(arr);
    cout << 0 << endl;
}