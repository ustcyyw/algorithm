/**
 * @Time : 2024/4/14-4:01 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛393 t2
 */
#include<bits/stdc++.h>
using namespace std;
const int n = 105;

vector<int> isPrime;
int init = []() {
    isPrime.assign(n + 1, 1);
    for(int i = 2; i <= n; i++){
        if(isPrime[i] == 0) continue; // 不是素数 跳过
        if((long)i * i >= LONG_LONG_MAX) continue;
        for(int j = i + i; j <= n; j += i) // 将素数的所有倍数标记成合数
            isPrime[j] = 0;
    }
    isPrime[1] = 0;
    return 0;
}();

class Solution {
public:
    int maximumPrimeDifference(vector<int>& nums) {
        int ans = 0, first = -1;
        for(int i = 0; i < nums.size(); i++) {
            if(isPrime[nums[i]]) {
                if(first == -1) first = i;
                ans = i - first;
            }
        }
        return ans;
    }
};