/**
 * @Time : 2023/5/4-9:07 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7, full = (1 << 10) - 1;
const int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
vector<int> digits(31, 0);
vector<bool> useless(31, false);
int init = []() {
    for (int i = 2; i < 31; i++) {
        int num = i, status = 0;
        for (int j = 0; j < 10 && num > 1;) {
            if (num % primes[j] == 0) {
                num /= primes[j];
                int t = 1 << j;
                if(t & status) {
                    useless[i] = true;
                    break;
                }
                status |= t;
            } else j++;
        }
        digits[i] = status;
    }
    return 0;
}();

class Solution {
public:
    /*
     * dp[i][j] 表示考虑使用数字[1,i]的满足题意的方案数
     * 因为1不会影响质数因子，因此任何一个数字1，都可以选或者不选
     * 先不考虑1，令dp[1][0] = 1，实质上是指不选任何数字的方案数为1
     */
    int numberOfGoodSubsets(vector<int> &nums) {
        vector<int> count(31, 0);
        for (int num: nums)
            count[num]++;
        vector<vector<long long>> dp(31, vector(full + 1, 0ll));
        dp[1][0] = 1;
        for (int i = 2; i < 31; i++) {
            dp[i] = vector(dp[i - 1].begin(), dp[i - 1].end());
            if (useless[i] || count[i] == 0) continue;
            int d = digits[i], cnt = count[i];
            dp[i][d] = (dp[i][d] + dp[i - 1][0] * cnt) % mod;
            for (int s = full; s; s = (s - 1) & full){
                if((d & s) == 0)
                    dp[i][s | d] = (dp[i][s | d] + dp[i - 1][s] * cnt) % mod;
            }
        }
        long long res = 0;
        for(long long num : dp[30])
            res += num;
        return ((res - 1) % mod * quickPower(2, count[1]) + mod) % mod;
    }

    long quickPower(int a, int b){
        long res = 1, temp = a;
        while (b != 0){
            if((b & 1) == 1) res = res * temp % mod;
            temp = temp * temp % mod;
            b >>= 1;
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}