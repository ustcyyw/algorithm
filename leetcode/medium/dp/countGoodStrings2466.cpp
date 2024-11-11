/**
 * @Time : 2022/11/22-9:29 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countGoodStrings(int low, int high, int zero, int one) {
        vector<long> dp(high + 2);
        dp[0] = 1;
        int n = dp.size(), mod = 1e9 + 7;
        for(int i = 0; i < dp.size(); i++){
            if(i + zero < n) dp[i + zero] = (dp[i + zero] + dp[i]) % mod;
            if(i + one < n) dp[i + one] = (dp[i + one] + dp[i]) % mod;
        }
        long long res = 0;
        for(int i = low + 1; i <= high + 1; i++)
            res += dp[i];
        return (int)(res % mod);
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}